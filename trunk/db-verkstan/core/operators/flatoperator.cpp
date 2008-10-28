#include "core/operators/flatoperator.hpp"

void FlatOperator::render()
{

}

void FlatOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    texture->fillRectangle(0, 0, 256, 256, getColorProperty(0));
}
