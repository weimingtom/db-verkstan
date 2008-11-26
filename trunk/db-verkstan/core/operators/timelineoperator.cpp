#include "core/operators/timelineoperator.hpp"

#include "core/core.hpp"

TimelineOperator::TimelineOperator()
:startTick(-1)
{

}

void TimelineOperator::render(int tick)
{
    if (getByteProperty(0) <= 0)
    {
        startTick = -1;
        return;
    }

    if (startTick == -1)
        startTick = tick;

    int relativeTick = tick % (ticks + 1);

    for (int i = 0; i < numberOfClips; i++)
    {
        Clip* clip = clips[timelineClips[i]];

        if (clip->start <= relativeTick && clip->end > relativeTick)
            Operator::broadcastChannelValue(clip->channel, clip->getValue(relativeTick - clip->start));
    }

    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render(relativeTick);
}

void TimelineOperator::process()
{

}

void TimelineOperator::broadcastChannelValue(int channel, float value)
{
    for (int i = 0; i < numberOfClips; i++)
        if (clips[timelineClips[i]]->channel == channel)
            return;

    Operator::broadcastChannelValue(channel, value);
}
