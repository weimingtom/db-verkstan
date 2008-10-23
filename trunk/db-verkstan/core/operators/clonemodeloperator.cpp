#include "core/operators/clonemodeloperator.hpp"

void CloneModelOperator::render()
{
    unsigned char clones = getByteProperty(0);
    float scalex = getFloatProperty(1);
    float scaley = getFloatProperty(2);
    float scalez = getFloatProperty(3);
    float rotationx = getFloatProperty(4);
    float rotationy = getFloatProperty(5);
    float rotationz = getFloatProperty(6);
    float translationx = getFloatProperty(7);
    float translationy = getFloatProperty(8);
    float translationz = getFloatProperty(9);
    globalWorldMatrixStack->Push();

    getInput(0)->render();

    for (int i = 1; i < clones; i++)
    {
        globalWorldMatrixStack->Translate(translationx, translationy, translationz);
        globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f), rotationx);
        globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), rotationy);
        globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), rotationz);
        globalWorldMatrixStack->Scale(scalex, scaley, scalez);
       
        getInput(0)->render();
    }

    globalWorldMatrixStack->Pop();
}

void CloneModelOperator::process()
{
   
}
