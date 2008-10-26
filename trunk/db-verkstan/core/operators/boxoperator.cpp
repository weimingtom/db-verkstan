#include "core/operators/boxoperator.hpp"

void BoxOperator::render()
{

}

void BoxOperator::process()
{
	if (mesh != 0)
        delete mesh;

    float width = getFloatProperty(0) / 2.0f;
    float height = getFloatProperty(1) / 2.0f;
    float depth = getFloatProperty(2) / 2.0f;

	int numVertices = 8;
	int numQuads = 6;

	mesh = new Mesh(numVertices, 0, numQuads, 1);

	int v = 0, q = 0;

	Vec3 uv1 = normalize(cross(Vec3(1,1,1), Vec3(0,1,0)));
	Vec3 uv2 = normalize(cross(Vec3(1,1,1), uv1));

	for (int z = -1; z <= 1; z += 2)
	{
		for (int y = -1; y <= 1; y += 2)
		{
			for (int x = -1; x <= 1; x += 2)			
			{
				mesh->pos(v).x = x * width;
				mesh->pos(v).y = y * height;
				mesh->pos(v).z = z * depth;
				mesh->normal(v) = normalize(Vec3(x / width, y / height, z / depth));
				mesh->uv(v) = Vec2(dot(uv1, Vec3((float)x, (float)y, (float)z)), dot(uv2, Vec3((float)x, (float)y, (float)z)));
				v++;
			}
		}
	}

	mesh->setQuad(q, 0, 2, 3, 1);   q++;
	mesh->setQuad(q, 4, 5, 7, 6);   q++;
	mesh->setQuad(q, 6, 7, 3, 2);   q++;
	mesh->setQuad(q, 0, 1, 5, 4);   q++;
	mesh->setQuad(q, 0, 4, 6, 2);   q++;
	mesh->setQuad(q, 1, 3, 7, 5);   q++;
}
