#pragma once

#include "operator.hpp"

/**
 * Generates random pixels.
 *
 * @int 0 color
 * @int 1 count
 * @int 2 seed
 */
class PixelsOperator: public Operator
{
public:
    void process();
};