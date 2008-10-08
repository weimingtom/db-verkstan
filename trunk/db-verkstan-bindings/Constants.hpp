#pragma once

using namespace System;

namespace VerkstanBindings
{
    public ref class Constants
    {
    public:
        enum class OperatorCategories
        {
            Texture,
            Mesh,
            Model,
            Scene,
            Misc
        };

        enum class OperatorTypes
        {
            Texture,
            Mesh,
            Model,
            Camera,
            Scene
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
