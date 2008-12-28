#include "core/operators/normalmapoperator.hpp"

void NormalMapOperator::process()
{
    if (texture != 0)
        delete texture;
    texture = new Texture();

    D3DXComputeNormalMap(texture->getD3D9Texture(),
                         getInput(0)->texture->getD3D9Texture(),
                         NULL,
                         0,
                         D3DX_CHANNEL_RED,
                         getByteProperty(0));
}
