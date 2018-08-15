#pragma once

#include <random>
#include <vector>
#include <functional>
#include <cmath>
#include <time.h>
#include <functional>


using namespace std;

class NetworkInput {
public:

	NetworkInput(size_t w, size_t h) :
		width(w),
		height(h),
		inputs(w*h) {}

	double at(int i) const { return inputs[i]; }
	double & at(int i) { return inputs[i]; }

	double at(int x, int y) const { return inputs[x + y*width]; }
	double & at(int x, int y) { return inputs[x + y * width]; }

	vector<double> inputs;

	size_t width;
	size_t height;
};

//general neuron network class
class Network
{
public:

	Network(NetworkInput * input):
		input(input),
		w(input->width),
		h(input->height),
		weights(w * h) {}

	void get_rand() {
		
		random_device rnd_device;		
		mt19937 mersenne_engine{ rnd_device() }; 
		uniform_real<double> dist{ -1, 1 };

		auto gen = [&dist, &mersenne_engine]() {
			return dist(mersenne_engine);
		};

		generate(begin(weights), end(weights), gen);
	}

	double calc() const;

protected:
	size_t w;
	size_t h;

	std::function<double(double)> func = [](double x) {return (exp(2 * x) - 1) / (exp(2 * x) + 1); };
	NetworkInput * input;

	vector<double> weights;
};

