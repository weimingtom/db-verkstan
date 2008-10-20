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

    LPD3DXMESH tmpMesh;
    D3DXCreateTorus(globalDirect3DDevice, 
                    innerRadius, 
                    outerRadius, 
                    (int)sides, 
                    (int)rings, 
                    &tmpMesh, 
                    NULL);
    tmpMesh->CloneMeshFVF(NULL, 
                          FVF_VERTEX,
                          globalDirect3DDevice,
                          &mesh->d3d9Mesh);
    tmpMesh->Release();
}
