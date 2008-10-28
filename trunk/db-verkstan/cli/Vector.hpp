#pragma once

using namespace System;

namespace Verkstan
{
    public ref struct Vector
    {
    public:
        Vector();
        Vector(float x, float y, float z);
        Vector(float x, float y, float z, float w);
        float X;
        float Y;
        float Z;
        float W;
    };
}