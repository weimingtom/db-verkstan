#include "core/operators/sceneoperator.hpp"

void SceneOperator::render()
{
    for (int i = 0; i < numberOfInputs; i++)
        getInput(0)->render();
}

void SceneOperator::process()
{

}
