#pragma once

#include "core/globals.hpp"
#include "core/texture.hpp"

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
    
    void cascadeProcess();
    virtual void process() = 0;
    virtual void render() = 0;

    virtual void deviceLost();

    Operator* getInput(int index);
    unsigned char getByteProperty(int index);
    void setByteProperty(int index, unsigned char value);
    int getIntProperty(int index);
    void setIntProperty(int index, int value);
    float getFloatProperty(int index);
    void setFloatProperty(int index, float value);
    const char* getStringProperty(int index);
    void setStringProperty(int index, const char *value);
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
    int inputs[DB_MAX_OPERATOR_CONNECTIONS];
    int outputs[DB_MAX_OPERATOR_CONNECTIONS];
    int numberOfInputs;
    int numberOfOutputs;
    bool dirty;
};