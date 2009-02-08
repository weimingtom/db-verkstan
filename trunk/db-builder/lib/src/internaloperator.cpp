#include "db-util.hpp"
#include "internaloperator.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "filters.hpp"
#include <string.h>

InternalOperator* InternalOperator::operators[DB_MAX_OPERATORS];
short InternalOperator::numberOfOperators;

InternalOperator::InternalOperator(unsigned int filterType_) :
	mesh(0),
	texture(0),
    renderable(0),
	numberOfInputs(0),
	numberOfOutputs(0),
	dirty(true),
	filterType(filterType_)
{
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        inputs[i] = -1;
    for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
        outputs[i] = -1;
}

#ifdef DB_EDITOR
InternalOperator::~InternalOperator()
{
    deviceLost();
}
#endif

void InternalOperator::cascadeProcess()
{  
    if (!isDirty())
        return;

    for (int i = 0; i < numberOfInputs; i++)
        operators[inputs[i]]->cascadeProcess();
   
    process();
    dirty = false;
}

void InternalOperator::process()
{
	if (texture != 0)
	{
		delete texture;
		texture = 0;
	}

	if (mesh != 0)
	{
		delete mesh;
		// The mesh can also be the renderable, don't delete twice
		if (renderable == mesh)
			renderable = 0;
		mesh = 0;
	}
	
	if (renderable != 0) 
	{
		delete renderable;
		renderable = 0;
	}

    switch (filterType)
    {
        /*
    case BlurTextureFilter:
        texture = TextureFilters::blur(getInput(0)->texture, 
                                       getByteProperty(0), 
                                       getByteProperty(2),
                                       getByteProperty(3),
                                       getByteProperty(1) + 1);
        break;
        */
    case 0:
        break;
    case 1:
        {
        Texture* inputTexture = 0;

        if (getInput(0) != 0)
            inputTexture = getInput(0)->texture;

        texture = TextureFilters::pixels(inputTexture, 
                                         getColorProperty(0), 
                                         getColorProperty(1),
                                         getByteProperty(2),
                                         getByteProperty(3));
        break;
        }
    default:
        break;
    }
    

	if (mesh != 0 && renderable == 0)
	{
		// Use mesh as renderable
		renderable = mesh;
	}
}

unsigned char InternalOperator::getByteProperty(int index)
{
    return properties[index].byteValue;
}

int InternalOperator::getIntProperty(int index)
{
    return properties[index].intValue;
}

float InternalOperator::getFloatProperty(int index)
{
    return properties[index].floatValue;
}

const char* InternalOperator::getStringProperty(int index)
{
    return properties[index].stringValue;
}

D3DXCOLOR InternalOperator::getColorProperty(int index)
{
    return properties[index].colorValue;
}

D3DXVECTOR3 InternalOperator::getVectorProperty(int index)
{
    return properties[index].vectorValue;
}

bool InternalOperator::isDirty()
{
    return dirty;
}

void InternalOperator::setDirty(bool dirty)
{
    for (int i = 0; i < numberOfOutputs; i++)
        operators[outputs[i]]->setDirty(dirty);

    this->dirty = dirty;
}

InternalOperator* InternalOperator::getInput(int index)
{
    if (inputs[index] == -1)
        return 0;
    return operators[inputs[index]];
}

#ifdef DB_EDITOR
void InternalOperator::deviceLost()
{
    if (texture != 0)
        texture->setDirty();

    if (mesh != 0)
        mesh->setDirty();
}
#endif
