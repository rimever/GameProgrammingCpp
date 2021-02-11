#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned numVerts, const unsigned* indices, unsigned numIndices)
	: mNumVerts(numVerts), mNumIndices(numIndices)
{
	glGenVertexArrays(1, &this->mVertexArray);
	glBindVertexArray(this->mVertexArray);

	glGenBuffers(1, &this->mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &this->mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &this->mVertexBuffer);
	glDeleteBuffers(1, &this->mIndexBuffer);
	glDeleteVertexArrays(1, &this->mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(this->mVertexArray);
}
