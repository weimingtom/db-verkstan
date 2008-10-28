#include "core/operators/sceneoperator.hpp"

#include "core/core.hpp"

void SceneOperator::cascadeProcess()
{
    for (int i = 0; i < numberOfClips; i++)
    {
        Clip* clip = clips[operatorClips[i]];

        if (clip->start <= beat && clip->end > beat)
            broadcastChannelValue(clip->channel, clip->getValue(beat), 2, 2, 2);
    }

    Operator::cascadeProcess();
}

void SceneOperator::render()
{
    for (int i = 0; i < numberOfInputs; i++)
        getInput(0)->render();
}

void SceneOperator::process()
{

}
