#include "core/operators/transformmeshoperator.hpp"

void TransformMeshOperator::render()
{

}

void TransformMeshOperator::process()
{
    if (mesh != 0)
        delete mesh;

    Operator* input = getInput(0);
    mesh = input->mesh->clone();

    mesh->scale.x = getFloatProperty(0);
    mesh->scale.y = getFloatProperty(1);
    mesh->scale.z = getFloatProperty(2);
    mesh->rotation.x = getFloatProperty(3);
    mesh->rotation.y = getFloatProperty(4);
    mesh->rotation.z = getFloatProperty(5);
    mesh->translation.x = getFloatProperty(6);
    mesh->translation.y = getFloatProperty(7);
    mesh->translation.z = getFloatProperty(8);
}
