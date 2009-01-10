#include "core/operators/megaextrudeoperator.hpp"

void MegaExtrudeOperator::process()
{
    if (mesh != 0)
        delete mesh;

	float distance = getFloatProperty(0);
    unsigned char count = getByteProperty(1);
    Vec3 scale = getVectorProperty(3);
    Vec3 rotation = getVectorProperty(4);
    Vec3 translation = getVectorProperty(5);

	Mesh *srcMesh = getInput(0)->mesh;

    int numberOfVertices = srcMesh->getNumVertices();
    int numberOfQuads = srcMesh->getNumQuads();
	
    // Calculate the new number of quads.
    for (int i = 0; i < srcMesh->getNumFaces(); i++)
    {
        int n;
        int *face = srcMesh->face(i, n);

        if (srcMesh->faceSelected(i))
        {
            numberOfQuads += 3 * count;
            numberOfVertices += n * count;
        }
    }

    mesh = new Mesh(numberOfVertices, srcMesh->getNumTriangles(), numberOfQuads, 1);

    int triangleIndex = 0;
    int quadIndex = 0;
 
    // Copy the src mesh vertices.
    for (int i = 0; i < srcMesh->getNumVertices(); i++)
    {
        mesh->pos(i) = srcMesh->pos(i);
    }

    int vertexIndex = srcMesh->getNumVertices();
    // Extrude each selected face and add triangles and quads.
    for (int i = 0; i < srcMesh->getNumFaces(); i++)
    {
        int n;
        int *face = srcMesh->face(i, n);

        int v0 = face[0];
        int v1 = face[1];
        int v2 = face[2];
        int v3 = face[3]; // Might segfault...

        if (srcMesh->faceSelected(i))
        {
            Vec3* lastPositions = new Vec3[n];
            for (int f = 0; f < n; f++)
                lastPositions[f] = srcMesh->pos(face[f]);

            Vec3 incrementVector = normalize(srcMesh->getFaceNormal(i));
            incrementVector.x *= distance;
            incrementVector.y *= distance;
            incrementVector.z *= distance;

            for (int c = 0; c < count; c++)
            {
                for (int f = 0; f < n; f++)
                {
                    Vec3 pos = lastPositions[f] + incrementVector;
                    mesh->pos(vertexIndex) = pos;
                    lastPositions[f] = pos;
                    vertexIndex++;

                    mesh->setQuad(quadIndex, 
                                  vertexIndex - n, 
                                  vertexIndex - n + 1, 
                                  vertexIndex,
                                  vertexIndex + 1);
                    quadIndex++;
                }

                if (n == 3)
                {
                     mesh->setTriangle(triangleIndex, 
                                       vertexIndex - 3, 
                                       vertexIndex - 2, 
                                       vertexIndex - 1);
                     triangleIndex++;
                }
                if (n == 4)
                {
                    mesh->setQuad(quadIndex, 
                                  vertexIndex - 4, 
                                  vertexIndex - 3, 
                                  vertexIndex - 2,
                                  vertexIndex - 1);
                    quadIndex++;
                }
            }

            delete[] lastPositions;
        }

        /*
        if (n == 3)
        {
            mesh->setTriangle(triangleIndex, v0, v1, v2);
            triangleIndex++;
        }
        else
        {
            mesh->setQuad(quadIndex, v0, v1, v2, v3);
            quadIndex++;
        }*/

        mesh->recalculateNormals();
    }
}
