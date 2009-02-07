#include "db-util.hpp"
#include "operator.hpp"
#include "filters.hpp"
#include <string.h>

Operator::Operator(unsigned int filterType_)
:mesh(0),
texture(0),
numberOfInputs(0),
numberOfOutputs(0),
dirty(true),
filterType(filterType_)
{
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        inputs[i] = -1;
}

#ifdef DB_EDITOR
Operator::~Operator()
{
    deviceLost();
}
#endif

void Operator::cascadeProcess()
{
    if (!isDirty())
        return;

    for (int i = 0; i < numberOfInputs; i++)
        operators[inputs[i]]->cascadeProcess();

    process();
    dirty = false;
}

void Operator::process()
{
    if (texture != 0)
        delete texture;

    if (mesh != 0)
        delete mesh;

    switch (filterType)
    {
    case BlurTextureFilter:
        texture = TextureFilters::blur(getInput(0)->texture, 
                                       getByteProperty(0), 
                                       getByteProperty(2),
                                       getByteProperty(3),
                                       getByteProperty(1));
        break;
    case PixelsTextureFilter:
        {
        Texture* inputTexture = 0;

        if (getInput(0) != 0)
            inputTexture = getInput(0)->texture;

        texture = TextureFilters::pixels(inputTexture, 
                                         getColorProperty(0), 
                                         getColorProperty(1),
                                         getByteProperty(2),
                                         getByteProperty(3));
        break;
        }
    }
}

unsigned char Operator::getByteProperty(int index)
{
    return properties[index].byteValue;
}

int Operator::getIntProperty(int index)
{
    return properties[index].intValue;
}

float Operator::getFloatProperty(int index)
{
    return properties[index].floatValue;
}

const char* Operator::getStringProperty(int index)
{
    return properties[index].stringValue;
}

D3DXCOLOR Operator::getColorProperty(int index)
{
    return properties[index].colorValue;
}

D3DXVECTOR3 Operator::getVectorProperty(int index)
{
    return properties[index].vectorValue;
}

bool Operator::isDirty()
{
    return dirty;
}

void Operator::setDirty(bool dirty)
{
    for (int i = 0; i < numberOfOutputs; i++)
        operators[outputs[i]]->setDirty(dirty);

    this->dirty = dirty;
}

Operator* Operator::getInput(int index)
{
    if (inputs[index] == -1)
        return 0;
    return operators[inputs[index]];
}

#ifdef DB_EDITOR
void Operator::deviceLost()
{
    if (texture != 0)
        texture->setDirty();

    if (mesh != 0)
        mesh->setDirty();
}
#endif