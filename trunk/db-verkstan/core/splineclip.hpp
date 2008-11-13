#pragma once

#include "core/clip.hpp"

class SplineClip: public Clip
{
public:
    float getValue(int tick);
};