#include "db-util.hpp"
#include "builder.hpp"
#include "internaloperator.hpp"
#include "filters.hpp"

#define DB_EDITOR 1

LPDIRECT3DDEVICE9 Builder::device = 0;

void Builder::setLoadCallback(BuilderLoadCallback* callback)
{

}

Texture* Builder::getTexture(unsigned int id)
{
    return textures[id]; 
}

Mesh* Builder::getMesh(unsigned int id)
{
    return meshes[id];
}

Renderable* Builder::getRenderable(unsigned int id)
{
    return renderables[id];
}


// We define a couple of macros we don't need (they are used
// for the editor) to do nothing.
#define DEF_OP_FOR_EDITOR(opNameChars, opFilterType, opType, opRendererClass)
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
#define DEF_OP_FOR_LOADER(opFilterType, _numberOfConstantInputs, _numberOfProperties, ...) \
    unsigned char opFilterType##PropertyTypes[_numberOfProperties] = {__VA_ARGS__};
#define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opFilterType, _numberOfConstantInputs) \
// We includes all operator defines to create the variables.
#define OPERATOR_DEFINES 1
#include "operators.hpp"
#undef OPERATOR_DEFINES

unsigned char findLowestOperatorType(short type, const unsigned char* data)
{
    unsigned char result = 255;
    for (int i = 0; i < InternalOperator::numberOfOperators; i++)
    {
        short index = i + 2;
        unsigned char d = data[index];
        if (d < result && d > type)
            result = d;
    }

    return result;
}

short findNextIndexOfOperatorType(short type, short index, const unsigned char* data)
{    
    for (int i = 0; i < InternalOperator::numberOfOperators; i++)
    {
        if (i > index && data[i + 2] == type)
            return i;
    }

    return -1;
}

