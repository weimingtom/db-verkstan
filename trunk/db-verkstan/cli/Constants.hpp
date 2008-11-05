#pragma once

using namespace System;

namespace Verkstan
{
    public ref class Constants
    {
    public:
        enum class OperatorTypes
        {
            Texture,
            Mesh,
            Model,
            Renderer,
            Load,
            Store,
            Unspecified,
            Scene
        };

       enum class OperatorPropertyTypes
       {
            Byte,
            Int,
            Float,
            Color,
            String,
            Text,
            Vector,
            Enum
       };

       enum class GeneratorClipTypes
       {
            Sine,
            Cosine,
            RampUp,
            RampDown,
            SawTooth
       };
    };
}
