#pragma once

#include "core/operator.hpp"

class ParticleSystemOperator: public Operator
{
public:
	void render(int tick);
    void process();

#ifdef DB_EDITOR
    void deviceLost();
#endif

private:
	DWORD fvf;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9 *indexBuffer;
};