#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

#include "cli/VerkstanCore.hpp"

#include "cli/Timer.hpp"

namespace Verkstan
{
    int Timer::GetBeat()
    {
        if (!ticking)
            return lastBeat;


        int diff = GetTickCount() - startTickCount;
        lastBeat = (int)((diff * (BPM / 60000.0f)) * DB_TICKS_PER_BEAT);
        return lastBeat;
    }

    void Timer::Start()
    {
        if (ticking)
        {
            Pause();
            return;
        }
        startTickCount = GetTickCount() - (stopTickCount - startTickCount);
        ticking = true;
    }

    void Timer::Pause()
    {
        ticking = false;
        stopTickCount = GetTickCount();
    }

    void Timer::SetBeat(int beat)
    {
         float b = beat / (float)DB_TICKS_PER_BEAT;
         int m = (int)(b*BPM*60000);
         startTickCount = GetTickCount() - m;
         stopTickCount = startTickCount;
         lastBeat = beat;
    }

    int Timer::GetTicksPerBeat()
    {
        return DB_TICKS_PER_BEAT;
    }

    int Timer::GetMilliseconds()
    {
        float b = GetBeat() / (float)DB_TICKS_PER_BEAT;
        return (int)(b / BPM * 60000);
    }
}