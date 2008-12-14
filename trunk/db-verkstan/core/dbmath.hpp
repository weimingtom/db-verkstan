#pragma once

extern "C"
{
    float sin(float x);
    float cos(float x);
    float sqrt(float x);
    float pow(float x, float y);
    float powf(float x, float y);
    float log(float x);
    float fmodf(float x, float y);
    float tanhf(float v);
    float fabsf(float v);
    float fabs(float v);
    float __max(float v1, float v2);
    float abs(float v);
}