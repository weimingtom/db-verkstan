#include "core/operators/sphereoperator.hpp"

void SphereOperator::render()
{

}

void SphereOperator::process()
{
	if (mesh != 0)
        delete mesh;
    
	float radius = getFloatProperty(0);
    unsigned char slices = getByteProperty(1);
    unsigned char stacks = getByteProperty(2);

	int numVertices = 2 + slices * stacks;
	int numQuads = slices * (stacks - 1);
    int numTriangles = slices * 2;

	mesh = new Mesh(numVertices, numTriangles + numQuads * 2, 0, 1);

	int v = 0;
	int t = 0;

	for(int i = 0; i < stacks; i++)
	{
		float a = (((float)i + 1) / (stacks + 1)) * (float)M_PI;
		float cosa = cosf(a);
		float sina = sinf(a);

		for(int j = 0; j < slices; j++)
		{
			float b = (float)(j * M_PI * 2 / slices);
			mesh->normal(v) = Vec3(cosf(b) * sina, sinf(b) * sina, cosa * radius);
			mesh->pos(v) = mesh->normal(v) * radius;
			mesh->uv(v) = Vec2(a, b);			
			mesh->triangle(t)[0] = v;
			mesh->triangle(t)[1] = v - 1 < 0 ? 0 : v - 1;
			mesh->triangle(t)[2] = v - slices < 0 ? 0 : v - slices;
			v++; t++;
		}
	}

	/*
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
    tmpMesh->Release();*/
}
