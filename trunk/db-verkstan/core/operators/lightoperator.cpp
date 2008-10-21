#include "core/operators/lightoperator.hpp"

void LightOperator::render()
{
    globalDirect3DDevice->SetLight(0, &d3dLight); 
    globalDirect3DDevice->LightEnable(0, TRUE); 
}

void LightOperator::process()
{
    ZeroMemory(&d3dLight, sizeof(d3dLight));
    d3dLight.Type = D3DLIGHT_DIRECTIONAL;
  
    d3dLight.Diffuse.r = getByteProperty(0) / 256.0f;
    d3dLight.Diffuse.g = getByteProperty(1) / 256.0f;
    d3dLight.Diffuse.b = getByteProperty(2) / 256.0f;
    d3dLight.Diffuse.a = 1.0f;

    D3DVECTOR position;
    position.x = getFloatProperty(3);
    position.y = getFloatProperty(4);
    position.z = getFloatProperty(5);
    d3dLight.Position = position;

    D3DVECTOR direction;
    direction.x = getFloatProperty(6);
    direction.y = getFloatProperty(7);
    direction.z = getFloatProperty(8);
    d3dLight.Direction = direction;
}
