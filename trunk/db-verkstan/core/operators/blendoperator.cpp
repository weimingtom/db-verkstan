#include "core/operators/blendoperator.hpp"

void BlendOperator::process()
{
    if (texture == 0)
       texture = new Texture();

    texture->lock();
    for (int i = 0; i < numberOfInputs; i++)
    getInput(i)->texture->lock();

    float a = 1.0f / numberOfInputs;
    
    DWORD* pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            float r = 0;
            float g = 0;
            float b = 0;

            for (int i = 0; i < numberOfInputs; i++)
            {
                 DWORD* srcPixels = (DWORD*)getInput(i)->texture->d3d9LockedRect.pBits;
                 D3DCOLOR c = srcPixels[x + y * pitch];
                 r += D3DCOLOR_R(c) * a;
                 g += D3DCOLOR_G(c) * a;
                 b += D3DCOLOR_B(c) * a;
            }
            
            int ri = (int)r;
            int gi = (int)g;
            int bi = (int)b;
            ri = ri > 255 ? 255 : ri;
            gi = gi > 255 ? 255 : gi;
            bi = bi > 255 ? 255 : bi;

            pixels[x + y * pitch] = D3DCOLOR_XRGB(ri, gi, bi);
        }
    }

    texture->unlock();
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->texture->unlock();
}
