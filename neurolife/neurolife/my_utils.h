#pragma once

#include <cstdlib>
#include <iostream>

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif
namespace my {
	void sleep(int sleepMs);

	void clear();

	// helper class
	class color {
	public:
		color(WORD val);

		void set() const;

	private:
		WORD m_val;
	};

	static const color red(4);
	static const color green(2);
	static const color blue(1);
	static const color white(7);
}

// overload operator<< to get manipulator to work
inline std::ostream & operator<<(std::ostream & os, const my::color & c)
{
	c.set();
	return os;
}