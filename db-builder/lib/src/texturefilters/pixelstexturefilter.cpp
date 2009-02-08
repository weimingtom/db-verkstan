#include "db-util.hpp"
#include "filters.hpp"
#include "texture.hpp"

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
		if (texture != 0)
		{
			newTexture = texture->clone();
		}
		else
		{
			newTexture = new Texture();
			newTexture->fillRectangle(0, 0, 256, 256, D3DCOLOR_ARGB(255, 0, 0, 0));
		}
    }
    else
    {
        newTexture = texture;        
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