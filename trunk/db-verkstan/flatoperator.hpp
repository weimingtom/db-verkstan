#pragma once

#include "operator.hpp"

/**
 * Generates a flat texture.
 *
 * @int 0 color
 */
class FlatOperator: public Operator
{
public:
    void process();
};