#include "core/operators/transformmodeloperator.hpp"

void TransformModelOperator::render()
{
    globalWorldMatrixStack->Push();
    globalWorldMatrixStack->TranslateLocal(getFloatProperty(6),
                                  getFloatProperty(7),
                                  getFloatProperty(8));
    globalWorldMatrixStack->RotateAxisLocal(&Vec3(1.0f, 0.0f, 0.0f),
                                       getFloatProperty(3));
    globalWorldMatrixStack->RotateAxisLocal(&Vec3(0.0f, 1.0f, 0.0f),
                                       getFloatProperty(4));
    globalWorldMatrixStack->RotateAxisLocal(&Vec3(0.0f, 0.0f, 1.0f),
                                       getFloatProperty(5));
    globalWorldMatrixStack->ScaleLocal(getFloatProperty(0),
                                  getFloatProperty(1),
                                  getFloatProperty(2));

    getInput(0)->render();
    globalWorldMatrixStack->Pop();
}

void TransformModelOperator::process()
{
}
