#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::invert(Texture* texture, bool inPlace)
{
    Texture* newTexture;
    
    if (!inPlace)
        newTexture = texture->clone();
    else
        newTexture = texture;
   

    newTexture->lock();

    for (int y = 0; y < 256; y++)
        for (int x = 0; x < 256; x++)
            newTexture->putPixel(x, y, (~newTexture->getPixel(x, y)) | 0xff000000);

    newTexture->unlock();

    return newTexture;
}