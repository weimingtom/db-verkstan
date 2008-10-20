#include "core/operators/cylinderoperator.hpp"

void CylinderOperator::render()
{

}

void CylinderOperator::process()
{
    if (mesh != 0)
        delete mesh;

    mesh = new Mesh();

    float radius1 = getFloatProperty(0);
    float radius2 = getFloatProperty(1);
    float length = getFloatProperty(2);
    unsigned char slices = getByteProperty(3);
    unsigned char stacks = getByteProperty(4);

    LPD3DXMESH tmpMesh;
    D3DXCreateCylinder(globalDirect3DDevice, 
                       radius1,
                       radius2,
                       length,
                       slices,
                       stacks,
                       &tmpMesh, 
                       NULL);
    tmpMesh->CloneMeshFVF(NULL, 
                          FVF_VERTEX,
                          globalDirect3DDevice,
                          &mesh->d3d9Mesh);
    tmpMesh->Release();
}
