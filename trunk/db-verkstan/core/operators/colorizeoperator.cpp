#include "core/operators/colorizeoperator.hpp"

/*
inline void RGB2HSV(int r_, 
                    int g_, 
                    int b_, 
                    float& h, 
                    float& s, 
                    float& v) 
{
    float r = r_ / 256.0f;
    float g = g_ / 256.0f;
    float b = b_ / 256.0f;

    float min = r < g ? r : g;
    min = min < b ? min : b;
    float max = r > g ? r : g;
    max = max > b ? max : b;
    float delta = max - min;

	v = max;

	if (max != 0.0f)
		s = delta / max;
	else 
    {
		s = 0.0f;
		h = -1.0f;
		return;
	}

	if (r == max)
        h = (g - b) / delta;
	else if (g == max)
		h = 2.0f + ( b - r ) / delta;
	else
		h = 4.0f + (r - g) / delta;

	h *= 60.0f;	
	if (h < 0.0f)
		h += 360.0f;
}

inline void HSV2RGB(float h, float s, float v, int& r_, int& g_, int& b_) 
{
    if (v < 0.0f)
        v = 0.0f;
    if (v > 1.0f)
        v = 1.0f;

    if (s < 0.0f)
        s = 0.0f;
    if (s > 1.0f)
        s = 1.0f;

	if (s == 0.0f) 
    {
		r_ = g_ = b_ = (int)(v * 255.0f);
		return;
	}

	h /= 60.0f;			// sector 0 to 5
	int i = (int)floor(h);
	float f = h - i;			// factorial part of h
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

    float r, g, b;
	switch (i) 
    {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		case 5:
			r = v;
			g = p;
			b = q;
			break;
	}

    r_ = (int)(r * 255.0f);
    g_ = (int)(g * 255.0f);
    b_ = (int)(b * 255.0f);
}
*/
inline void RGB2HSL(int r_, int g_, int b_, float& h, float& s, float& l)
{

    float r = r_ / 256.0f;
    float g = g_ / 256.0f;
    float b = b_ / 256.0f;
   
    h = 0.0f;
    s = 0.0f;
    l = 0.0f;
    
    float min = r < g ? r : g;
    min = min < b ? min : b;
    float max = r > g ? r : g;
    max = max > b ? max : b;
    float delta = max - min;

    l = (max + min) / 2.0f;

    if (l <= 0.0f)
        return;

    s = delta;

    if (s > 0.0f)
        s /= (l <= 0.5f) ? (max + min) : (2.0f - max - min);
    else
        return;

    float r2 = (max - r) / delta;
    float g2 = (max - g) / delta;
    float b2 = (max - b) / delta;

    if (r == max)
        h = (g == min ? 5.0f + b2 : 1.0f - g2);
    else if (g == max)
        h = (b == min ? 1.0f + r2 : 3.0f - b2);
    else
        h = (r == min ? 3.0f + g2 : 5.0f - r2);

    h /= 6.0f;
}

inline void HSL2RGB(float h, float s, float l, int& r_, int& g_, int& b_)
{
    if (l < 0.0f)
        l = 0.0f;
    if (l > 1.0f)
        l = 1.0f;

    float r = l; 
    float g = l;
    float b = l;

    float v = (l <= 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);

    if (v > 0.0f)
    {
        float m;
        float sv;
        int sextant;
        float fract, vsf, mid1, mid2;

        m = l + l - v;
        sv = (v - m ) / v;
        h *= 6.0f;
        sextant = (int)h;
        fract = h - sextant;
        vsf = v * sv * fract;
        mid1 = m + vsf;
        mid2 = v - vsf;

        switch (sextant)
        {
            case 0:
                  r = v;
                  g = mid1;
                  b = m;
                  break;
            case 1:
                  r = mid2;
                  g = v;
                  b = m;
                  break;
            case 2:
                  r = m;
                  g = v;
                  b = mid1;
                  break;
            case 3:
                  r = m;
                  g = mid2;
                  b = v;
                  break;
            case 4:
                  r = mid1;
                  g = m;
                  b = v;
                  break;
            case 5:
                  r = v;
                  g = m;
                  b = mid2;
                  break;
        }
    }

    r_ = (int)(r * 255.0f);
    g_ = (int)(g * 255.0f);
    b_ = (int)(b * 255.0f);
}

void ColorizeOperator::process()
{
    if (texture == 0)
       texture = new Texture();

    Texture* srcTexture = getInput(0)->texture;
    texture->lock();
    srcTexture->lock();
    DWORD* destPixels = (DWORD*)texture->d3d9LockedRect.pBits;
    DWORD* srcPixels = (DWORD*)srcTexture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    float hue = getByteProperty(0) / 256.0f;
    float saturation = getByteProperty(1) / 256.0f ;
    float light = (getByteProperty(2) - 128) / 128.0f;

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            float h, s, l;
            D3DCOLOR srcColor = srcPixels[x + y * pitch];
            RGB2HSL(D3DCOLOR_R(srcColor), 
                    D3DCOLOR_G(srcColor), 
                    D3DCOLOR_B(srcColor), 
                    h, 
                    s, 
                    l);
            int r, g, b;
            HSL2RGB(hue, saturation, l + light, r, g, b);
            destPixels[x + y * pitch] = D3DCOLOR_XRGB(r, g, b);
        }
    }

    texture->unlock();
    srcTexture->unlock();
}
