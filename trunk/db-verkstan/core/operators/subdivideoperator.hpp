#pragma once

#include "core/operator.hpp"

class SubdivideOperator: public Operator
{
public:
    void process();

private:
	Mesh* subdivide(Mesh *srcMesh, bool cleanup, float smoothness);
};