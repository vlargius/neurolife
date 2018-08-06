#include "my_utils.h"

namespace my {
	void sleep(int sleepMs)
	{
#ifdef LINUX
		usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
		Sleep(sleepMs);
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

	inline void SetColor(WORD color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	color::color(WORD val) : m_val(val) { }

	void color::set() const
	{
		SetColor(m_val);
	}

}
