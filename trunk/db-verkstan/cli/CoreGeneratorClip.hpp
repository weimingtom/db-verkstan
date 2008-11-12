#pragma once

#include "cli/Core.hpp"
#include "cli/Constants.hpp"

using namespace System;

namespace Verkstan
{
    public ref class CoreGeneratorClip
    {
    public:
        CoreGeneratorClip();
        ~CoreGeneratorClip();
        property int Id
        {
            int get();
        }

        int GetPeriod();
        void SetPeriod(int period);
        Constants::GeneratorClipTypes GetType();
        void SetType(Constants::GeneratorClipTypes type);

    private:
        Core::GeneratorClip* coreGeneratorClip;
        int id;
    };
}