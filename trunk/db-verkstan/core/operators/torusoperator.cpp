#include "core/operators/torusoperator.hpp"

void TorusOperator::render()
{

}

void TorusOperator::process()
{
    if (mesh != 0)
        delete mesh;

    mesh = new Mesh();

    float innerRadius = getFloatProperty(0);
    float outerRadius = getFloatProperty(1);
    unsigned char sides = getByteProperty(2);
    unsigned char rings = getByteProperty(3);

    D3DXCreateTorus(globalDirect3DDevice, 
                    innerRadius, 
                    outerRadius, 
                    (int)sides, 
                    (int)rings, 
                    &mesh->d3d9Mesh, 
                    NULL);
}
