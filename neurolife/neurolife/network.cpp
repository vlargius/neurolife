#include <algorithm>

#include "network.h"


double Network::calc() const
{
	double out = 0;
	for (int i = 0; i < w*h; ++i) {
		out += weights[i] * input->at(i);
	}
	return out;
}
