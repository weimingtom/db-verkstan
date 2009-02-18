#include "db-util.hpp"
#include "filters.hpp"
#include "mesh.hpp"

Mesh* MeshFilters::randomSelect(Mesh* mesh,
                                int probability, 
                                int seed,
                                bool inPlace)
{        
    Mesh* newMesh = mesh->clone();

    srand(seed);

	for (int i = 0; i < mesh->getNumFaces(); i++)
	{
        newMesh->faceSelected(i) = (rand() % 255) < probability;
	}

    return newMesh;
}