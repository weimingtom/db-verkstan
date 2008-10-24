#include "core/operators/demooperator.hpp"

void DemoOperator::render()
{
   for (int i = 0; i < numberOfInputs; i++)
        getInput(0)->render();
}

void DemoOperator::process()
{
   
}
