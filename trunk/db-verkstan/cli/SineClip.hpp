#pragma once

#include "cli/Clip.hpp"

using namespace System;

namespace Verkstan
{
    public ref class SineClip: public Clip
    {
    public:
        SineClip(int clipid);
        ~SineClip();
    };
}