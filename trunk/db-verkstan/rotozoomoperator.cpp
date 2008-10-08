#include "rotozoomoperator.hpp"

void RotozoomOperator::process()
{    
    if (texture == 0)
        texture = new Texture();

    Texture* source = getInConnectedOperator(0)->texture;

    unsigned char centerx = getByteProperty(0);
    unsigned char centery = getByteProperty(1);
    unsigned char rotation = getByteProperty(2);
    float zoom = getFloatProperty(3);
   
    source->lock();
    texture->lock();

    float frotate = rotation / 256.0f * M_PI * 2.0f;
    float fzoom = zoom;
    float co = cos(frotate);
    float si = sin(frotate);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
		{
            float u = (x - centerx) * co + (y - centery) * (-si) + centerx;
            float v = (x - centerx) * si + (y - centery) * co + centery;
            
            u *= fzoom;
            v *= fzoom;
            u += 256.0f * 10.0f;
            v += 256.0f * 10.0f;
            u = ((int)u % 256) + (u - floor(u));
            v = ((int)v % 256) + (v - floor(v)); 
            
            texture->putPixel(x, y, source->getPixel(u, v));
        }
    }

    source->unlock();
    texture->unlock();
}
