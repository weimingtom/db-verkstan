#pragma once

class Filter {
public:
	Filter() :
	  buf0(0.0f), buf1(0.0f)
	{}

	void process(float *buffer, int length, float f, float q);

private:
	float buf0, buf1;
};