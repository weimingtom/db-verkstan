#pragma once

using namespace System;

namespace Verkstan
{
    public ref class Metronome
    {
    public:
        static int BPM = 120;
        static bool Loop = false;
        static property int Beat
        {
            int get();
            void set(int beat);
        }
        static property int Beats
        {
            int get();
            void set(int beats);
        }
        static property int TicksPerBeat
        {
            int get();
        }
        static property int Milliseconds
        {
            int get();
        }

        static void Start();
        static void Pause();

    private:
        static bool ticking = false;
        static int beat = 0;
        static int beats = 10240;
        static int lastTickCount = 0;
        static float leftOvers = 0.0f;
    };
}