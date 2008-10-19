#include "core/mesh.hpp"

#include "core/globals.hpp"

Mesh::Mesh()
:d3d9Mesh(0)
{
    translation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

Mesh::~Mesh()
{
  if (d3d9Mesh != 0)
        d3d9Mesh->Release();
}

Mesh* Mesh::clone()
{
    Mesh* clone = new Mesh();
    d3d9Mesh->CloneMeshFVF(NULL, 
                           d3d9Mesh->GetFVF(), 
                           globalDirect3DDevice,
                           &clone->d3d9Mesh);

    return clone;
}

void Mesh::copy(Mesh* mesh)
{

}