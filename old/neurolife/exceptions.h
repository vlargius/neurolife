#pragma once

class Error {
public:
	Error(const char * msg) :
		msg(msg) {}
	const char * what() { return msg; }
private:
	const char* msg;
};


inline void error(const char * msg) {
	throw Error(msg);
}