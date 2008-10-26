#pragma once

/**
 * Helper class that wraps vertex & index buffers.
 */
class Mesh
{
public:
	class EdgeInfo
	{
	public:	
		EdgeInfo(int *edges, int numEdges);

		~EdgeInfo();

		int getNumEdges();

		int *getEdge(int i);

		int getIndexOf(int v1, int v2);

	private:
		int numEdges;
		int *edges;
	};

	// Creates a new mesh and allocates buffers of desired size
	Mesh(int numVertices, int numTriangles, int numQuads, int numUVSets = 1);
    
	// Creates a copy of a mesh
	Mesh(const Mesh& mesh);	
    
	~Mesh();	
    
	void render();

	// Position of a vertex
	Vec3 &pos(int vertexIndex);

	// Normal of a vertex
	Vec3 &normal(int vertexIndex);

	// Texture coordinate of a vertex, from the selected UV set
	Vec2 &uv(int vertexIndex);

	// Texture coordinate of a vertex, a certain UV set
	Vec2 &uv(int vertexIndex, int uvSet);

	// Gets a pointer to the indices of a triangle
	int *triangle(int triangleIndex);

	// Gets a pointer to the indices of a quad
	int *quad(int quadIndex);

	// Sets all three vertices of a triangle
	void setTriangle(int triangleIndex, int v0, int v1, int v2);

	// Sets all four vertices of a quad
	void setQuad(int quadIndex, int v0, int v1, int v2, int v3);	

	// Gets a pointer to the indices of a face (either triangle or quad)
	// outNumVertices will hold number of vertices (3 or 4)
	int *face(int faceIndex, int &outNumVertices);

	// Constructs an EdgeInfo object for this Mesh, takes a while.
	// Caller is responsible for deleting it
	EdgeInfo *constructEdgeInfo();

	void recalculateNormals();

	// Trivial getters and setters, inlined to conserve space and time (i hope?)
	inline void setSelectedUVSet(int selectedUVSet) { this->selectedUVSet = selectedUVSet; };
	
	inline int getSelectedUVSet() { return selectedUVSet; }

	inline int getNumVertices() { return numVertices; }

	inline int getNumTriangles() { return numTriangles; }	

	inline int getNumQuads() { return numQuads; }

	inline int getNumFaces() { return numQuads + numTriangles; }

	inline int getNumUVSets() { return numUVSets; }

	// Clones a mesh, just for convenience, should not take up extra space
	inline Mesh* clone() { return new Mesh(*this); }

	inline void setDirty() { destroyD3DBuffers(); }

	void debugPrint();

private:
	void createD3DBuffers();
	void destroyD3DBuffers();

	float *vertexData;
	int *triangleData;
	int *quadData;
	int selectedUVSet;
	int numVertices;
	int numTriangles;
	int numQuads;
	int numUVSets;
	int vertexStride;

	DWORD fvf;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9 *indexBuffer;
};