#include "Graphics/Mesh.hpp"
#include "Memory/Memory.hpp"

namespace DE {

Mesh* Mesh::smRectangle = nullptr;

Mesh::Mesh() : DE_Class() {

	mVertexCount = 0;
	mVertices = nullptr;
	mNormals = nullptr;
	mFaces = nullptr;
	mTextureCoordinates = nullptr;
	mVerticesIndex = 0;
	mNormalsIndex = 0;
	mFacesIndex = 0;
	mTextureCoordinatesIndex = 0;
}

Mesh::~Mesh() {
	DE_FREE(mVertices);
	DE_FREE(mNormals);
	DE_FREE(mTextureCoordinates);
	DE_FREE(mFaces);
}

void Mesh::init(u32 vertexCount, u32 facesCount) {
	DE_TRACE()

	mVertexCount = vertexCount;

	mVertices = DE_NEW<Array<f32>>();
	mTextureCoordinates = DE_NEW<Array<f32>>();
	mNormals = DE_NEW<Array<f32>>();
	mFaces = DE_NEW<Array<u32>>();

	mVertices->init(vertexCount * 3);
	mTextureCoordinates->init(vertexCount * 3);
	mNormals->init(vertexCount * 3);
	mFaces->init(facesCount * 3);

	mVerticesIndex = 0; // Vertices index
	mNormalsIndex = 0; // Normals index
	mFacesIndex = 0; // Face index
	mTextureCoordinatesIndex = 0; // TexCoord index
}

Mesh* Mesh::addVertex(const Vector3 &vector) {
	mVertices->set(mVerticesIndex, vector.x);
	mVerticesIndex++;
	mVertices->set(mVerticesIndex, vector.y);
	mVerticesIndex++;
	mVertices->set(mVerticesIndex, vector.z);
	mVerticesIndex++;
	return this;
}

Mesh* Mesh::addNormal(const Vector3 &vector) {
	mNormals->set(mNormalsIndex, vector.x);
	mNormalsIndex++;
	mNormals->set(mNormalsIndex, vector.y);
	mNormalsIndex++;
	mNormals->set(mNormalsIndex, vector.z);
	mNormalsIndex++;
	return this;
}

Mesh* Mesh::addTexCoord(u32 u, u32 v) {
	mTextureCoordinates->set(mTextureCoordinatesIndex, u);
	mTextureCoordinatesIndex++;
	mTextureCoordinates->set(mTextureCoordinatesIndex, v);
	mTextureCoordinatesIndex++;
	return this;
}

Mesh* Mesh::addFace(u32 v1, u32 v2, u32 v3) {
	mFaces->set(mFacesIndex, v1);
	mFacesIndex++;
	mFaces->set(mFacesIndex, v2);
	mFacesIndex++;
	mFaces->set(mFacesIndex, v3);
	mFacesIndex++;
	return this;
}

Mesh* Mesh::getRectangle() {
	if (!smRectangle) {
		smRectangle = DE_NEW<Mesh>();
		smRectangle->init(4, 2);

		smRectangle->addVertex(Vector3(-0.5f, 0.5f, 0.0f))-> // top left
		addVertex(Vector3(-0.5f, -0.5f, 0.0f))-> // bottom left
		addVertex(Vector3(0.5f, -0.5f, 0.0f))-> // bottom right
		addVertex(Vector3(0.5f, 0.5f, 0.0f))-> // top right

		addTexCoord(0.0f, 1.0f)-> // top left
		addTexCoord(0.0f, 0.0f)-> // bottom left
		addTexCoord(1.0f, 0.0f)-> // bottom right
		addTexCoord(1.0f, 1.0f)-> // top right

		addFace(0, 1, 3)->addFace(1, 2, 3);
	}

	return smRectangle;
}

void Mesh::freeRectangle() {
	DE_FREE(smRectangle);
	smRectangle = nullptr;
}

}
