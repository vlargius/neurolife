#include <iostream>

using std::cout;

#include "my_utils.h"

namespace my {
	void sleep(int sleepMs)
	{
		#ifdef LINUX
			usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
		#endif
		#ifdef WINDOWS
			Sleep(sleepMs* 1000);
		#endif
	}

	void clear()
	{
		#ifdef WINDOWS
			std::system("cls");
		#else
			// Assume POSIX
			std::system("clear");
		#endif
	}  


	inline void SetColor(unsigned short color) {
		#ifdef WINDOWS
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		#endif
	}

	void color::set() const	{
		SetColor(m_val);
	}

	std::ostream& color::set(std::ostream& os) const {
		return os << m_val_unix;
	}

}



	/*      
	 foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47
*/