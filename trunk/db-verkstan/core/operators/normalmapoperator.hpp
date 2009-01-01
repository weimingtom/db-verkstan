#pragma once

#include "core/operator.hpp"

class NormalMapOperator: public Operator
{
public:
    NormalMapOperator();
    void process();
    Texture* normalMapTexture;
#ifdef DB_EDITOR
    void deviceLost();
#endif
};