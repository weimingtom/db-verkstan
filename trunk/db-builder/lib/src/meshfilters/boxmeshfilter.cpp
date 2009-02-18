#include "db-util.hpp"
#include "filters.hpp"
#include "mesh.hpp"

Mesh* MeshFilters::box(float width, 
                       float height, 
                       float depth,
                       int xSlices,
                       int ySlices,
                       int zSlices)
{
    Vec3 dimension(width / 2.0f, height / 2.0f, depth / 2.0f);


	int numVertices = ((1 + xSlices) * (1 + ySlices) + (1 + ySlices) * (1 + zSlices) + (1 + zSlices) * (1 + xSlices)) * 2;
	int numQuads = (xSlices * ySlices + ySlices * zSlices + zSlices * xSlices) * 2;

	Mesh* newMesh = new Mesh(numVertices, 0, numQuads, 1);

	int vert = 0, quad = 0;
	Vec3 f = Vec3(0, 0, 1);
	
	for (int sign = -1; sign <= 1; sign += 2)
	{
		for (int axis = 0; axis < 3; axis++)
		{
			Vec3 n = (float)sign * f;
			Vec3 a = Vec3(n.y, n.z, n.x);
			Vec3 b = Vec3(f.z, f.x, f.y);

			for (int y = 0; y <= ySlices; y++)
			{
				for (int x = 0; x <= xSlices; x++)
				{
					Vec2 uv(x / (float)xSlices, y / (float)ySlices);
					Vec3 pos = (uv.x * 2.0f - 1.0f) * a + (uv.y * 2.0f - 1.0f) * b + n;
					newMesh->pos(vert) = Vec3(pos.x * dimension.x, pos.y * dimension.y, pos.z * dimension.z);
					newMesh->normal(vert) = n;
					newMesh->uv(vert) = Vec2(uv.y, uv.x);

					if (y != ySlices && x != xSlices)
					{
						newMesh->setQuad(quad, vert, vert + xSlices + 1, vert + xSlices + 2, vert + 1);
                        newMesh->quadSelected(quad) = axis == 1;
						quad++;
					}

					vert++;
				}
			}

			int temp = xSlices;
			xSlices = ySlices;
			ySlices = zSlices;
			zSlices = temp;
			f = Vec3(f.y, f.z, f.x);
		}
	}

    return newMesh;
}