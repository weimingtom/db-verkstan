#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::rectangle(Texture* texture, 
                                   D3DXCOLOR color, 
                                   int x, 
                                   int y,
                                   int width,
                                   int height,
                                   bool inPlace)
{
    Texture* newTexture = new Texture();

    if (texture == 0)    
        newTexture->fillRectangle(0, 0, 256, 256, 0xff000000);
    else
        texture->copy(texture);

    newTexture->fillRectangle(x, y, width, height, color);
    return newTexture;
}