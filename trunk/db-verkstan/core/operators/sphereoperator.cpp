#include "core/operators/sphereoperator.hpp"

void SphereOperator::render()
{

}

void SphereOperator::process()
{
    if (mesh != 0)
        delete mesh;

    mesh = new Mesh();

    float radius = getFloatProperty(0);
    unsigned char slices = getByteProperty(1);
    unsigned char stacks = getByteProperty(2);

    LPD3DXMESH tmpMesh;
    D3DXCreateSphere(globalDirect3DDevice, 
                     radius,
                     (int)slices,
                     (int)stacks,
                     &tmpMesh, 
                     NULL);
    tmpMesh->CloneMeshFVF(NULL, 
                          FVF_VERTEX,
                          globalDirect3DDevice,
                          &mesh->d3d9Mesh);
    tmpMesh->Release();
}
