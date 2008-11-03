#include "core/generatorclip.hpp"
#include "core/core.hpp"

#include <math.h>

float GeneratorClip::getValue(int beat)
{
    switch (type)
    {
    case 0:
        return sinf((beat / (float)period) * D3DX_PI * 2.0f);
    case 1:
        return cosf((beat / (float)period) * D3DX_PI * 2.0f);
    case 2: // Ramp up
        return (beat % period) / (float)period;
    case 3: // Ramp down
        return (1.0f - (beat % period)) / (float)period;
    }
}
