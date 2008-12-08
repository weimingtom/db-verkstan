#pragma once

#include "core/operator.hpp"

class CloudsOperator: public Operator
{
public:
    void process();
    float noise(int x, int y);
    float interpolate(float x, float y, float t);
    float smooth(float x, float y);
    int r1;
    int r2;
    int r3;
    int pitch;
    DWORD* pixels;
    D3DXCOLOR color1;
    D3DXCOLOR color2;
    void divideGrid(int x, int y, int width, int height, float c1, float c2, float c3, float c4, int scale);
};