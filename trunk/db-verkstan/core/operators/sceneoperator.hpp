#pragma once

#include "core/operator.hpp"

class SceneOperator: public Operator
{
public:
    void cascadeProcess();
    void process();
    void render();
};