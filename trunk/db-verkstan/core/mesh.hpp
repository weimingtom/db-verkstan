#pragma once

#include <d3d9.h>
#include <d3dx9.h>

struct Vertex
{
    D3DXVECTOR3 position; 
    D3DXVECTOR3 normal;
    float u, v;
};

#define FVF_VERTEX D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1

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
    D3DXVECTOR3 scale; 
    D3DXVECTOR3 rotation; 
    D3DXVECTOR3 translation; 
};