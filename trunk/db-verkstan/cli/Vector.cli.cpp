#include "cli/Vector.hpp"

namespace Verkstan
{
    Vector::Vector()
        :X(0.0f), Y(0.0f), Z(0.0f), W(0.0f)
    {

    }

    Vector::Vector(float x, float y, float z)
         :X(x), Y(y), Z(z), W(0.0f)
    {

    }

    Vector::Vector(float x, float y, float z, float w)
         :X(x), Y(y), Z(z), W(w)
    {

    }
}