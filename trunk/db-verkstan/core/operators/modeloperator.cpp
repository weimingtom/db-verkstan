#include "core/operators/modeloperator.hpp"

void ModelOperator::render(int tick)
{
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
    getInput(0)->mesh->render();
}

void ModelOperator::process()
{
    
}
