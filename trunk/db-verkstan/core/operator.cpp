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
    return properties[index].value.byteValue + (unsigned char)properties[index].channelValue;
}

void Operator::setByteProperty(int index, unsigned char value)
{
    properties[index].value.byteValue = value;
    properties[index].channelValue = 0.0f;
}

int Operator::getIntProperty(int index)
{
    return properties[index].value.intValue + (int)properties[index].channelValue;
}

void Operator::setIntProperty(int index, int value)
{
    properties[index].value.intValue = value;
    properties[index].channelValue = 0.0f;
}

float Operator::getFloatProperty(int index)
{
    return properties[index].value.floatValue + properties[index].channelValue;
}

void Operator::setFloatProperty(int index, float value)
{
    properties[index].value.floatValue = value;
    properties[index].channelValue = 0.0f;
}

const char* Operator::getStringProperty(int index)
{
    return properties[index].value.stringValue;
}

void Operator::setStringProperty(int index, const char *value)
{
    // TODO Should strcpy really be used here? Perhaps there is a better solution.
    // Perhaps strcpy requires a runtime library that we cannot relay on (like Microsoft runtime libraries).
    strcpy(properties[index].value.stringValue, value);
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
        delete mesh;
        mesh = 0;
    }

    dirty = true;
}