#include "core/operators/sceneoperator.hpp"

#include "core/core.hpp"

SceneOperator::SceneOperator()
:startTick(0)
{

}
void SceneOperator::cascadeProcess(int tick)
{
    if (getByteProperty(0) <= 0)
    {
        startTick = -1;
        return;
    }

    if (startTick == -1)
        startTick = tick;

    int relativeTick = (tick - startTick + getIntProperty(1) % ticks;

    for (int i = 0; i < numberOfClips; i++)
    {
        Clip* clip = clips[timelineClips[i]];

        if (clip->start <= relativeTick && clip->end > relativeTick)
            broadcastChannelValue(clip->channel, clip->getValue(relativeTick - clip->start));
    }

    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->cascadeProcess(relativeTick);
}

void SceneOperator::render()
{
    if (getByteProperty(0) <= 0)
        return;

    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render();
}

void SceneOperator::process()
{

}
