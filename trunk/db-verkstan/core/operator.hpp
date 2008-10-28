#pragma once

#include "core/globals.hpp"
#include "core/texture.hpp"
#include "core/mesh.hpp"

#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>

#define DB_MAX_OPERATOR_CONNECTIONS 64
#define DB_MAX_OPERATOR_PROPERTIES 32
#define DB_MAX_OPERATOR_CLIPS 64
#define DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH 1024

class Operator
{
public:
    Operator();
    virtual ~Operator() {};
    
    virtual void cascadeProcess();
    virtual void process() = 0;
    virtual void render() = 0;

    virtual void deviceLost();

    Operator* getInput(int index);
    
    unsigned char getByteProperty(int index);
    int getIntProperty(int index);
    float getFloatProperty(int index);
    const char* getStringProperty(int index);
    D3DXCOLOR getColorProperty(int index);
    D3DXVECTOR4 getVectorProperty(int index);

    bool isDirty();
    void setDirty(bool dirty);
    
    void broadcastChannelValue(int channel, float value);

    Mesh* mesh;
    Texture* texture;
    int start;
    int end;
    int operatorClips[DB_MAX_OPERATOR_CLIPS];
    int numberOfClips;

    struct Property
    {
        unsigned char byteValue;
        float floatValue;
        int intValue;
        char stringValue[DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH];
        D3DXCOLOR colorValue;
        D3DXVECTOR4 vectorValue;
        int channel;
        float amplify;
        float channelValue;
    };

    Property properties[DB_MAX_OPERATOR_PROPERTIES];
    int inputs[DB_MAX_OPERATOR_CONNECTIONS];
    int outputs[DB_MAX_OPERATOR_CONNECTIONS];
    int numberOfInputs;
    int numberOfOutputs;
    bool dirty;
};