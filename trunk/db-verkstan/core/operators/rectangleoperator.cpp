#include "core/operators/rectangleoperator.hpp"

void RectangleOperator::render()
{

}

void RectangleOperator::process()
{    
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);
    
    if (input != 0)
        input->texture->copy(texture);
    else
        texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    unsigned char r = getByteProperty(0);
    unsigned char g = getByteProperty(1);
    unsigned char b = getByteProperty(2);
    unsigned char x = getByteProperty(3);
    unsigned char y = getByteProperty(4);
    unsigned char width = getByteProperty(5);
    unsigned char height = getByteProperty(6);

    texture->fillRectangle(x, y, width, height, D3DCOLOR_XRGB(r, g, b));
}
