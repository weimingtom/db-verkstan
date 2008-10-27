#include "core/operators/lightoperator.hpp"

void LightOperator::render()
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
  
    d3dLight.Diffuse.r = getByteProperty(1) / 256.0f;
    d3dLight.Diffuse.g = getByteProperty(2) / 256.0f;
    d3dLight.Diffuse.b = getByteProperty(3) / 256.0f;
    d3dLight.Diffuse.a = 1.0f;

    d3dLight.Specular.r = getByteProperty(4) / 256.0f;
    d3dLight.Specular.g = getByteProperty(5) / 256.0f;
    d3dLight.Specular.b = getByteProperty(6) / 256.0f;
    d3dLight.Specular.a = 1.0f;

    d3dLight.Ambient.r = getByteProperty(7) / 256.0f;
    d3dLight.Ambient.g = getByteProperty(8) / 256.0f;
    d3dLight.Ambient.b = getByteProperty(9) / 256.0f;
    d3dLight.Ambient.a = 1.0f;

    D3DVECTOR position;
    position.x = getFloatProperty(10);
    position.y = getFloatProperty(11);
    position.z = getFloatProperty(12);
    d3dLight.Position = position;

    D3DVECTOR direction;
    direction.x = getFloatProperty(13);
    direction.y = getFloatProperty(14);
    direction.z = getFloatProperty(15);
    d3dLight.Direction = direction;

    d3dLight.Range = getFloatProperty(16);
    d3dLight.Falloff = getFloatProperty(17);
    d3dLight.Attenuation0 = getFloatProperty(18);
    d3dLight.Attenuation1 = getFloatProperty(19);
    d3dLight.Attenuation2 = getFloatProperty(20);
    d3dLight.Theta = getFloatProperty(21);
    d3dLight.Phi = getFloatProperty(22);
}
