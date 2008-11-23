#include "core/operators/sceneoperator.hpp"

#include "core/core.hpp"

void SceneOperator::cascadeProcess(int tick)
{
    for (int i = 0; i < numberOfClips; i++)
    {
        Clip* clip = clips[timelineClips[i]];

        if (clip->start <= tick && clip->end > tick)
            broadcastChannelValue(clip->channel, clip->getValue(tick - clip->start));
    }

    for (int i = 0; i < numberOfInputs; i++)
        operators[inputs[i]]->cascadeProcess(tick);
}

void SceneOperator::render()
{
    for (int i = 0; i < numberOfInputs; i++)
        getInput(0)->render();
}

void SceneOperator::process()
{

}
