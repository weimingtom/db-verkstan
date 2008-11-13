#include "cli/CoreSplineClip.hpp"

namespace Verkstan
{
    CoreSplineClip::CoreSplineClip()
    {
        coreSplineClip = new Core::SplineClip();
        for (int i = 0; i < DB_MAX_CLIPS; i++)
        {   
            if (Core::clips[i] == 0)
            {
                Core::clips[i] = coreSplineClip;
                id = i;
                break;
            }
        }

        SetCoreClip(coreSplineClip);
    }

    CoreSplineClip::~CoreSplineClip()
    {
       Core::clips[id] = 0;
       delete coreSplineClip;
    }

    int CoreSplineClip::Id::get()
    {
        return id;
    }
}