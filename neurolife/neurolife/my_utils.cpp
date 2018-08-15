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

string get_font_path(const string& path_to_bin) {
	auto ch = path_to_bin.end();
	ch--;
	while (ch != path_to_bin.begin() && *ch != '\\') {
		ch--;
	}
	return string(path_to_bin.begin(), ch) + "\\fonts\\";
}