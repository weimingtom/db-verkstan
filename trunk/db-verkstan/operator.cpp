#include "operator.hpp"

#include "core.hpp"

#include <string.h>

Operator::Operator()
:mesh(0),
texture(0),
numberOfInputs(0),
numberOfOutputs(0),
dirty(true)
{
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        inputs[i] = -1;
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        outputs[i] = -1;
}

void Operator::process()
{

}

unsigned char Operator::getByteProperty(int index)
{
    return properties[index].byteValue;
}

void Operator::setByteProperty(int index, unsigned char value)
{
    properties[index].byteValue = value;
}

int Operator::getIntProperty(int index)
{
    return properties[index].intValue;
}

void Operator::setIntProperty(int index, int value)
{
    properties[index].intValue = value;
}

float Operator::getFloatProperty(int index)
{
    return properties[index].floatValue;
}

void Operator::setFloatProperty(int index, float value)
{
    properties[index].floatValue = value;
}

const char* Operator::getStringProperty(int index)
{
    return properties[index].stringValue;
}

void Operator::setStringProperty(int index, const char *value)
{
    // TODO Should strcpy really be used here? Perhaps there is a better solution.
    // Perhaps strcpy requires a runtime library that we cannot relay on (like Microsoft runtime libraries).
    strcpy(properties[index].stringValue, value);
    setDirty(true);
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

void Operator::setDirty(bool dirty)
{
    for (int i = 0; i < numberOfOutputs; i++)
        operators[outputs[i]]->setDirty(dirty);

    this->dirty = dirty;
}

Operator* Operator::getInput(int index)
{
    return operators[inputs[index]];
}

void Operator::deviceLost()
{
    if (texture != 0)
    {
        delete texture;
        texture = 0;
    }

    dirty = true;
}