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
    return properties[index].byteValue + (unsigned char)properties[index].channelValue1;
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
    color.r += properties[index].channelValue1;
    color.g += properties[index].channelValue2;
    color.b += properties[index].channelValue3;
    color.a = 1.0f;

    return color;
}

D3DXVECTOR4 Operator::getVectorProperty(int index)
{
    D3DXVECTOR4 vector = properties[index].vectorValue;
    vector.x += properties[index].channelValue1;
    vector.y += properties[index].channelValue2;
    vector.z += properties[index].channelValue3;
    vector.w += properties[index].channelValue4;
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

void Operator::broadcastChannelValue(int channel, 
                                     float value1, 
                                     float value2, 
                                     float value3, 
                                     float value4)
{
    for (int i = 0; i < numberOfInputs; i++)
        operators[inputs[i]]->broadcastChannelValue(channel, 
                                                    value1, 
                                                    value2, 
                                                    value3, 
                                                    value4);

    for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
    {
        if (properties[i].channel == channel)
        {
            if (value1 != 2)
            {
                float v1 = properties[i].amplify * value1;
                setDirty(properties[i].channelValue1 != value1);
                properties[i].channelValue1 = v1;
            }
            if (value2 != 2)
            {
                float v2 = properties[i].amplify * value2;
                setDirty(properties[i].channelValue2 != value2);
                properties[i].channelValue2 = v2;
            }
            if (value3 != 2)
            {
                float v3 = properties[i].amplify * value3;
                setDirty(properties[i].channelValue3 != value3);
                properties[i].channelValue3 = v3;
            }
            if (value4 != 2)
            {
                float v4 = properties[i].amplify * value4;
                setDirty(properties[i].channelValue4 != value4);
                properties[i].channelValue4 = v4;
            }
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