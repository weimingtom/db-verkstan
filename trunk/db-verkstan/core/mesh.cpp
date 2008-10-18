#include "core/mesh.hpp"


Mesh::Mesh()
:d3d9Mesh(0)
{

}

Mesh::~Mesh()
{
  if (d3d9Mesh != 0)
        d3d9Mesh->Release();
}

Mesh* Mesh::clone()
{
    return 0;
}

void Mesh::copy(Mesh* mesh)
{

}