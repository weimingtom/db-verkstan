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
            Renderable,
            Load,
            Store,
            Unspecified
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
    };
}
