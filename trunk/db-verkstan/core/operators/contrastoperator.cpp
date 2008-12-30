#include "core/operators/contrastoperator.hpp"

void ContrastOperator::process()
{
    if (texture == 0)
       texture = new Texture();

    Texture* srcTexture = getInput(0)->texture;
    texture->lock();
    srcTexture->lock();
    DWORD* destPixels = (DWORD*)texture->d3d9LockedRect.pBits;
    DWORD* srcPixels = (DWORD*)srcTexture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    float contrast = powf((getByteProperty(0) / 128.0f), 3.0f);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            D3DCOLOR srcColor = srcPixels[x + y * pitch];
            int r = (int)((D3DCOLOR_R(srcColor) - 128.0f) * contrast + 128.0f);
            int g = (int)((D3DCOLOR_G(srcColor) - 128.0f) * contrast + 128.0f);
            int b = (int)((D3DCOLOR_B(srcColor) - 128.0f) * contrast + 128.0f);
            
            if (r < 0)
                r = 0;
            if (r > 255)
                r = 255;
            if (g < 0)
                g = 0;
            if (g > 255)
                g = 255;
            if (b < 0)
                b = 0;
            if (b > 255)
                b = 255;
            destPixels[x + y * pitch] = D3DCOLOR_XRGB(r, g, b);
        }
    }

    texture->unlock();
    srcTexture->unlock();
}
