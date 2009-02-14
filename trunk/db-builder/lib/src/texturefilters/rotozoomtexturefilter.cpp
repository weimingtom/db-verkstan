#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::rotoZoom(Texture* texture, 
                                  int centerX,
                                  int centerY,
                                  int rotation,
                                  int zoom,
                                  bool inPlace)
{
    Texture* newTexture = new Texture();
    
    texture->lock();
    newTexture->lock();

    float frotate = rotation / 255.0f * D3DX_PI * 2.0f;
    float fzoom = pow(2.0f, (zoom - 128.0f) / 32.0f);
    float co = cosf(frotate);
    float si = sinf(frotate);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
		{
            float u = ((x - centerX) * co + (y - centerY) * (-si) + centerX) * fzoom;
            float v = ((x - centerX) * si + (y - centerY) * co + centerY) * fzoom;
            newTexture->putPixel(x, y, texture->getPixelWrap(u, v));
        }
    }

    texture->unlock();
    newTexture->unlock();

    return newTexture;
}