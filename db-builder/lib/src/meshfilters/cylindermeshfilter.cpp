#include "db-util.hpp"
#include "filters.hpp"
#include "mesh.hpp"

Mesh* MeshFilters::cylinder(float radius1, 
                            float radius2, 
                            float length,
                            int slices,
                            int stacks,
                            int capCircles1,
                            int capCircles2)
{
	int capVerts1 = capCircles1 == 0 ? 0 : capCircles1 * slices + 1;
	int capQuads1 = capCircles2 == 0 ? 0 : capCircles1 * slices;
	int capTriangles1 = slices;
	int capVerts2 = capCircles2 == 0 ? 0 : capCircles2 * slices + 1;
	int capQuads2 = capCircles2 * slices;
	int capTriangles2 = capCircles2 == 0 ? 0 :slices;
	
	int mantleVerts = stacks == 0 ? 0 : (stacks + 1) * (slices + 1);
	int mantleQuads = stacks * slices;

	Mesh* newMesh = new Mesh(capVerts1 + capVerts2 + mantleVerts, 
                             capTriangles1 + capTriangles2, 
                             capQuads1 + capQuads2 + mantleQuads);

	int capVertBase1 = mantleVerts;
	int capVertBase2 = mantleVerts + capVerts1;

	int capQuadBase1 = mantleQuads;
	int capQuadBase2 = mantleQuads + capQuads1;

	if (mantleVerts > 0)
	{
		int vert = 0, quad = 0;

		for (int x = 0; x <= slices; x++)
		{
			float u = x / (float)slices;
			Vec2 p(cos(u * 2 * M_PI), sin(u * 2 * M_PI));

			for (int y = 0; y <= stacks; y++)
			{
				float v = y / (float)stacks;
				float r = radius1 + (radius2 - radius1) * v;
				
				newMesh->pos(vert) = Vec3(p.x * r, v * length, p.y * r);
				newMesh->normal(vert) = Vec3(p.x, 0.0f, p.y);
				newMesh->uv(vert) = Vec2(u, 1.0f - v);

				if (x != slices && y != stacks)
				{
					newMesh->setQuad(quad, vert, vert + 1, vert + stacks + 2, vert + stacks + 1);
					quad++;
				}

				vert++;
			}
		}
	}

	int tri = 0;

	int circles = capCircles1;
	int vertBase = capVertBase1;
	float radius = radius1;
	int quad = capQuadBase1;	
	float h = 0.0f;
	Vec3 n = Vec3(0.0f, -1.0f, 0.0f);
	bool inv = false;

	for (int i = 0; i < 2; i++)
	{
		int vert = 0;

		if (circles)
		{
			for (int x = 0; x < slices; x++)
			{
				float u = (inv ? slices - x - 1 : x) / (float)slices;

				for (int y = 0; y < circles; y++)
				{
					float v = 1.0f - y / (float)circles;
					float r = v * radius;
					
					Vec2 p(cos(u * 2 * M_PI), sin(u * 2 * M_PI));

					newMesh->pos(vert + vertBase) = Vec3(p.x * r, h, p.y * r);
					newMesh->normal(vert + vertBase) = n;
					Vec2 uv = (p * v + Vec2(1.0f, 1.0f)) * 0.5f;
					newMesh->uv(vert + vertBase) = Vec2(uv.x, inv ? 1.0f - uv.y : uv.y);

					if (y != circles - 1)
					{
						int x2 = (x + 1) % slices;
						int y2 = (y + 1) % circles;

						int v1 = x * circles + y;
						int v2 = x2 * circles + y;
						int v3 = x2 * circles + y2;
						int v4 = x * circles + y2;
						newMesh->setQuad(quad, v1 + vertBase, v2 + vertBase, v3 + vertBase, v4 + vertBase);
						quad++;
					}
					else
					{
						int x2 = (x + 1) % slices;

						int v1 = x * circles + y;
						int v2 = x2 * circles + y;
						int v3 = slices * circles;
						newMesh->setTriangle(tri, v1 + vertBase, v2 + vertBase, v3 + vertBase);
						tri++;
					}

					vert++;
				}
			}
			
			newMesh->pos(vert + vertBase) = Vec3(0.0f, h, 0.0f);
			newMesh->normal(vert + vertBase) = n;
			newMesh->uv(vert + vertBase) = Vec2(0.5f, 0.5f);
			vert++;
		}

		circles = capCircles2;
		vertBase = capVertBase2;
		radius = radius2;
		quad = capQuadBase2;
		h = length;
		n = Vec3(0.0f, 1.0f, 0.0f);
		inv = true;
	}

    return newMesh;
}