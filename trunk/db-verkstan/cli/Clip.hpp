#pragma once

#include "cli/internal/VerkstanCore.hpp"

using namespace System;

namespace Verkstan
{
    public ref class Clip
    {
    public:
        Clip();
        virtual ~Clip();
        property int Id
        {
            int get();
        }
        property int Start
        {
            int get();
            void set(int value);
        }
        property int End
        {
            int get();
            void set(int value);
        }
        property int Channel
        {
            int get();
            void set(int value);
        }

        Core::Clip* getClip();
        float GetValue(int beat);
    
    protected:
        int id;
    };
}
