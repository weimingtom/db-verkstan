#pragma once

#include "operator.hpp"

/**
 * Generates text.
 *
 * @int 0 color
 * @byte 1 height
 * @byte 2 x
 * @byte 3 y
 * @text 4 font. May be discarded with "".
 * @text 5 text
 */
class TextOperator: public Operator
{
public:
    TextOperator();
    ~TextOperator();
    void process();
    void deviceLost();
    LPDIRECT3DTEXTURE9 d3d9RenderTargetTexture;
};