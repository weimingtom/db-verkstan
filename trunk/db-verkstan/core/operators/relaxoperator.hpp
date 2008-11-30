#pragma once

#include "core/operator.hpp"

class RelaxOperator: public Operator
{
public:
    void process();

private:
	void relax(Mesh::EdgeInfo *edgeInfo, float strength);
};