#pragma once

class Clip
{
public:
    virtual float getValue(int beat) = 0;
    int start;
    int end;
    int channel;
};