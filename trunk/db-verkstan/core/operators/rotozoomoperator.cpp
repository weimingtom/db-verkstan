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
    float co = cos(frotate);
    float si = sin(frotate);
    
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

            int u1 = ((int)u + 2560) % 256;
            int u2 =  u1 + 1;
            int v1 = ((int)v + 2560) % 256;
            int v2 =  v1 + 1;
            float u1w = u - (int)u;
            float u2w = 1.0f - u1w;
            float v1w = v - (int)v;
            float v2w = 1.0f - v1w;

            dstPixels[dstPitch * y + x] = 
                srcPixels[srcPitch * v1 + u1] * u1w * v1w +
                srcPixels[srcPitch * v1 + u2] * u2w * v1w +
                srcPixels[srcPitch * v2 + u1] * u1w * v2w +
                srcPixels[srcPitch * v2 + u2] * u2w * v2w;
            /*
            u += 256.0f * 10.0f;
            v += 256.0f * 10.0f;

            u = ((int)u % 256);
            v = ((int)v % 256);*/
            

           // dstPixels[dstPitch * y + x] = srcPixels[srcPitch * (int)v + (int)u];
        }
    }

    source->unlock();
    texture->unlock();
}
