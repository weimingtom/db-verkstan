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
        void SetNumberOfControlPoints(int number);
        int GetNumberOfControlPoints();
        void SetControlPoint(int index, int tick, float value);
        int GetControlPointTick(int index);
        float GetControlPointValue(int index);
        void SetSplineType(int type);
        int GetSplineType();

    private:
        Core::SplineClip* coreSplineClip;
        int id;
    };
}