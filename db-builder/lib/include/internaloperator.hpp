#pragma once

#include "db-util.hpp"

#define DB_MAX_OPERATORS 1024
#define DB_MAX_OPERATOR_CONNECTIONS 32
#define DB_MAX_OPERATOR_PROPERTIES 32
#define DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH 1024

class Texture;
class Mesh;
class Renderable;

class InternalOperator
{
public:
    
    static InternalOperator* operators[DB_MAX_OPERATORS];
    static short numberOfOperators;

    InternalOperator(unsigned int filterType);

#ifdef DB_EDITOR
    ~InternalOperator();
#endif

    InternalOperator* getInput(int index);
    
    void cascadeProcess();
    void process();

    unsigned char getByteProperty(int index);
    int getIntProperty(int index);
    float getFloatProperty(int index);
    const char* getStringProperty(int index);
    D3DXCOLOR getColorProperty(int index);
    D3DXVECTOR3 getVectorProperty(int index);

    Mesh* mesh;
    Texture* texture;
	Renderable *renderable;

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
    bool isDirty();
    void setDirty(bool dirty);
    void deviceLost();
#endif
};