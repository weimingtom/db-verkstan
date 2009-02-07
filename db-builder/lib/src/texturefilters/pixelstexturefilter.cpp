#include "db-util.hpp"
#include "filters.hpp"

Texture* TextureFilters::pixels(Texture* texture, 
                                D3DXCOLOR color1, 
                                D3DXCOLOR color2, 
                                int count, 
                                int seed, 
                                bool inPlace)
{
    Texture* newTexture;
    
    if (!inPlace)
    {
        newTexture = texture->clone();
    }
    else
    {
        newTexture = texture;
        newTexture->fillRectangle(0, 0, 56, 256, D3DCOLOR_ARGB(255, 0, 0, 0));
    }

    newTexture->lock();
    srand(seed);
    D3DXCOLOR color;
    
    for (int i = 0; i < count; i++)
    {
        D3DXColorLerp(&color, &color1, &color2, frand());
        newTexture->putPixel(rand() % 256, rand() % 256, color); 
    }

    newTexture->unlock();
    newTexture->setDirty();

    return newTexture;
}