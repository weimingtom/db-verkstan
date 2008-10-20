#include "core/operators/texturemappingoperator.hpp"

void TextureMappingOperator::render()
{

}

void TextureMappingOperator::process()
{
    if (mesh != 0)
        delete mesh;

    Operator* input = getInput(0);
    mesh = input->mesh->clone();

    Vertex* vertices;
    mesh->d3d9Mesh->LockVertexBuffer(0,(void**)&vertices);

    int numberOfVertices =  mesh->d3d9Mesh->GetNumVertices();

    D3DXVECTOR3 min, max;
    D3DXComputeBoundingBox(&vertices->position, 
                           numberOfVertices, 
                           D3DXGetFVFVertexSize(mesh->d3d9Mesh->GetFVF()), 
                           &min, 
                           &max);

    D3DXVECTOR3 center;
    center = (max + min) * 0.5f;

    System::Console::WriteLine("Numer of vertices = " + numberOfVertices);

    for (int i = 0; i < numberOfVertices; i++) 
    {
        D3DXVECTOR3 v;
        v = vertices->position - center;
        D3DXVec3Normalize(&v, &v);

        vertices->u = asinf(v.x) / D3DX_PI + 0.5f;
        vertices->v = asinf(v.y) / D3DX_PI + 0.5f;

        vertices++;
    }

    mesh->d3d9Mesh->UnlockVertexBuffer();
}
