#include "core/operators/rotozoomoperator.hpp"

void RotozoomOperator::process()
{    
    if (texture == 0)
        texture = new Texture();

    Texture* source = getInput(0)->texture;

    unsigned char centerx = getByteProperty(0);
    unsigned char centery = getByteProperty(1);
    unsigned char rotation = getByteProperty(2);
    float zoom = getFloatProperty(3);
   
    source->lock();
    texture->lock();

    float frotate = rotation / 256.0f * D3DX_PI * 2.0f;
    float fzoom = zoom;
    float co = cosf(frotate);
    float si = sinf(frotate);
    
    DWORD* srcPixels = (DWORD*)source->d3d9LockedRect.pBits;
    DWORD* dstPixels = (DWORD*)texture->d3d9LockedRect.pBits;
    int srcPitch = source->d3d9LockedRect.Pitch / sizeof(DWORD);
    int dstPitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
		{
            float u = (x - centerx) * co + (y - centery) * (-si) + centerx;
            float v = (x - centerx) * si + (y - centery) * co + centery;
            
            u *= fzoom;
            v *= fzoom;

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
            r += (int)(D3DCOLOR_R(srcPixels[srcPitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[srcPitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[srcPitch * v1 + u1]) * weight);

            weight = uf * (1.0f - vf);
            u1 = (ut + 2561) % 256;
            v1 = (vt + 2560) % 256;
            r += (int)(D3DCOLOR_R(srcPixels[srcPitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[srcPitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[srcPitch * v1 + u1]) * weight);

            weight = (1.0f - uf) * vf;
            u1 = (ut + 2560) % 256;
            v1 = (vt + 2561) % 256;
            r += (int)(D3DCOLOR_R(srcPixels[srcPitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[srcPitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[srcPitch * v1 + u1]) * weight);

            weight = uf * vf;
            u1 = (ut + 2561) % 256;
            v1 = (vt + 2561) % 256;
            r += (int)(D3DCOLOR_R(srcPixels[srcPitch * v1 + u1]) * weight);
            g += (int)(D3DCOLOR_G(srcPixels[srcPitch * v1 + u1]) * weight);
            b += (int)(D3DCOLOR_B(srcPixels[srcPitch * v1 + u1]) * weight);

            dstPixels[dstPitch * y + x] = D3DCOLOR_XRGB(r, g, b);
        }
    }

    source->unlock();
    texture->unlock();
}
