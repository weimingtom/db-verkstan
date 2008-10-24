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
            Scene,
            Demo,
            Load,
            Store
        };

       enum class OperatorPropertyTypes
       {
            Byte,
            Int,
            Float,
            Color,
            String,
            Text,
            Vector
       };
    };
}
