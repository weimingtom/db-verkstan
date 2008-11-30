#include "core/operators/torusoperator.hpp"

void TorusOperator::process()
{/*
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

    Vertex* vertices;
    mesh->d3d9Mesh->LockVertexBuffer(0,(void**)&vertices);

    int numberOfVertices =  mesh->d3d9Mesh->GetNumVertices();

    for (int i = 0; i < numberOfVertices; i++) 
    {
        vertices->v = acosf(vertices->position.y / innerRadius) / 2 * D3DX_PI;
        vertices->u = (acosf(vertices->position.x / (innerRadius + outerRadius * cos(2 * D3DX_PI * vertices->v)))) * 2 * D3DX_PI;
        vertices++;
    }*/
}
