#pragma once

#include "core/operator.hpp"

class SceneOperator: public Operator
{
public:
    SceneOperator();
    void cascadeProcess(int tick);
    void process();
    void render();
    int startTick;
};