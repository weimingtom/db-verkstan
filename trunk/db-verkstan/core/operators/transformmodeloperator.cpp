#include "core/operators/transformmodeloperator.hpp"

void TransformModelOperator::render()
{
    globalWorldMatrixStack->Push();
    globalWorldMatrixStack->Translate(getFloatProperty(6),
                                  getFloatProperty(7),
                                  getFloatProperty(8));
    globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f),
                                       getFloatProperty(3));
    globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f),
                                       getFloatProperty(4));
    globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f),
                                       getFloatProperty(5));
    globalWorldMatrixStack->Scale(getFloatProperty(0),
                                  getFloatProperty(1),
                                  getFloatProperty(2));

    getInput(0)->render();
    globalWorldMatrixStack->Pop();
}

void TransformModelOperator::process()
{
}
