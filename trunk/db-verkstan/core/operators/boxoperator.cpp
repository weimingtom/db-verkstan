#include "core/operators/boxoperator.hpp"

void BoxOperator::render()
{

}

void BoxOperator::process()
{
    if (mesh != 0)
        delete mesh;

    mesh = new Mesh();

    float width = getFloatProperty(0);
    float height = getFloatProperty(1);
    float depth = getFloatProperty(2);

    LPD3DXMESH tmpMesh;
    D3DXCreateBox(globalDirect3DDevice,
                  width,
                  height,
                  depth,
                  &tmpMesh, 
                  NULL);
    tmpMesh->CloneMeshFVF(NULL, 
                          FVF_VERTEX,
                          globalDirect3DDevice,
                          &mesh->d3d9Mesh);
    tmpMesh->Release();

}
