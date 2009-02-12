#include "db-util.hpp"
#include "filters.hpp"
#include "texture.hpp"

static DWORD pack(DWORD r, DWORD g, DWORD b, DWORD div, DWORD amp)
{
	div *= 16;
	r = (r * amp) / div;
	g = (g * amp) / div;
	b = (b * amp) / div;

	r = min(r, (DWORD)255);
	g = min(g, (DWORD)255);
	b = min(b, (DWORD)255);

	return 0xff000000 |
		(r & 0xff) |
		(g & 0xff) << 8 |
		(b & 0xff) << 16;
}

Texture* TextureFilters::blur(Texture* texture, 
                              int passes,
                              int direction,
                              int width,
                              int amplify)
{
    passes += 1;
    direction += 1;
	passes = max(1, passes);
	width = max(1, width);
   
    Texture* in = texture->clone();   
    Texture* out = new Texture();

    in->lock();
    out->lock();

	if (direction & 1)
	{
		// Repeat box blur
		for (int t = 0; t < passes; t++)
		{
			// For each line
			for (int y = 0; y < 256; y++)
			{
				DWORD r = 0, g = 0, b = 0;
				for (int x = 0; x < width; x++)
				{
					DWORD c = in->getPixel(x, y);
					r += c & 0xff;
					g += (c >> 8) & 0xff;
					b += (c >> 16) & 0xff;
				}

				for (int x = 0; x < 256; x++)
				{
					out->putPixel((x + width / 2) & 0xff, y, pack(r, g, b, width, amplify));

					DWORD c1 = in->getPixel((x + width) & 0xff, y);
					DWORD c2 = in->getPixel(x, y);
					r += c1 & 0xff;
					g += (c1 >> 8) & 0xff;
					b += (c1 >> 16) & 0xff;
					r -= c2 & 0xff;
					g -= (c2 >> 8) & 0xff;
					b -= (c2 >> 16) & 0xff;
				}
			}

			{
				Texture *tmp = out;
				out = in;
				in = tmp;
			}
		}
	}

	if (direction & 2)
	{
		// Repeat box blur
		for (int t = 0; t < passes; t++)
		{
			// For each column
			for (int x = 0; x < 256; x++)
			{
				DWORD r = 0, g = 0, b = 0;
				for (int y = 0; y < width; y++)
				{
					DWORD c = in->getPixel(x, y);
					r += c & 0xff;
					g += (c >> 8) & 0xff;
					b += (c >> 16) & 0xff;
				}

				for (int y = 0; y < 256; y++)
				{
					out->putPixel(x, (y + width / 2) & 0xff, pack(r, g, b, width, amplify));

					DWORD c1 = in->getPixel(x, (y + width) & 0xff);
					DWORD c2 = in->getPixel(x, y);
					r += c1 & 0xff;
					g += (c1 >> 8) & 0xff;
					b += (c1 >> 16) & 0xff;
					r -= c2 & 0xff;
					g -= (c2 >> 8) & 0xff;
					b -= (c2 >> 16) & 0xff;
				}
			}

			{
				Texture *tmp = out;
				out = in;
				in = tmp;
			}
		}
	}

	
    in->unlock();
    out->unlock();

    delete out;

    return in;
}
