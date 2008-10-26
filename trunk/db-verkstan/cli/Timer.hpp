#pragma once

using namespace System;

namespace Verkstan
{
    public ref class Timer
    {
    public:
        static int BPM = 120;
        static int GetBeat();
        static void Start();
        static void Pause();
        static void SetBeat(int beat);
        static int GetTicksPerBeat();
        static int GetMilliseconds();

    private:
        static bool ticking = false;
        static int startTickCount = 0;
        static int stopTickCount = 0;
        static int lastBeat = 0;
    };
}