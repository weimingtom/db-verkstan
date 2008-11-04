#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

#include "cli/internal/VerkstanCore.hpp"

#include "cli/Metronome.hpp"

namespace Verkstan
{
    int Metronome::Beat::get()
    {
        if (!ticking)
            return beat;
    
        int currentTick = GetTickCount();
        int ms = currentTick - lastTickCount;
        int tpm = BPM * DB_TICKS_PER_BEAT;
        float tps = tpm / 60.0f;
        float tpms = tps / 1000.0f;

        int beatAddition = (int)(tpms * ms) + (int)leftOvers;
        beat += beatAddition;
        leftOvers -= (int)leftOvers;
        leftOvers +=  (tpms * ms) - (int)(tpms * ms);

        lastTickCount = currentTick;

        if (Loop && beat > loopEnd)
        {
            beat = loopStart;
        }
        else if (beat > beats)
        {
            beat = beats;
            ticking = false;
        }

        return beat;
    }

    void Metronome::Beat::set(int newBeat)
    {
        beat = newBeat;
        lastTickCount = GetTickCount();
        leftOvers = 0.0f;

        if (beat > beats)
            beat = beats;

        if (beat < 0)
            beat = 0;
    }

    int Metronome::Beats::get()
    {
        return beats;
    }

    void Metronome::Beats::set(int newBeats)
    {
        beats = newBeats;

        if (beat > beats)
        {
            beat = beats;
            ticking = Loop;
        }

        if (loopStart > beats)
            loopStart = beats;
        if (loopEnd > beats)
            loopEnd = beats;
    }

    int Metronome::LoopStart::get()
    {
        return loopStart;
    }

    void Metronome::LoopStart::set(int newLoopStart)
    {
        loopStart = newLoopStart;

        if (loopStart < 0)
            loopStart = 0;
        if (loopStart > beats)
            loopStart = beats;
    }

    int Metronome::LoopEnd::get()
    {
        return loopEnd;
    }

    void Metronome::LoopEnd::set(int newLoopEnd)
    {
        loopEnd = newLoopEnd;

        if (loopEnd < 0)
            loopEnd = 0;
        if (loopEnd > beats)
            loopEnd = beats;
    }

    int Metronome::Milliseconds::get()
    {
        float b = Beat::get() / (float)DB_TICKS_PER_BEAT;
        return (int)(b / BPM * 60000);
    }

    void Metronome::Start()
    {
        ticking = true;
        lastTickCount = GetTickCount();
    }

    void Metronome::Pause()
    {
        ticking = false;
    }


    int Metronome::TicksPerBeat::get()
    {
        return DB_TICKS_PER_BEAT;
    }
}