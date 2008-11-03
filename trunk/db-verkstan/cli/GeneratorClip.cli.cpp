#include "cli/internal/VerkstanCore.hpp"
#include "cli/GeneratorClip.hpp"

namespace Verkstan
{
    GeneratorClip::GeneratorClip()
    {
        Core::Clip* clip = new Core::GeneratorClip();
        for (int i = 0; i < DB_MAX_CLIPS; i++)
        {   
            if (clips[i] == 0)
            {
                clips[i] = clip;
                id = i;
                break;
            }
        }
    }

    GeneratorClip::~GeneratorClip()
    {
       
    }

    int GeneratorClip::Period::get()
    {
        return ((Core::GeneratorClip*)getClip())->period;
    }

    void GeneratorClip::Period::set(int newPeriod)
    {
        ((Core::GeneratorClip*)getClip())->period = newPeriod;
    }

    Constants::GeneratorClipTypes GeneratorClip::Type::get()
    {
        int type = ((Core::GeneratorClip*)getClip())->type;
        switch (type)
        {
        case 0:
            return Constants::GeneratorClipTypes::Sine;
        case 1:
            return Constants::GeneratorClipTypes::Cosine;
        case 2:
            return Constants::GeneratorClipTypes::RampUp;
        case 3:
            return Constants::GeneratorClipTypes::RampDown;
        case 4:
            return Constants::GeneratorClipTypes::SawTooth;
        case 5:
            return Constants::GeneratorClipTypes::Incrementor;
        case 6:
            return Constants::GeneratorClipTypes::Decrementor;
        }
    }

    void GeneratorClip::Type::set(Constants::GeneratorClipTypes type)
    {
        int newType;
        switch (type)
        {
        case Constants::GeneratorClipTypes::Sine:
            newType = 0;
            break;
        case Constants::GeneratorClipTypes::Cosine:
            newType = 1;
            break;
        case Constants::GeneratorClipTypes::RampUp:
            newType = 2;
            break;
        case Constants::GeneratorClipTypes::RampDown:
            newType = 3;
            break;
        case Constants::GeneratorClipTypes::SawTooth:
            newType = 4;
            break;
        case Constants::GeneratorClipTypes::Incrementor:
            newType = 5;
            break;
        case Constants::GeneratorClipTypes::Decrementor:
            newType = 6;
            break;
        }

        ((Core::GeneratorClip*)getClip())->type = newType;
    }
}