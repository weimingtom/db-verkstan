#include "core/operators/glowoperator.hpp"

void GlowOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);

    if (input != 0)
        input->texture->copy(texture);
    else
        texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    D3DXCOLOR color = getColorProperty(0);
    unsigned char centerx = getByteProperty(1);
    unsigned char centery = getByteProperty(2);
    unsigned char radiusx = getByteProperty(3);
    unsigned char radiusy = getByteProperty(4);
    float gamma = 1.0f - getByteProperty(5) / 256.0f;
    float alpha = 1.0f - getByteProperty(6) / 256.0f;

    unsigned char r = D3DCOLOR_R(color);
    unsigned char g = D3DCOLOR_G(color);
    unsigned char b = D3DCOLOR_B(color);
    
    float fradiusx = 1.0f / (float)radiusx;
	float fradiusy = 1.0f / (float)radiusy;
 
    D3DXCOLOR blackColor = D3DCOLOR_ARGB(0, 0, 0, 0);

    texture->lock();

    DWORD* pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    DWORD* inputPixels;
    
    if (input != 0)
        inputPixels = (DWORD*)input->texture->d3d9LockedRect.pBits;
    else
        inputPixels = pixels;

    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);
    
    for (int y = 0; y < 256; y++)
    {
        float dy = (float)(y - centery) * fradiusy;
		float dy_2 = dy*dy;

        for (int x = 0; x < 256; x++)
        {
            float dx = (float)(x-centerx) * fradiusx;
			float d = sqrtf(dx*dx + dy_2);
           
            if (d > 1.0f)		
                d = 1.0f;
			d = 1.0f - d;
            
            float a;
            if (d != 0.0f)
            {
                d = powf(d, gamma);
                a = d - alpha;
            }
            else
            {
                a = 0.0f;
            }

            D3DXCOLOR resultColor;
            D3DXCOLOR inputColor = inputPixels[pitch * y + x];
            D3DXColorLerp(&resultColor, &inputColor, &color, a);
            pixels[pitch * y + x] = resultColor;
        }
    }

    texture->unlock();
}
