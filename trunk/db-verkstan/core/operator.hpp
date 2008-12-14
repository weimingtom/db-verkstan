#pragma once

#include "core/globals.hpp"
#include "core/texture.hpp"
#include "core/mesh.hpp"

#include <d3d9.h>
#include <d3dx9.h>

#define DB_MAX_OPERATOR_CONNECTIONS 32
#define DB_MAX_OPERATOR_PROPERTIES 32
#define DB_MAX_TIMELINE_CLIPS 64
#define DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH 1024

class Operator
{
public:
    Operator();

    void process() {};

    void preRender(int tick);
    void render(int tick);

    Operator* getInput(int index);
    
    void cascadeProcess();

    unsigned char getByteProperty(int index);
    int getIntProperty(int index);
    float getFloatProperty(int index);
    const char* getStringProperty(int index);
    D3DXCOLOR getColorProperty(int index);
    D3DXVECTOR3 getVectorProperty(int index);

    bool isDirty();
    void setDirty(bool dirty);
    
    void broadcastChannelValue(int channel, float value);

    Mesh* mesh;
    Texture* texture;
    int ticks;
    int timelineClips[DB_MAX_TIMELINE_CLIPS];
    int numberOfClips;

    struct Property
    {
        unsigned char byteValue;
        int intValue;
        float floatValue;
        char stringValue[DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH];
        D3DXCOLOR colorValue;
        D3DXVECTOR3 vectorValue;
        int channel1;
        int channel2;
        int channel3;
        float amplify1;
        float amplify2;
        float amplify3;
        float channelValue1;
        float channelValue2;
        float channelValue3;
    };

    Property properties[DB_MAX_OPERATOR_PROPERTIES];
    int inputs[DB_MAX_OPERATOR_CONNECTIONS];
    int outputs[DB_MAX_OPERATOR_CONNECTIONS];
    int numberOfInputs;
    int numberOfOutputs;
    bool dirty;

#ifdef DB_VERKSTAN_EDITOR
    virtual void deviceLost();
#endif
};