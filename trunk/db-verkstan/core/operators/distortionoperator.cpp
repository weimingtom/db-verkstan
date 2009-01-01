#include "core/operators/distortionoperator.hpp"

void DistortionOperator::process()
{
    if (texture == 0)
       texture = new Texture();

    unsigned char mode = getByteProperty(0);
    float amount = getByteProperty(1) / 255.0f;

    Operator* inputToDistort = getInput(0);
    Operator* inputHowToDistort = getInput(1);
 
    texture->lock();
    inputToDistort->texture->lock();
    inputHowToDistort->texture->lock();
    DWORD* mapPixels = (DWORD*)inputHowToDistort->texture->d3d9LockedRect.pBits;
    DWORD* dstPixels = (DWORD*)texture->d3d9LockedRect.pBits;
    DWORD* srcPixels = (DWORD*)inputToDistort->texture->d3d9LockedRect.pBits;

    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            D3DCOLOR c = mapPixels[pitch * y + x];
            
            Vec3 normal;
            if (mode == 0)
                normal = Vec3(D3DCOLOR_G(c) - 127.0f, D3DCOLOR_B(c) - 127.0f, 1.0f);
            else if (mode == 1)
                normal = Vec3(D3DCOLOR_R(c) - 127.0f, D3DCOLOR_G(c) - 127.0f, D3DCOLOR_B(c) - 127.0f);

            normalize(normal);

            float u = fmodf(normal.x * amount + x, 255.0f);
            float v = fmodf(normal.y * amount + y, 255.0f);

            // Fractions
            float uf = u >= 0.0f ? (u - (int)u) : 1.0f + (u - (int)u);
            float vf = v >= 0.0f ? (v - (int)v) : 1.0f + (v - (int)v);
            // Pixel
            int ut = u >= 0.0f ? (int)u : (int)u - 1;
            int vt = v >= 0.0f ? (int)v : (int)v - 1;

            int r = 0;
            int g = 0;
            int b = 0;

            float weight = (1.0f - uf) * (1.0f - vf);
            int u1 = (ut + 2560) % 256;
            int v1 = (vt + 2560) % 256;
            r += (int)(D3DCOLOR_R(srcPixels[pitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[pitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[pitch * v1 + u1]) * weight);

            weight = uf * (1.0f - vf);
            u1 = (ut + 2561) % 256;
            v1 = (vt + 2560) % 256;
            r += (int)(D3DCOLOR_R(srcPixels[pitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[pitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[pitch * v1 + u1]) * weight);

            weight = (1.0f - uf) * vf;
            u1 = (ut + 2560) % 256;
            v1 = (vt + 2561) % 256;
            r += (int)(D3DCOLOR_R(srcPixels[pitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[pitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[pitch * v1 + u1]) * weight);

            weight = uf * vf;
            u1 = (ut + 2561) % 256;
            v1 = (vt + 2561) % 256;
            r += (int)(D3DCOLOR_R(srcPixels[pitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[pitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[pitch * v1 + u1]) * weight);

            dstPixels[pitch * y + x] = D3DCOLOR_XRGB(r, g, b);
        }
    }

    texture->unlock();
    inputToDistort->texture->unlock();
    inputHowToDistort->texture->unlock();
}
