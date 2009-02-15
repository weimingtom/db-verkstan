#include "db-util.hpp"
#include "filters.hpp"
#include "mesh.hpp"

Mesh* MeshFilters::megaExtrude(Mesh* mesh,
                               float distance, 
                               int count,
                               D3DXVECTOR3 scaleVector,
                               D3DXVECTOR3 rotationVector)
{

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

    int numberOfVertices = mesh->getNumVertices();
    int numberOfQuads = mesh->getNumQuads();
	
    // Calculate the new number of quads and vertices.
    // The number of triangles will be unchanged.
    for (int i = 0; i < mesh->getNumFaces(); i++)
    {
        int n;
        int *face = mesh->face(i, n);

        if (mesh->faceSelected(i))
        {
            numberOfQuads += n * count;
            numberOfVertices += n * count;
        }
    }

    Mesh* newMesh = new Mesh(numberOfVertices, mesh->getNumTriangles(), numberOfQuads, 1);

    int triangleIndex = 0;
    int quadIndex = 0;
 
    // Copy the src mesh vertices.
    for (int i = 0; i < mesh->getNumVertices(); i++)
    {
        newMesh->pos(i) = mesh->pos(i);
    }

    int vertexIndex = mesh->getNumVertices();
    // Extrude each selected face and add triangles and quads.
    
    Vec3 lastPositions[4];
    int lastIndices[4];
    int currentIndices[4];

    for (int i = 0; i < mesh->getNumFaces(); i++)
    {
        int n;
        int *face = mesh->face(i, n);   

        for (int f = 0; f < n; f++)
        {
            lastPositions[f] = mesh->pos(face[f]);
            lastIndices[f] = face[f];
        }
        
        bool faceSelected = mesh->faceSelected(i);
        
        if (faceSelected)
        {
            // Get our base vectors.
			Vec3 pos1 = mesh->pos(face[1]);
			Vec3 pos0 = mesh->pos(face[0]); 
            Vec3 faceBase1 = normalize(pos1 - pos0);
            Vec3 faceBase2 = normalize(mesh->getFaceNormal(i));
            Vec3 faceBase3 = normalize(cross(faceBase2, faceBase1));

            D3DXMATRIX fromFaceBaseMatrix = D3DXMATRIX(faceBase1.x, faceBase1.y, faceBase1.z, 0.0f,
                                                     faceBase2.x, faceBase2.y, faceBase2.z, 0.0f,
                                                     faceBase3.x, faceBase3.y, faceBase3.z, 0.0f,
                                                     0.0f,               0.0f,        0.0f, 1.0f);
            D3DXMATRIX toFaceBaseMatrix = D3DXMATRIX(faceBase1.x, faceBase2.x, faceBase3.x, 0.0f,
                                                       faceBase1.y, faceBase2.y, faceBase3.y, 0.0f,
                                                       faceBase1.z, faceBase2.z, faceBase3.z, 0.0f,
                                                       0.0f,               0.0f,        0.0f, 1.0f);
                    
            D3DXMATRIX toFaceBaseAndOrigoMatrix = toFaceBaseMatrix;
			D3DXMATRIX fromFaceBaseAndToFaceMatrix = extrudeMatrix * fromFaceBaseMatrix;

            for (int c = 0; c < count; c++)
            {
                for (int f = 0; f < n; f++)
                {
                    Vec3 pos = lastPositions[f];
                    Vec3 posInFaceBase;
                    D3DXVec3TransformCoord(&posInFaceBase, &pos, &toFaceBaseAndOrigoMatrix);
					Vec3 posTransformed;
                    D3DXVec3TransformCoord(&posTransformed, &posInFaceBase, &fromFaceBaseAndToFaceMatrix);
                    newMesh->pos(vertexIndex) = posTransformed;
                    currentIndices[f] = vertexIndex;
                    lastPositions[f] = posTransformed;
                    vertexIndex++;
                }

                for (int f = 0; f < n; f++)
                {
                     newMesh->setQuad(quadIndex, 
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
            }
        }
              
        if (n == 3)
        {
            newMesh->setTriangle(triangleIndex, lastIndices[0], lastIndices[1], lastIndices[2]);
            newMesh->triangleSelected(triangleIndex) = faceSelected;
            triangleIndex++;     
        }
        else
        {
            newMesh->setQuad(quadIndex, lastIndices[0], lastIndices[1], lastIndices[2],  lastIndices[3]);
            newMesh->quadSelected(quadIndex) = faceSelected;
            quadIndex++;         
        }
    }

    newMesh->recalculateNormals();
    return newMesh;
}