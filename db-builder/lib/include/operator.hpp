#pragma once

#include "db-util.hpp"

#define DB_MAX_OPERATORS 4096
#define DB_MAX_OPERATOR_CONNECTIONS 32
#define DB_MAX_OPERATOR_PROPERTIES 32
#define DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH 1024

class Texture;
class Mesh;

class Operator
{
public:
    static Operator* operators[DB_MAX_OPERATORS];
    static short numberOfOperators;

    Operator(unsigned int filterType);

#ifdef DB_EDITOR
    virtual ~Operator();
#endif

    Operator* getInput(int index);
    
    void cascadeProcess();
    void process();

    unsigned char getByteProperty(int index);
    int getIntProperty(int index);
    float getFloatProperty(int index);
    const char* getStringProperty(int index);
    D3DXCOLOR getColorProperty(int index);
    D3DXVECTOR3 getVectorProperty(int index);

    bool isDirty();
    void setDirty(bool dirty);

    Mesh* mesh;
    Texture* texture;

    struct Property
    {
        unsigned char byteValue;
        int intValue;
        float floatValue;
        char stringValue[DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH];
        D3DXCOLOR colorValue;
        D3DXVECTOR3 vectorValue;
    };

    Property properties[DB_MAX_OPERATOR_PROPERTIES];
    short inputs[DB_MAX_OPERATOR_CONNECTIONS];
    short outputs[DB_MAX_OPERATOR_CONNECTIONS];
    unsigned char numberOfInputs;
    unsigned char numberOfOutputs;
    bool dirty;
    unsigned int filterType;

#ifdef DB_EDITOR
    virtual void deviceLost();
#endif
};