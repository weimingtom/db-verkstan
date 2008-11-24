#include "core/operators/addmodelsoperator.hpp"

void AddModelsOperator::render(int tick)
{
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render(tick);
}

void AddModelsOperator::process()
{
   
}
