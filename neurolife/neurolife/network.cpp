#include <algorithm>
#include <numeric>

#include "network.h"


double Network::calc() const
{
	double out = 0;
	for (int i = 0; i < w*h; ++i) {
		out += weights[i] * input->at(i);
	}
	return out;
}

NetworkInput::NetworkInput(size_t w, size_t h) :
	width(w),
	height(h),
	inputs(w*h, 0) {
}

void NetworkInput::norm()
{
	length = accumulate(inputs.begin(), inputs.end(), 0, [](double x, double y) {return x * x + y*y; });

	for (auto& el : inputs) {
		el /= length;
	}

}