void Builder::load(const unsigned char* data)
{
    const unsigned char* dataptr = data;
    InternalOperator::numberOfOperators = *(reinterpret_cast<const unsigned short*>(dataptr));
    dataptr += 2;

    unsigned char lowest = findLowestOperatorType(0, data);
    // These variables contain information about the operators.
    int* instanceNumberOfProperties = new int[InternalOperator::numberOfOperators];
    int* instancePropertyTypes = new int[InternalOperator::numberOfOperators];
    int* instanceNumberOfConstantInputs = new int[InternalOperator::numberOfOperators];

    for (short operatorIndex = 0; operatorIndex < InternalOperator::numberOfOperators; operatorIndex++)
    {
        unsigned int filterType = (unsigned int)(*dataptr++);
        InternalOperator::operators[operatorIndex] = new InternalOperator(filterType);
        // We redefine the macros to instanciate operators and fill the instance variables with values.
    #undef DEF_OP_FOR_LOADER
    #undef DEF_OP_FOR_LOADER_WITH_NO_PROPS
    #define DEF_OP_FOR_LOADER(opFilterType, _numberOfConstantInputs, _numberOfProperties, ...) \
        if (opFilterType == filterType) \
        {\
            instanceNumberOfProperties[operatorIndex] = _numberOfProperties;\
            instancePropertyTypes[operatorIndex] =  (int)opFilterType##PropertyTypes;\
            instanceNumberOfConstantInputs[operatorIndex] = _numberOfConstantInputs;\
        }
    #define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opFilterType, _numberOfConstantInputs)\
        if (opFilterType == filterType) \
        {\
            instanceNumberOfProperties[operatorIndex] = 0;\
            instanceNumberOfConstantInputs[operatorIndex] =_numberOfConstantInputs;\
        }
    #define OPERATOR_DEFINES 1
    #include "operators.hpp"
    #undef OPERATOR_DEFINES
    }

    // Load the operators' properties
    short operatorType = -1;
    while (true)
    {
        operatorType = findLowestOperatorType(operatorType, data);

        if (operatorType == 255)
            break;

        short operatorIndex = findNextIndexOfOperatorType(operatorType, -1, data);
        unsigned char numberOfProperties = instanceNumberOfProperties[operatorIndex];
        operatorIndex = -1;
        for (unsigned char propertyIndex = 0; 
             propertyIndex < numberOfProperties; 
             propertyIndex++)
        {
            while (true)
            {        
                operatorIndex = findNextIndexOfOperatorType(operatorType, operatorIndex, data);

                if (operatorIndex < 0)
                    break;

                InternalOperator* op =  InternalOperator::operators[operatorIndex];
                unsigned char* propertyTypes = (unsigned char*)instancePropertyTypes[operatorIndex];
                unsigned char propertyType = propertyTypes[propertyIndex];
                switch (propertyType)
                {
                case 0: // Byte
                    op->properties[propertyIndex].byteValue = *dataptr++;
                    break;
                case 1: // Int
                    op->properties[propertyIndex].intValue = *(reinterpret_cast<const short*>(dataptr));
                    dataptr += 2;
                    break;
                case 2: // Float
                    op->properties[propertyIndex].floatValue = *(reinterpret_cast<const float*>(dataptr));
                    dataptr += 4;
                    break;
                case 3: // Color
                    op->properties[propertyIndex].colorValue.r = *dataptr++ / 256.0f;
                    op->properties[propertyIndex].colorValue.g = *dataptr++ / 256.0f;
                    op->properties[propertyIndex].colorValue.b = *dataptr++ / 256.0f;
                    break;
                case 4: // Vector
                    {
                    float x = *(reinterpret_cast<const float*>(dataptr));
                    dataptr += 4;
                    float y = *(reinterpret_cast<const float*>(dataptr));
                    dataptr += 4;
                    float z = *(reinterpret_cast<const float*>(dataptr));
                    dataptr += 4;
                    op->properties[propertyIndex].vectorValue = D3DXVECTOR3(x, y, z);
                    break;
                    }
                case 5: // String
                    {
                    unsigned short length = *(reinterpret_cast<const unsigned short*>(dataptr));
                    dataptr += 2;
                    for (unsigned short charIndex = 0; charIndex < length; charIndex++)
                        op->properties[propertyIndex].stringValue[charIndex] = *dataptr++;
                    op->properties[propertyIndex].stringValue[length] = '\0';
                    break;
                    }
                   
                }
            }
        }
    }
    // Load the operators inputs
    unsigned char* instanceNumberOfInputs = new unsigned char[InternalOperator::numberOfOperators];
    for (unsigned short operatorIndex = 0; operatorIndex < InternalOperator::numberOfOperators; operatorIndex++)
    {
        if (instanceNumberOfConstantInputs[operatorIndex] == -1)
            instanceNumberOfInputs[operatorIndex] = *dataptr++;
        else
            instanceNumberOfInputs[operatorIndex] = instanceNumberOfConstantInputs[operatorIndex];
    }
   
    for (unsigned short operatorIndex = 0; operatorIndex < InternalOperator::numberOfOperators; operatorIndex++)
    {
        unsigned char numberOfInputs = instanceNumberOfInputs[operatorIndex];
        short inputIndex;

        while(numberOfInputs > 0)
        {
            if (numberOfInputs == instanceNumberOfInputs[operatorIndex])
                inputIndex = (*(reinterpret_cast<const short*>(dataptr))) + operatorIndex;
            else
                inputIndex += *(reinterpret_cast<const short*>(dataptr));

            dataptr+=2;
            InternalOperator::operators[operatorIndex]->inputs[InternalOperator::operators[operatorIndex]->numberOfInputs] = inputIndex;
            InternalOperator::operators[operatorIndex]->numberOfInputs++;
            InternalOperator::operators[inputIndex]->outputs[InternalOperator::operators[inputIndex]->numberOfOutputs] = operatorIndex;
            InternalOperator::operators[inputIndex]->numberOfOutputs++;
            numberOfInputs--;
        }
    }

    // Load exports
    unsigned short numberOfTextures = *(reinterpret_cast<const unsigned short*>(dataptr));
    dataptr += 2;
    unsigned short numberOfMeshes = *(reinterpret_cast<const unsigned short*>(dataptr));
    dataptr += 2;
    unsigned short numberOfRenderables = *(reinterpret_cast<const unsigned short*>(dataptr));
    dataptr += 2;

    for (unsigned short i = 0; i < numberOfTextures; i++)
    {
        unsigned short id = *(reinterpret_cast<const unsigned short*>(dataptr));
        dataptr += 2;
        InternalOperator::operators[id]->cascadeProcess();
        textures[i] = InternalOperator::operators[id]->texture;
    }

    for (unsigned short i = 0; i < numberOfMeshes; i++)
    {
        unsigned short id = *(reinterpret_cast<const unsigned short*>(dataptr));
        dataptr += 2;
        InternalOperator::operators[id]->cascadeProcess();
        meshes[i] = InternalOperator::operators[id]->mesh;
    }

    for (unsigned short i = 0; i < numberOfRenderables; i++)
    {
        unsigned short id = *(reinterpret_cast<const unsigned short*>(dataptr));
        dataptr += 2;
        InternalOperator::operators[id]->cascadeProcess();
        renderables[i] = InternalOperator::operators[id]->renderable;
    }
}