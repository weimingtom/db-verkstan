#pragma once

#include "core/operator.hpp"

class CameraOperator: public Operator
{
public:
    void process();
    void render();
};