#pragma once

#include "core/operator.hpp"

class BlurOperator: public Operator
{
public:
    void process();
    void blur(DWORD* inPixels, DWORD* outPixels, int inPitch, int outPitch, int radius);
};