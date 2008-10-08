#pragma once

#include "globals.hpp"
#include "texture.hpp"

#include <d3d9.h>
#include <d3dx9.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define DB_MAX_OPERATOR_CONNECTIONS 128
#define DB_MAX_OPERATOR_PROPERTIES 32
#define DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH 1024

class Mesh;

class Operator
{
public:
    Operator();
    virtual ~Operator() {};
    virtual void process() = 0;
    virtual void deviceLost();
    void cascadeProcess();
    Operator* getInConnectedOperator(int index);
    unsigned char getByteProperty(int index);
    void setByteProperty(int index, unsigned char byteValue);
    int getIntProperty(int index);
    void setIntProperty(int index, int intValue);
    int getColorProperty(int index)
    {
        return getIntProperty(index);
    }
    void setColorProperty(int index, int intValue)
    {
        setIntProperty(index, intValue);
    }
    float getFloatProperty(int index);
    void setFloatProperty(int index, float floatValue);
    const char* getStringProperty(int index);
    void setStringProperty(int index, const char *stringValue);
    const char* getTextProperty(int index)
    {
        return getStringProperty(index);
    }
    void setTextProperty(int index, const char *textValue)
    {
         return setStringProperty(index, textValue);
    }
    bool isDirty();
    void setDirty(bool dirty);
  

    Mesh* mesh;
    Texture* texture;

    union Property
    {
        unsigned char byteValue;
        float floatValue;
        int intValue;
        char stringValue[DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH];
    };

    Property properties[DB_MAX_OPERATOR_PROPERTIES];
    int inConnections[DB_MAX_OPERATOR_CONNECTIONS];
    int outConnections[DB_MAX_OPERATOR_CONNECTIONS];
    int numberOfInConnections;
    int numberOfOutConnections;
protected:
    bool dirty;
};