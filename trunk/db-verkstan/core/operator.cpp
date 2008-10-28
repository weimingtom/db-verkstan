#include "core/operator.hpp"

#include "core/core.hpp"

#include <string.h>

Operator::Operator()
:mesh(0),
texture(0),
numberOfInputs(0),
numberOfOutputs(0),
numberOfClips(0),
dirty(true)
{
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        inputs[i] = -1;
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        outputs[i] = -1;
    for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
        properties[i].channel = -1;
    for (int i = 0; i < DB_MAX_OPERATOR_CLIPS; i++)
        operatorClips[i] = -1;
}


unsigned char Operator::getByteProperty(int index)
{
    return properties[index].byteValue + (unsigned char)properties[index].channelValue;
}

int Operator::getIntProperty(int index)
{
    return properties[index].intValue + (int)properties[index].channelValue;
}

float Operator::getFloatProperty(int index)
{
    return properties[index].floatValue + properties[index].channelValue;
}

const char* Operator::getStringProperty(int index)
{
    return properties[index].stringValue;
}

D3DXCOLOR Operator::getColorProperty(int index)
{
    D3DXCOLOR color = properties[index].colorValue;
    float channelValue = properties[index].channelValue;
    color.r += channelValue;
    color.g += channelValue;
    color.b += channelValue;
    color.a = 1.0f;

    return color;
}

D3DXVECTOR4 Operator::getVectorProperty(int index)
{
    D3DXVECTOR4 vector = properties[index].vectorValue;
    float channelValue = properties[index].channelValue;
    vector.x += channelValue;
    vector.y += channelValue;
    vector.z += channelValue;
    vector.w += channelValue;
    return vector;
}

bool Operator::isDirty()
{
    return dirty;
}

void Operator::cascadeProcess()
{
    if (!isDirty())
        return;

    for (int i = 0; i < numberOfInputs; i++)
        operators[inputs[i]]->cascadeProcess();

    process();
    dirty = false;
}

void Operator::broadcastChannelValue(int channel, float value)
{
    for (int i = 0; i < numberOfInputs; i++)
        operators[inputs[i]]->broadcastChannelValue(channel, value);

    for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
    {
        if (properties[i].channel == channel)
        {
            float v = properties[i].amplify * value;
            setDirty(properties[i].channelValue != value);
            properties[i].channelValue = v;
        }
    }
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

void Operator::deviceLost()
{
    if (texture != 0)
    {
        delete texture;
        texture = 0;
    }

    if (mesh != 0)
    {
		mesh->setDirty();
    }

    dirty = true;
}