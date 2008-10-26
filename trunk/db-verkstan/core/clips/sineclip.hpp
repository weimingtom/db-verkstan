#pragma once

#include "core/clip.hpp"

class SineClip: public Clip
{
public:
    float getValue(int beat);
};