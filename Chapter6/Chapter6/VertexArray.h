#pragma once
class VertexArray
{
public:
	VertexArray(const float* verts,unsigned int numVerts,const unsigned int* indices,unsigned int numIndices);
	~VertexArray();

	void SetActive() const;
	unsigned int GetNumIndices() const {return this->mNumIndices;}
	unsigned int GetNumVerts() const { return this->mNumVerts;}
private:
	unsigned int mNumIndices;
	unsigned int mNumVerts;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};

