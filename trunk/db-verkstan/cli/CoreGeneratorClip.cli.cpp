#include "cli/CoreGeneratorClip.hpp"

namespace Verkstan
{
    CoreGeneratorClip::CoreGeneratorClip()
    {
        coreGeneratorClip = new Core::GeneratorClip();
        for (int i = 0; i < DB_MAX_CLIPS; i++)
        {   
            if (Core::clips[i] == 0)
            {
                Core::clips[i] = coreGeneratorClip;
                id = i;
                break;
            }
        }
    }

    CoreGeneratorClip::~CoreGeneratorClip()
    {
       Core::clips[id] = 0;
       delete coreGeneratorClip;
    }

    int CoreGeneratorClip::Id::get()
    {
        return id;
    }

    int CoreGeneratorClip::GetPeriod()
    {
        return coreGeneratorClip->period;
    }

    void CoreGeneratorClip::SetPeriod(int newPeriod)
    {
        coreGeneratorClip->period = newPeriod;
    }

    Constants::GeneratorClipTypes CoreGeneratorClip::GetType()
    {
        int type = coreGeneratorClip->type;
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
        }
    }

    void CoreGeneratorClip::SetType(Constants::GeneratorClipTypes type)
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
        }

        coreGeneratorClip->type = newType;
    }
}