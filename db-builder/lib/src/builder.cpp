#include "db-util.hpp"
#include "builder.hpp"

LPDIRECT3DDEVICE9 Builder::device = 0;

void Builder::load(const unsigned char* data)
{

}

Texture* Builder::getTexture(unsigned int id)
{
    return 0; 
}

Mesh* getMesh(unsigned int id)
{
    return 0;
}

Renderable* getRenderable(unsigned int id)
{
    return 0;
}