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
    {
        properties[i].channel1 = -1;
        properties[i].channel2 = -1;
        properties[i].channel3 = -1;
        properties[i].amplify1 = 1.0f;
        properties[i].amplify2 = 1.0f;
        properties[i].amplify3 = 1.0f;
    }
    for (int i = 0; i < DB_MAX_OPERATOR_CLIPS; i++)
        operatorClips[i] = -1;
}

unsigned char Operator::getByteProperty(int index)
{
    return properties[index].byteValue + (int)properties[index].channelValue1;
}

int Operator::getIntProperty(int index)
{
    return properties[index].intValue + (int)properties[index].channelValue1;
}

float Operator::getFloatProperty(int index)
{
    return properties[index].floatValue + properties[index].channelValue1;
}

const char* Operator::getStringProperty(int index)
{
    return properties[index].stringValue;
}

D3DXCOLOR Operator::getColorProperty(int index)
{
    D3DXCOLOR color = properties[index].colorValue;
    color.r += properties[index].channelValue1 / 256.0f;
    color.g += properties[index].channelValue2 / 256.0f;
    color.b += properties[index].channelValue3 / 256.0f;
    color.a = 1.0f;

    return color;
}

D3DXVECTOR4 Operator::getVectorProperty(int index)
{
    D3DXVECTOR4 vector = properties[index].vectorValue;
    vector.x += properties[index].channelValue1;
    vector.y += properties[index].channelValue2;
    vector.z += properties[index].channelValue3;
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
        if (properties[i].channel1 == channel)
        {
            float v = properties[i].amplify1 * value;
            if (properties[i].channelValue1 != v)
                setDirty(true);
            properties[i].channelValue1 = v;
        }
        if (properties[i].channel2 == channel)
        {
            float v = properties[i].amplify2 * value;
            if (properties[i].channelValue2 != v)
                setDirty(true);
            properties[i].channelValue2 = v;
        }
        if (properties[i].channel3 == channel)
        {
            float v = properties[i].amplify3 * value;
            if (properties[i].channelValue3 != v)
                setDirty(true);
            properties[i].channelValue3 = v;
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