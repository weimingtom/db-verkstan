#include "core/operators/particlesystemoperator.hpp"

void ParticleSystemOperator::process()
{

}

void ParticleSystemOperator::render(int tick)
{	
	Mesh *srcMesh = getInput(0)->mesh;

	if (!srcMesh)
	{
		return;
	}

	float particleSize = getFloatProperty(0);
	
	globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

    Vec3 forward, up, right;

	{
		D3DXMATRIX viewMatrix;
		D3DXMATRIX worldMatrix;
		D3DXMATRIX worldViewMatrix;

		globalDirect3DDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
		globalDirect3DDevice->GetTransform(D3DTS_WORLD, &worldMatrix);

		D3DXMatrixMultiply(&worldViewMatrix, &viewMatrix, &worldMatrix);
		D3DXMatrixTranspose(&worldViewMatrix, &worldViewMatrix);

		right = Vec3(worldViewMatrix.m[0]);
		up = Vec3(worldViewMatrix.m[1]);
		forward = Vec3(worldViewMatrix.m[2]);
	}

	Mesh *tmpMesh = new Mesh(srcMesh->getNumVertices() * 4, 0, srcMesh->getNumVertices());

	int *sortedVerts = srcMesh->constructSortedVertexIndices(-forward);

	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		int j = sortedVerts[i];

		tmpMesh->pos(i * 4 + 0) = srcMesh->pos(j) + (up + right) * particleSize;
		tmpMesh->pos(i * 4 + 1) = srcMesh->pos(j) + (up - right) * particleSize;
		tmpMesh->pos(i * 4 + 2) = srcMesh->pos(j) + (-up - right) * particleSize;
		tmpMesh->pos(i * 4 + 3) = srcMesh->pos(j) + (-up + right) * particleSize;

		tmpMesh->normal(i * 4 + 0) = srcMesh->normal(j);
		tmpMesh->normal(i * 4 + 1) = srcMesh->normal(j);
		tmpMesh->normal(i * 4 + 2) = srcMesh->normal(j);
		tmpMesh->normal(i * 4 + 3) = srcMesh->normal(j);

		tmpMesh->uv(i * 4 + 0) = Vec2(0.0f, 0.0f);
		tmpMesh->uv(i * 4 + 1) = Vec2(0.0f, 1.0f);
		tmpMesh->uv(i * 4 + 2) = Vec2(1.0f, 1.0f);
		tmpMesh->uv(i * 4 + 3) = Vec2(1.0f, 0.0f);

		tmpMesh->setQuad(i, i * 4 + 0, i * 4 + 3, i * 4 + 2, i * 4 + 1);
	}						
							
	globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	tmpMesh->render();		
	delete tmpMesh;

	delete[] sortedVerts;
}

#ifdef DB_EDITOR
void ParticleSystemOperator::deviceLost()
{
}
#endif