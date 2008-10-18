#pragma once

#include <d3d9.h>
#include <d3dx9.h>

/**
 * Helper class that wraps a D3D9 mesh.
 */
class Mesh
{
public:
    Mesh();
    ~Mesh();
    Mesh* clone();
    void copy(Mesh* mesh);
    LPD3DXMESH d3d9Mesh;
    bool d3d9MeshDirty;
};