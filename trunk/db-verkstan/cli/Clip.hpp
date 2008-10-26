#pragma once

#include "cli/VerkstanCore.hpp"

using namespace System;

namespace Verkstan
{
    public ref class Clip
    {
    public:
        Clip(int clipid);
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
    
    private:
        int id;
    };
}
