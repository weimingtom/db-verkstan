#pragma once

#include "core/operator.hpp"

class SubdivideOperator: public Operator
{
public:
    void process();
    void render();

private:
	Mesh* subdivide(Mesh *srcMesh, bool cleanup);
};