#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::flat(D3DXCOLOR color)
{
    Texture* newTexture = new Texture();
    newTexture->fillRectangle(0, 0, 256, 256, color);
    return newTexture;
}