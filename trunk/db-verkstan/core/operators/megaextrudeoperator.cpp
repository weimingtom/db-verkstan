#include "core/operators/megaextrudeoperator.hpp"

void MegaExtrudeOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

	float distance = getFloatProperty(0);
    unsigned char count = getByteProperty(1);
    D3DXVECTOR3 scaleVector = getVectorProperty(2);
    D3DXVECTOR3 rotationVector = getVectorProperty(3);
    D3DXMATRIX scaleMatrix;
    D3DXMatrixScaling(&scaleMatrix, 
                      scaleVector.x, 
                      scaleVector.y, 
                      scaleVector.z);
    D3DXMATRIX rotationXMatrix;
    D3DXMatrixRotationX(&rotationXMatrix, rotationVector.x);
    D3DXMATRIX rotationYMatrix;
    D3DXMatrixRotationY(&rotationYMatrix, rotationVector.y);
    D3DXMATRIX rotationZMatrix;
    D3DXMatrixRotationZ(&rotationZMatrix, rotationVector.z);
    D3DXMATRIX translationMatrix;
    D3DXMatrixTranslation(&translationMatrix,
                          0.0f,
                          distance,
                          0.0f);
    D3DXMATRIX extrudeMatrix = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;
    D3DXMATRIX matrix;
    D3DXMatrixIdentity(&matrix);

	Mesh *srcMesh = getInput(0)->mesh;

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
    
    Vec3* lastPositions = new Vec3[4];
    int* lastIndices = new int[4];
    int* currentIndices = new int[4];

    for (int i = 0; i < srcMesh->getNumFaces(); i++)
    {
        int n;
        int *face = srcMesh->face(i, n);   

        for (int f = 0; f < n; f++)
        {
            lastPositions[f] = srcMesh->pos(face[f]);
            lastIndices[f] = face[f];
        }

        if (srcMesh->faceSelected(i))
        {
            // Get our base vectors.
            Vec3 faceBase1 = normalize(srcMesh->pos(face[0]));
            Vec3 faceBase2 = normalize(srcMesh->getFaceNormal(i));
            Vec3 faceBase3 = normalize(cross(faceBase2, faceBase1));

            D3DXMATRIX toFaceBaseMatrix = D3DXMATRIX(faceBase1.x, faceBase2.x, faceBase3.x, 0.0f,
                                                     faceBase1.y, faceBase2.y, faceBase3.y, 0.0f,
                                                     faceBase1.z, faceBase2.z, faceBase3.z, 0.0f,
                                                     0.0f,               0.0f,        0.0f, 1.0f);
            D3DXMATRIX fromFaceBaseMatrix;
            D3DXMatrixInverse(&fromFaceBaseMatrix, NULL, &toFaceBaseMatrix);
                                
            for (int c = 0; c < count; c++)
            {
                for (int f = 0; f < n; f++)
                {
                    Vec3 pos = lastPositions[f];
                    Vec4 posInFaceBase;
                    D3DXVec3Transform(&posInFaceBase, &pos, &toFaceBaseMatrix);
                    Vec4 posTransformedInFaceBase;
                    D3DXVec4Transform(&posTransformedInFaceBase, &posInFaceBase, &extrudeMatrix);
                    Vec4 posTransformed;
                    D3DXVec4Transform(&posTransformed, &posTransformedInFaceBase, &fromFaceBaseMatrix);
                    mesh->pos(vertexIndex) = Vec3(posTransformed.x,
                                                  posTransformed.y,
                                                  posTransformed.z);
                    currentIndices[f] = vertexIndex;
                    lastPositions[f] = Vec3(posTransformed.x,
                                            posTransformed.y,
                                            posTransformed.z);
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
                }  

                matrix *= extrudeMatrix;
            }
        }
        
       
        if (n == 3)
        {
            mesh->setTriangle(triangleIndex, lastIndices[0], lastIndices[1], lastIndices[2]);
            triangleIndex++;
        }
        else
        {
            mesh->setQuad(quadIndex, lastIndices[0], lastIndices[1], lastIndices[2],  lastIndices[3]);
            quadIndex++;
        }
    }

    delete[] lastIndices;
    delete[] currentIndices;
    delete[] lastPositions;

    mesh->recalculateNormals();
}
