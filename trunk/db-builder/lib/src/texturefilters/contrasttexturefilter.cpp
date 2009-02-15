#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::contrast(Texture* texture, 
                                  int amount,
                                  bool inPlace)
{
    Texture* newTexture = new Texture();

    texture->lock();
    newTexture->lock();

    float contrast = powf((amount / 128.0f), 3.0f);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            D3DCOLOR srcColor = texture->getPixel(x, y);
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
            newTexture->putPixel(x, y, D3DCOLOR_XRGB(r, g, b));
        }
    }

    texture->unlock();
    newTexture->unlock();

    return newTexture;
}