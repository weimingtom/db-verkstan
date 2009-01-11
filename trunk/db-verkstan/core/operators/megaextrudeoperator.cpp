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

    System::Console::WriteLine(srcMesh->getNumFaces() + " " + srcMesh->getNumQuads() + " " + srcMesh->getNumTriangles());
    int numberOfVertices = srcMesh->getNumVertices();
    int numberOfQuads = srcMesh->getNumQuads();
	
    // Calculate the new number of quads and vertices.
    // The number of triangles will be unchanged.
    for (int i = 0; i < srcMesh->getNumFaces(); i++)
    {
        int n;
        int *face = srcMesh->face(i, n);

        if (srcMesh->faceSelected(i))
        {
            numberOfQuads += n * count;
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

        if (srcMesh->faceSelected(i))
        {
            int* lastIndices = face;
            Vec3* lastPositions = new Vec3[n];
            for (int f = 0; f < n; f++)
                lastPositions[f] = srcMesh->pos(face[f]);

            Vec3 incrementVector = normalize(srcMesh->getFaceNormal(i));
            incrementVector.x *= distance;
            incrementVector.y *= distance;
            incrementVector.z *= distance;

            for (int c = 0; c < count; c++)
            {
                int* currentIndices = new int[n];
                for (int f = 0; f < n; f++)
                {
                    Vec3 pos = lastPositions[f] + incrementVector;
                    mesh->pos(vertexIndex) = pos;
                    currentIndices[f] = vertexIndex;
                    lastPositions[f] = pos;
                    vertexIndex++;
                }

                for (int f = 0; f < n; f++)
                {
                     mesh->setQuad(quadIndex, 
                                   lastIndices[f], 
                                   lastIndices[(f + 1) % n], 
                                   currentIndices[(f + 1) % n],
                                   currentIndices[f]);
                     quadIndex++;
                }

                for (int f = 0; f < n; f++)
                {
                    lastIndices[f] = currentIndices[f];
                    face[f] = currentIndices[f];
                }

                delete[] currentIndices;
            }

            delete[] lastPositions;
        }

        if (n == 3)
        {
            mesh->setTriangle(triangleIndex, face[0], face[1], face[2]);
            triangleIndex++;
        }
        else
        {
            mesh->setQuad(quadIndex, face[0], face[1], face[2],  face[3]);
            quadIndex++;
        }
    }

    mesh->recalculateNormals();
}
