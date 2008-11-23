#pragma once

#include "core/operator.hpp"

class SceneOperator: public Operator
{
public:
    void cascadeProcess(int tick);
    void process();
    void render();
};