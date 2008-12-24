// We define a couple of macros we don't need (they are used
// for the editor) to do nothing.
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

// We define the DEF_OP_LOADER macro to retrieve information about operators,
// such as number of properties, property types etc...
#define DEF_OP_FOR_LOADER(opId, opClass, _numberOfConstantInputs, _numberOfProperties, ...) \
    unsigned char opClass##NumberOfProperties = _numberOfProperties; \
    unsigned char opClass##PropertyTypes[_numberOfProperties] = {__VA_ARGS__}; \
    char opClass##NumberOfConstantInputs = _numberOfConstantInputs;
#define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opId, opClass, _numberOfConstantInputs) \
     char opClass##NumberOfConstantInputs = _numberOfConstantInputs;
// We includes all operator defines to create the variables.
#define OPERATOR_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_DEFINES 

unsigned char* dataptr = data;

/////////////////////////
// Instanciate operators.
/////////////////////////
int instances = *dataptr++;
unsigned char* instanceNumberOfProperties = new unsigned char[instances];
int* instancePropertyTypes = new int[instances];
char* instanceNumberOfConstantInputs = new char[instances];
for (unsigned char operatorIndex = 0; operatorIndex < instances; operatorIndex++)
{
    unsigned char id = *dataptr++;
    // We redefine the macros to instanciate operators and fill the instance variables with values.
#undef DEF_OP_FOR_LOADER
#undef DEF_OP_FOR_LOADER_WITH_NO_PROPS
#define DEF_OP_FOR_LOADER(opId, opClass, _numberOfConstantInputs, _numberOfProperties, ...) \
    if (opId == id) \
    {\
        operators[operatorIndex] = new opClass##();\
        instanceNumberOfProperties[operatorIndex] = opClass##NumberOfProperties;\
        instancePropertyTypes[operatorIndex] =  (int)opClass##PropertyTypes;\
        instanceNumberOfConstantInputs[operatorIndex] = opClass##NumberOfConstantInputs;\
    }
#define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opId, opClass, _numberOfConstantInputs)\
    if (opId == id) \
    {\
        operators[operatorIndex] = new opClass##();\
        instanceNumberOfProperties[operatorIndex] = 0;\
        instanceNumberOfConstantInputs[operatorIndex] = opClass##NumberOfConstantInputs;\
    }
#define OPERATOR_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_DEFINES
}
////////////////////////////
// Load operator properties.
////////////////////////////
for (unsigned char operatorIndex = 0; operatorIndex < instances; operatorIndex++)
{
    unsigned int numberOfProperties = instanceNumberOfProperties[operatorIndex];
    for (unsigned char propertyIndex = 0; propertyIndex < numberOfProperties; propertyIndex++)
    {
        Operator* currentOp =  operators[operatorIndex];
        unsigned char* propertyTypes = (unsigned char*)instancePropertyTypes[operatorIndex];
        unsigned char type = propertyTypes[propertyIndex];
        switch (type)
        {
        case 0: // Byte
            currentOp->properties[propertyIndex].byteValue = *dataptr++;
            break;
        case 1: // Int
            currentOp->properties[propertyIndex].intValue = *(reinterpret_cast<short*>(dataptr));
            dataptr += 2;
            break;
        case 2: // Float
            currentOp->properties[propertyIndex].floatValue = *(reinterpret_cast<float*>(dataptr));
            dataptr += 4;
            break;
        case 3: // Color
            currentOp->properties[propertyIndex].colorValue.r = *dataptr++;
            currentOp->properties[propertyIndex].colorValue.g = *dataptr++;
            currentOp->properties[propertyIndex].colorValue.b = *dataptr++;
            break;
        case 4: // Vector
            {
            float x = *(reinterpret_cast<float*>(dataptr));
            dataptr += 4;
            float y = *(reinterpret_cast<float*>(dataptr));
            dataptr += 4;
            float z = *(reinterpret_cast<float*>(dataptr));
            dataptr += 4;
            currentOp->properties[propertyIndex].vectorValue = D3DXVECTOR3(x, y, z);
            break;
            }
        case 5: // String
            break;
        }
    }
}
////////////////////////////
// Load inputs.
////////////////////////////
for (unsigned char operatorIndex = 0; operatorIndex < instances; operatorIndex++)
{
    unsigned char numberOfInputs;
    if (instanceNumberOfConstantInputs[operatorIndex] == -1)
        numberOfInputs = *dataptr++;
    else
        numberOfInputs = instanceNumberOfConstantInputs[operatorIndex];

    while(numberOfInputs > 0)
    {
        int inputIndex = (*dataptr) + operatorIndex;
        dataptr++;
        operators[operatorIndex]->inputs[operators[operatorIndex]->numberOfInputs] = inputIndex;
        operators[operatorIndex]->numberOfInputs++;
        operators[inputIndex]->outputs[operators[inputIndex]->numberOfOutputs] = operatorIndex;
        operators[inputIndex]->numberOfOutputs++;
        numberOfInputs--;
    }
}