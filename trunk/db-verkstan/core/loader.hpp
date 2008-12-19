#define DEF_OP_FOR_EDITOR(opNameChars, opClass, opType)
#define ADD_BYTE_PROP(name, value)
#define ADD_INT_PROP(name, value)
#define ADD_FLOAT_PROP(name, value)
#define ADD_STRING_PROP(name, value)
#define ADD_TEXT_PROP(name, value)
#define ADD_COLOR_PROP(name, r, g, b)
#define ADD_VECTOR_PROP(name, x, y, z)
#define ADD_ENUM_PROP(name, enumValues, value)
#define ADD_INPUT(inType)
#define ADD_INFINITE_INPUT(inType)
#define ADD_OPTIONAL_INPUT(inType)
#define END_OP_FOR_EDITOR()

// First version of macros
#define DEF_OP_FOR_LOADER(opClass, numberOfProps, propTypes) \
    int opClass##NumberOfProperties = numberOfProps; \
    unsigned char opClass##PropertyTypes[numberOfProps] = propTypes;
#define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opClass)

#define OPERATOR_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_DEFINES

#undef DEF_OP_FOR_LOADER
#undef DEF_OP_FOR_LOADER_WITH_NO_PROPS

// Second version of macros
#define DEF_OP_FOR_LOADER(opClass, numberOfProps, propTypes)\
    if (operatorType == type) \
    {\
        op = new opClass##();\
        numberOfProperties = opClass##NumberOfProperties;\
        propertyTypes = opClass##PropertyTypes;\
    }\
    operatorType++;
#define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opClass)\
    if (operatorType == type) \
    {\
        op = new opClass##();\
        numberOfProperties = 0;\
    }\
    operatorType++;

int id = 0;
int dataOffset = 0;
while (dataOffset < dataSize)
{
    unsigned char instances = data[dataOffset++];
    unsigned char type = data[dataOffset++];
   
    unsigned char numberOfProperties;
    unsigned char* propertyTypes;
    int startId = id;
    for (unsigned char i = 0; i < instances; i++)
    {
        Operator* op;
        unsigned char operatorType = 0;

#define OPERATOR_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_DEFINES       

        operators[id++] = op;
    }

    for (unsigned char p = 0; p < numberOfProperties; p++)
    {
        for (unsigned char i = 0; i < instances; i++)
        {
            Operator* currentOp =  operators[startId + i];
            switch (propertyTypes[p])
            {
            case 0: // Byte
                currentOp->properties[p].byteValue = data[dataOffset++];
                break;
            case 1: // Int
                currentOp->properties[p].intValue = (reinterpret_cast<int*>(data))[dataOffset];
                dataOffset += 4;
                break;
            case 2: // Float
                currentOp->properties[p].floatValue = (reinterpret_cast<float*>(data))[dataOffset];
                dataOffset += 4;
                break;
            case 3: // Color
                currentOp->properties[p].colorValue = D3DXCOLOR(255, 
                                                                data[dataOffset++], 
                                                                data[dataOffset++], 
                                                                data[dataOffset++]);
                break;
            case 4: // Vector
                {
                float x = (reinterpret_cast<float*>(data))[dataOffset];
                dataOffset += 4;
                float y = (reinterpret_cast<float*>(data))[dataOffset];
                dataOffset += 4;
                float z = (reinterpret_cast<float*>(data))[dataOffset];
                dataOffset += 4;
                currentOp->properties[p].vectorValue = D3DXVECTOR3(x, y, z);
                break;
                }
            case 5: // String
                break;
            }
        }
    }
}