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
            Camera,
            Scene,
            Load,
            Store,
            Core
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