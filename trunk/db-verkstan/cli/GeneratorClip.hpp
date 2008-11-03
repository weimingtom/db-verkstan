#pragma once

#include "cli/Clip.hpp"
#include "cli/Constants.hpp"

using namespace System;

namespace Verkstan
{
    public ref class GeneratorClip: public Clip
    {
    public:
        GeneratorClip();
        ~GeneratorClip();
        property int Period
        {
            int get();
            void set(int period);
        }
        property Constants::GeneratorClipTypes Type
        {
            Constants::GeneratorClipTypes get();
            void set(Constants::GeneratorClipTypes type);
        }
    };
}