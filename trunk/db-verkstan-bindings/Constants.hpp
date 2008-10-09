#pragma once

using namespace System;

namespace VerkstanBindings
{
    public ref class Constants
    {
    public:
        enum class OperatorTypes
        {
            Texture,
            Mesh,
            Model,
            Camera,
            Scene,
            Reference,
            Name
        };

       enum class OperatorPropertyTypes
       {
            Byte,
            Int,
            Float,
            Color,
            String,
            Text
       };
    };
}
