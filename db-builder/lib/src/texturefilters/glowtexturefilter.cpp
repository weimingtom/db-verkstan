#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::glow(Texture* texture, 
                              D3DXCOLOR color, 
                              int centerX,
                              int centerY,
                              int radiusX_,
                              int radiusY_,
                              int gamma_,
                              int alpha_,
                              bool inPlace)
{
    Texture* newTexture = new Texture();
    
    if (texture != 0)
        texture->copy(newTexture);
    else
        newTexture->fillRectangle(0, 0, 256, 256, 0xff000000);

    float radiusX = 1.0f / radiusX_;
    float radiusY = 1.0f / radiusY_;
    float gamma = 1.0f - gamma_ / 256.0f;
    float alpha = 1.0f - alpha_ / 256.0f;

    newTexture->lock();
    
    for (int y = 0; y < 256; y++)
    {
        float dy = (float)(y - centerY) * radiusY;
		float dy_2 = dy*dy;

        for (int x = 0; x < 256; x++)
        {
            float dx = (float)(x-centerX) * radiusX;
			float d = sqrtf(dx*dx + dy_2);
           
            if (d > 1.0f)		
                d = 1.0f;
			d = 1.0f - d;
            
            float a = -1.0f;;
            if (d != 0.0f)
            {
                d = powf(d, gamma);
                a = d - alpha;
            }
            
            if (a < 0.0f)
                continue;

            D3DXCOLOR resultColor;
            D3DXCOLOR inputColor = newTexture->getPixel(x, y);
            D3DXColorLerp(&resultColor, &inputColor, &color, a);
            newTexture->putPixel(x, y, resultColor);
        }
    }

    newTexture->unlock();

    return newTexture;
}