#pragma once

#include "cli/CoreClip.hpp"
#include "cli/Constants.hpp"

using namespace System;

namespace Verkstan
{
    public ref class CoreSplineClip: public CoreClip
    {
    public:
        CoreSplineClip();
        ~CoreSplineClip();
        property int Id
        {
            int get();
        }

    private:
        Core::SplineClip* coreSplineClip;
        int id;
    };
}