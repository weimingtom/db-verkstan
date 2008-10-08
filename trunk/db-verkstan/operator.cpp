#include "operator.hpp"

#include "core.hpp"

#include <string.h>

Operator::Operator()
:mesh(0),
texture(0),
numberOfInConnections(0),
numberOfOutConnections(0),
dirty(true)
{
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        inConnections[i] = -1;
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        outConnections[i] = -1;
}

void Operator::process()
{

}

unsigned char Operator::getByteProperty(int index)
{
    return properties[index].byteValue;
}

void Operator::setByteProperty(int index, unsigned char byteValue)
{
    setDirty(properties[index].byteValue != byteValue || dirty);
    properties[index].byteValue = byteValue;
}

int Operator::getIntProperty(int index)
{
    return properties[index].intValue;
}

void Operator::setIntProperty(int index, int intValue)
{
    setDirty(properties[index].intValue != intValue || dirty);
    properties[index].intValue = intValue;
}

float Operator::getFloatProperty(int index)
{
    return properties[index].floatValue;
}

void Operator::setFloatProperty(int index, float floatValue)
{
    setDirty(properties[index].floatValue != floatValue || dirty);
    properties[index].floatValue = floatValue;
}

const char* Operator::getStringProperty(int index)
{
    return properties[index].stringValue;
}

void Operator::setStringProperty(int index, const char *stringValue)
{
    // TODO Should strcpy really be used here? Perhaps there is a better solution.
    // Perhaps strcpy requires a runtime library that we cannot relay on (like Microsoft runtime libraries).
    strcpy(properties[index].stringValue, stringValue);
    setDirty(true);
}

bool Operator::isDirty()
{
    bool result = dirty;
    for (int i = 0; i < numberOfInConnections; i++)
        result |= operators[inConnections[i]]->dirty;
    return result;
}

void Operator::cascadeProcess()
{
    if (!isDirty())
        return;

    for (int i = 0; i < numberOfInConnections; i++)
        operators[inConnections[i]]->cascadeProcess();

    process();
    dirty = false;
}

void Operator::setDirty(bool dirty)
{
    for (int i = 0; i < numberOfOutConnections; i++)
        operators[outConnections[i]]->setDirty(dirty);

    this->dirty = dirty;
}

Operator* Operator::getInConnectedOperator(int index)
{
    return operators[index];
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