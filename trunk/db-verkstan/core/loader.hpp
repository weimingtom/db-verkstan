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
while (dataOffset < dataSize)
{
    unsigned char type = data[dataOffset++];
    unsigned char instances = data[dataOffset++];

    for (unsigned char i = 0; i < instances; i++)
    {
        Operator* op;
        unsigned char numberOfProperties;
        unsigned char* propertyTypes;
        unsigned char operatorType = 0;

#define OPERATOR_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_DEFINES       

        operators[id++] = op;

        for (unsigned char p = 0; p < numberOfProperties; p++)
        {
            switch (propertyTypes[p])
            {
            case 0: // Byte
                op->properties[p].byteValue = data[dataOffset++];
                break;
            case 1: // Int
                {
                    int intValue = 0;
                    intValue |= data[dataOffset++] << 6;
                    intValue |= data[dataOffset++] << 4;
                    intValue |= data[dataOffset++] << 2;
                    intValue |= data[dataOffset++];
                    op->properties[p].intValue = intValue;
                    break;
                }
            case 2: // Float
                dataOffset += 4;
                break;
            case 3: // Color
                dataOffset += 3;
                break;
            case 4: // Vector
                dataOffset += 4*3;
                break;
            case 5: // String
                break;
            }
        }
    }
}