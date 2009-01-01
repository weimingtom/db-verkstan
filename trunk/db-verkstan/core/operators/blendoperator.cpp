#include "core/operators/blendoperator.hpp"

void BlendOperator::process()
{
    if (texture == 0)
       texture = new Texture();

    Operator* inputToBlend1 = getInput(0);
    Operator* inputToBlend2 = getInput(1);
    Operator* inputAlpha = getInput(2);

    texture->lock();
    inputToBlend1->texture->lock();
    inputToBlend2->texture->lock();
    inputAlpha->texture->lock();

    DWORD* dstPixels = (DWORD*)texture->d3d9LockedRect.pBits;
    DWORD* src1Pixels = (DWORD*)inputToBlend1->texture->d3d9LockedRect.pBits;
    DWORD* src2Pixels = (DWORD*)inputToBlend2->texture->d3d9LockedRect.pBits;
    DWORD* alphaPixels = (DWORD*)inputAlpha->texture->d3d9LockedRect.pBits;
 
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            float a = D3DCOLOR_R(alphaPixels[x + y * pitch]) / 255.0f;
            float oneMinusA = 1.0f - a;
            D3DCOLOR c1 = src1Pixels[x + y * pitch];
            D3DCOLOR c2 = src2Pixels[x + y * pitch];

            float r = D3DCOLOR_R(c1) * a + D3DCOLOR_R(c2) * oneMinusA;
            float g = D3DCOLOR_G(c1) * a + D3DCOLOR_G(c2) * oneMinusA;
            float b = D3DCOLOR_B(c1) * a + D3DCOLOR_B(c2) * oneMinusA;
           
            dstPixels[x + y * pitch] = D3DCOLOR_XRGB((int)r, (int)g, (int)b);
        }
    }

    texture->unlock();
    inputToBlend1->texture->unlock();
    inputToBlend2->texture->unlock();
    inputAlpha->texture->unlock();
}
