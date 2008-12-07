#include "core/operators/cloudsoperator.hpp"

void CloudsOperator::divideGrid(float x, 
                                float y, 
                                float width, 
                                float height, 
                                float c1, 
                                float c2, 
                                float c3, 
                                float c4)
{
	float Edge1, Edge2, Edge3, Edge4, Middle;
	float newWidth = width / 2.0f;
	float newHeight = height / 2.0f;

	if (width >= 2.0f || height >= 2.0f)
	{	
        float max = (newWidth + newHeight) / 512.0f * 3.0f;
		Middle = (c1 + c2 + c3 + c4) / 4 + (frand() - 0.5f) * max;	//Randomly displace the midpoint!
		Edge1 = (c1 + c2) / 2;	//Calculate the edges by averaging the two corners of each edge.
		Edge2 = (c2 + c3) / 2;
		Edge3 = (c3 + c4) / 2;
		Edge4 = (c4 + c1) / 2;
		
		//Make sure that the midpoint doesn't accidentally "randomly displaced" past the boundaries!
		if (Middle < 0)
		{
			Middle = 0;
		}
		else if (Middle > 1.0f)
		{
			Middle = 1.0f;
		}
		
		//Do the operation over again for each of the four new grids.			
		divideGrid(x, y, newWidth, newHeight, c1, Edge1, Middle, Edge4);
		divideGrid(x + newWidth, y, newWidth, newHeight, Edge1, c2, Edge2, Middle);
		divideGrid(x + newWidth, y + newHeight, newWidth, newHeight, Middle, Edge2, c3, Edge3);
		divideGrid(x, y + newHeight, newWidth, newHeight, Edge4, Middle, Edge3, c4);
	}
	else
	{
		float c = (c1 + c2 + c3 + c4) / 4;
        
        D3DXCOLOR color;
        D3DXColorLerp(&color, &color1, &color2, c);
        pixels[pitch * (int)y + (int)x] = color; 
    }
}

void CloudsOperator::process()
{
    if (texture == 0)
        texture = new Texture();
    
    color1 = getColorProperty(0);
    color2 = getColorProperty(1);
    srand(getByteProperty(2));
    texture->lock();

    pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    divideGrid(0.0f, 0.0f, 256.0f, 256.0f, frand(), frand(), frand(), frand());

    texture->unlock();
}
