#pragma once

#include "core/operator.hpp"

class TextureMappingOperator: public Operator
{
public:
    void process();
    void render(int tick);
};