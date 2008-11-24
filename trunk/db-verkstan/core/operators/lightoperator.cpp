#include "core/operators/lightoperator.hpp"

void LightOperator::render(int tick)
{
    globalDirect3DDevice->SetLight(0, &d3dLight); 
    globalDirect3DDevice->LightEnable(0, TRUE); 
}

void LightOperator::process()
{
    ZeroMemory(&d3dLight, sizeof(d3dLight));
    unsigned char type = getByteProperty(0);

    switch (type)
    {
    case 0:
        d3dLight.Type = D3DLIGHT_POINT;
        break;
    case 1:
        d3dLight.Type = D3DLIGHT_SPOT;
        break;
    case 2:
        d3dLight.Type = D3DLIGHT_DIRECTIONAL;
        break;
    }
  
    d3dLight.Diffuse = getColorProperty(1);
    d3dLight.Specular = getColorProperty(2);
    d3dLight.Ambient = getColorProperty(3);
    d3dLight.Position = getVectorProperty(4);
    d3dLight.Direction = getVectorProperty(5);
    d3dLight.Range = getFloatProperty(6);
    d3dLight.Falloff = getFloatProperty(7);
    d3dLight.Attenuation0 = getFloatProperty(8);
    d3dLight.Attenuation1 = getFloatProperty(9);
    d3dLight.Attenuation2 = getFloatProperty(10);
    d3dLight.Theta = getFloatProperty(11);
    d3dLight.Phi = getFloatProperty(12);
}
