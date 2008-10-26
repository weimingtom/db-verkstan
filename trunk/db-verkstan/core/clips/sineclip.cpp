#include "core/clips/sineclip.hpp"
#include "core/core.hpp"

#include <math.h>

float SineClip::getValue(int beat)
{
    return sinf(beat / (float) DB_TICKS_PER_BEAT);
}
