#include "core/operators/bluroperator.hpp"

// Some thoughts and ideas about enhancing the code.
// Different was of handling edges could be handled,
// like CLAMP, WRAP and ZERO.
// As the vertical and horizontal bluring is almost
// identicall it could be done with a single loop
// if the loop transposes each pixel so it's ready
// for the next blur.
void BlurOperator::process()
{
    if (texture != 0)
        delete texture;

    Texture* tmp;
    Texture* out = getInput(0)->texture->clone();   
    Texture* in = new Texture();

    in->lock();
    out->lock();

    DWORD* inPixels = (DWORD*)in->d3d9LockedRect.pBits;
    DWORD* outPixels = (DWORD*)out->d3d9LockedRect.pBits;

    int pitch = in->d3d9LockedRect.Pitch / sizeof(DWORD);

    unsigned char type = getByteProperty(0);
    unsigned char direction = getByteProperty(1);
    unsigned char width = getByteProperty(2);
    unsigned char amplify = getByteProperty(3);

    width = width % 2 == 0 ? width + 1 : width;
    width = width < 1 ? 1 : width;
    amplify = amplify > 32 ? 32 : amplify; 
    int wh = width / 2;
    float amp = (width - 1.0f) * (amplify / 32.0f);

    float w = ((float)width - amp);

    // Type 0 is Box blur
    // Type 1 is Triangle blur
    // Type 2 is Gaussien blur
    for (int p = 0; p < type + 1; p++)
    {
        // Swap
        tmp = in;
        in = out;
        out = tmp;
        inPixels = (DWORD*)in->d3d9LockedRect.pBits;
        outPixels = (DWORD*)out->d3d9LockedRect.pBits;

        // If we should blur along the x-axis.
        if (direction == 0 || direction == 2)
        {
            // Blur along the x-axis.
            for (int y = 0; y < 256; ++y)
            {
                //int suma = 0;
                float sumr = 0;
                float sumg = 0;
                float sumb = 0;
               
                for (int i = 0; i < width; ++i)
                {
                    D3DCOLOR c = inPixels[y * pitch + i];
                    //suma += D3DCOLOR_A(c);
                    sumr += D3DCOLOR_R(c) / w;
                    sumg += D3DCOLOR_G(c) / w;
                    sumb += D3DCOLOR_B(c) / w;
                }

                for (int x = 0; x < 256; ++x)
                {
                    int ox = (x + wh) % 256;

                    //int a = suma / (width - amp);
                    int r = (int)sumr;// / (width - amp);
                    int g = (int)sumg;// / (width - amp);
                    int b = (int)sumb;// / (width - amp);

                    //a = a > 255 ? 255 : a;
                    r = r > 255 ? 255 : r;
                    g = g > 255 ? 255 : g;
                    b = b > 255 ? 255 : b;

                    outPixels[y * pitch + ox] = D3DCOLOR_XRGB(r, g, b);
                    
                    D3DCOLOR c1 = inPixels[y * pitch + x];
                    //suma -= D3DCOLOR_A(c1);
                    sumr -= D3DCOLOR_R(c1) / w;
                    sumg -= D3DCOLOR_G(c1) / w;
                    sumb -= D3DCOLOR_B(c1) / w;

                    int ex = (x + width) % 256;

                    D3DCOLOR c2 = inPixels[y * pitch + ex];
                    //suma += D3DCOLOR_A(c2);
                    sumr += D3DCOLOR_R(c2) / w;
                    sumg += D3DCOLOR_G(c2) / w;
                    sumb += D3DCOLOR_B(c2) / w;
                }
            }
        }

        // If direction is X and Y we need to perform a swap
        // before we blur along the Y-axis.
        if (direction == 2)
        {
            // Swap
            tmp = in;
            in = out;
            out = tmp;
            inPixels = (DWORD*)in->d3d9LockedRect.pBits;
            outPixels = (DWORD*)out->d3d9LockedRect.pBits;
        }

        // If we should blur along the y-axis.
        if (direction > 0)
        {
            // Blur along the y-axis.
            for (int x = 0; x < 256; ++x)
            {
                //int suma = 0;
                float sumr = 0;
                float sumg = 0;
                float sumb = 0;
               
                for (int i = 0; i < width; ++i)
                {
                    D3DCOLOR c = inPixels[i * pitch + x];
                    //suma += D3DCOLOR_A(c);
                    sumr += D3DCOLOR_R(c) / w;
                    sumg += D3DCOLOR_G(c) / w;
                    sumb += D3DCOLOR_B(c) / w;
                }

                for (int y = 0; y < 256; ++y)
                {
                    int oy = (y + wh) % 256;

                    //int a = suma / (width - amp);
                    int r = (int)sumr;
                    int g = (int)sumg;
                    int b = (int)sumb;

                    r = r > 255 ? 255 : r;
                    g = g > 255 ? 255 : g;
                    b = b > 255 ? 255 : b;

                    outPixels[oy * pitch + x] = D3DCOLOR_XRGB(r, g, b);
                    
                    D3DCOLOR c1 = inPixels[y * pitch + x];
                    sumr -= D3DCOLOR_R(c1) / w;
                    sumg -= D3DCOLOR_G(c1) / w;
                    sumb -= D3DCOLOR_B(c1) / w;

                    int ey = (y + width) % 256;

                    D3DCOLOR c2 = inPixels[ey * pitch + x];
                    sumr += D3DCOLOR_R(c2) / w;
                    sumg += D3DCOLOR_G(c2) / w;
                    sumb += D3DCOLOR_B(c2) / w;
                }
            }
        }
    }

    in->unlock();
    out->unlock();

    texture = out->clone();

    delete in;
    delete out;
}