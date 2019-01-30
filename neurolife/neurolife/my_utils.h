#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

using std::string;

namespace utils {
	void sleep(int sleepMs);

	void clear();



	// helper class
	class color {
	public:
		color(unsigned short val) :
			m_val(val) { }

		color(string val):
			m_val_unix(val) { }

		void set() const;
		std::ostream& set(std::ostream& os) const;

	private:
		unsigned short m_val;
		string m_val_unix;
	};


#ifdef WINDOWS
	static const color red(4);
	static const color green(2);
	static const color blue(1);
	static const color white(7);
#endif
#ifdef LINUX
	static const color red("\033[0;31m");
	static const color green("\033[1;32m");
	static const color blue("\033[0;36m");
	static const color white("\033[0m");
#endif
}

inline std::ostream & operator<<(std::ostream & os, const utils::color & c)
{
	#ifdef LINUX
		return c.set(os);
	#else 
		c.set();
		return os;
	#endif
	
}

string get_font_path(const string& path_to_bin);