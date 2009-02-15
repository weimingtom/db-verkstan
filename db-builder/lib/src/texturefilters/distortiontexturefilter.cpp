#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::distortion(Texture* texture, 
                                    Texture* map, 
                                    int mode, int amount_,
                                    bool inPlace)
{
    Texture* newTexture = new Texture();
    
    float amount = amount_ / 255.0f;
 
    newTexture->lock();
    texture->lock();
    map->lock();

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            D3DCOLOR c = map->getPixel(x, y);
            
            Vec3 normal;
            if (mode == 0)
                normal = Vec3(D3DCOLOR_G(c) - 127.0f, D3DCOLOR_B(c) - 127.0f, 1.0f);
            else if (mode == 1)
                normal = Vec3(D3DCOLOR_R(c) - 127.0f, D3DCOLOR_G(c) - 127.0f, D3DCOLOR_B(c) - 127.0f);

            normalize(normal);

            float u = fmodf(normal.x * amount + x, 255.0f);
            float v = fmodf(normal.y * amount + y, 255.0f);

            newTexture->putPixel(x, y, texture->getPixelWrap(u, v));
        }
    }

    newTexture->unlock();
    texture->unlock();
    map->unlock();

    return newTexture;
}