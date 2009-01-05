#include "weldoperator.hpp"

static Vec3 projector;
static Mesh *srcMesh;

static int projectedComparator(const void *_i1, const void *_i2)
{
	int i1 = *(int *)_i1;
	int i2 = *(int *)_i2;

	Vec3 p1 = srcMesh->pos(i1);
	Vec3 p2 = srcMesh->pos(i2);

	float j1 = dot(p1, projector);
	float j2 = dot(p2, projector);

	return j1 < j2 ? -1 : 1;
}

void WeldOperator::process()
{
	// TODO: Weld away triangles and quads properly

    if (mesh != 0)
        delete mesh;

	srcMesh = getInput(0)->mesh;

	int *welded = new int[srcMesh->getNumVertices()];
	int *numInputs = new int[srcMesh->getNumVertices()];

	memset(welded, -1, sizeof(int) * srcMesh->getNumVertices());
	memset(numInputs, 0, sizeof(int) * srcMesh->getNumVertices());

	projector = normalize(Vec3(0.2f, 0.3f, 0.5f));
	static const float epsilon = 0.0001f;

	int *sortedVerts = new int[srcMesh->getNumVertices()];

	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		sortedVerts[i] = i;
	}

	qsort(sortedVerts, srcMesh->getNumVertices(), sizeof(int), projectedComparator);

	int numVertices = 0;

	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		int v1 = sortedVerts[i];

		if (welded[v1] >= 0) {
			continue;
		}

		welded[v1] = numVertices;
		numInputs[numVertices]++;
		Vec3 pos1 = srcMesh->pos(v1);

		for (int j = i + 1; j < srcMesh->getNumVertices(); j++)
		{
			int v2 = sortedVerts[j];
			Vec3 pos2 = srcMesh->pos(v2);

			float pl = dot(pos1, projector) - dot(pos2, projector);

			if (pl * pl > epsilon)
			{
				break;
			}

			if (lengthSq(pos1 - pos2) < epsilon)
			{
				welded[v2] = numVertices;
				numInputs[numVertices]++;
			}
		}

		numVertices++;
	}

	mesh = new Mesh(numVertices, srcMesh->getNumTriangles(), srcMesh->getNumQuads(), srcMesh->getNumUVSets());
	mesh->setSelectedUVSet(srcMesh->getSelectedUVSet());

	for(int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		int v = welded[i];
		mesh->pos(v) += srcMesh->pos(i);
		mesh->normal(v) += srcMesh->normal(i);

		for (int s = 0; s < mesh->getNumUVSets(); s++)
		{
			mesh->uv(v, s) += srcMesh->uv(i, s);
		}
	}

	for(int i = 0; i < mesh->getNumVertices(); i++)
	{
		int n = numInputs[i];
		float k = 1.0f / n;
		
		if (n == 1) {
			continue;
		}

		mesh->pos(i) *= k;
		mesh->normal(i) = normalize(mesh->normal(i));
		
		for (int s = 0; s < mesh->getNumUVSets(); s++)
		{
			mesh->uv(i, s) *= k;
		}
	}

	for (int i = 0; i < mesh->getNumFaces(); i++)
	{
		int sides;
		int *srcFace = srcMesh->face(i, sides);
		int dstFace[4];
		for (int s = 0; s < sides; s++)
		{
			dstFace[s] = welded[srcFace[s]];
		}
		mesh->setFace(i, dstFace);
	}

	delete[] welded;
	delete[] sortedVerts;
	delete[] numInputs;
}