#pragma once

using namespace System;

namespace Verkstan
{
    ref class Clip;

    public ref class ClipFactory
    {
    public:
        static Clip^ Create(String^ name);
    };
}