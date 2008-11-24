#include "core/operators/randomselectionoperator.hpp"

void RandomSelectionOperator::render(int tick)
{

}

void RandomSelectionOperator::process()
{
    if (mesh != 0)
        delete mesh;

	mesh = getInput(0)->mesh->clone();

	int probability = getByteProperty(0);
	int seed = getByteProperty(0);

	srand(seed);

	for (int i = 0; i < mesh->getNumFaces(); i++)
	{
		mesh->faceSelected(i) = (rand() % 255) < probability;
/*
		if (mesh->faceSelected(i)) 
		{
			System::Console::WriteLine("Selected face: " + i);
		}*/
	}
}
