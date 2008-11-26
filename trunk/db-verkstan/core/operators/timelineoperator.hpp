#pragma once

#include "core/operator.hpp"

class TimelineOperator: public Operator
{
public:
    TimelineOperator();
    void process();
    void render(int tick);
    int startTick;
    void broadcastChannelValue(int channel, float value);
};