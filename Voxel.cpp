#include "Voxel.h"

Voxel::VoxelInstance::VoxelInstance(int x, int y, int z, int voxelType) {
	mType = getVoxelType(voxelType);
	mData = getVoxelData(x, y, z);
}

const Voxel::VoxelType & Voxel::VoxelInstance::getType() {
	return mType;
}

const Voxel::VoxelData & Voxel::VoxelInstance::getData() {
	return mData;
}

Voxel::VoxelType Voxel::getVoxelType(int voxelType) {
	Voxel::VoxelType type;

	if (voxelType == 0) {
		type.mColor = glm::vec3(0.0, 1.0, 0.0);
	} else if (voxelType == 1) {
		type.mColor = glm::vec3(1.0, 0.0, 0.0);
	} else if (voxelType == 2) {
		type.mColor = glm::vec3(0.5, 0.5, 0.5);
	}

	return type;
}

Voxel::VoxelData Voxel::getVoxelData(int _x, int _y, int _z) {
	Voxel::VoxelData data;

	double size = 3;

	double x = _x*size;
	double y = _y*size;
	double z = _z*size;

	data.mVertices = {
		glm::vec3(-size + x, -size + y, -size + z),
		glm::vec3(size + x, -size + y, -size + z),
		glm::vec3(size + x, size + y, -size + z),
		glm::vec3(-size + x, size + y, -size + z),
		glm::vec3(-size + x, -size + y, size + z),
		glm::vec3(size + x, -size + y, size + z),
		glm::vec3(size + x, size + y, size + z),
		glm::vec3(-size + x, size + y, size + z)
	};

	data.mNormals = {
		glm::vec3(0, 0, 1),
		glm::vec3(0, 1, 1),
		glm::vec3(1, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 1, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	};

	data.mIndices = {
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

	return data;
}

void Voxel::addVoxelInstanceToDataBase(VoxelDataBase * database, VoxelInstance & voxel) {

	int indexOffset = database->mIndices.size()/36*8;

	for (int i = 0; i < voxel.getData().mVertices.size(); i++) {
		database->mVertices.push_back(voxel.getData().mVertices[i]);
	}

	for (int i = 0; i < voxel.getData().mNormals.size(); i++) {
		database->mNormals.push_back(voxel.getData().mNormals[i]);
	}

	for (int i = 0; i < voxel.getData().mVertices.size(); i++) {
		database->mColors.push_back(voxel.getType().mColor);
	}

	for (int i = 0; i < voxel.getData().mIndices.size(); i++) {
		database->mIndices.push_back(voxel.getData().mIndices[i]+indexOffset);
	}
}

Voxel::VoxelMesh::VoxelMesh(const Voxel::VoxelDataBase& voxels) 
	: mVoxels(voxels) {

	glm::vec3* vertices = new glm::vec3[mVoxels.mVertices.size()];
	for (int i = 0; i < mVoxels.mVertices.size(); i++) {
		vertices[i] = mVoxels.mVertices[i];
	}

	glm::vec3* normals = new glm::vec3[mVoxels.mNormals.size()];
	for (int i = 0; i < mVoxels.mNormals.size(); i++) {
		normals[i] = mVoxels.mNormals[i];
	}

	glm::vec3* colors = new glm::vec3[mVoxels.mColors.size()];
	for (int i = 0; i < mVoxels.mColors.size(); i++) {
		colors[i] = mVoxels.mColors[i];
	}

	unsigned int* indices = new unsigned int[mVoxels.mIndices.size()];
	for (int i = 0; i < mVoxels.mIndices.size(); i++) {
		indices[i] = mVoxels.mIndices[i];
	}

	glGenVertexArrays(1, &mVAO);

	glBindVertexArray(mVAO);

	glGenBuffers(1, &mPositionVBO);
	glGenBuffers(1, &mNormalVBO);
	glGenBuffers(1, &mColorVBO);
	glGenBuffers(1, &mEBO);

	glBindBuffer(GL_ARRAY_BUFFER, mPositionVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVoxels.mVertices[0]) * mVoxels.mVertices.size(), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] vertices;

	glBindBuffer(GL_ARRAY_BUFFER, mNormalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVoxels.mNormals[0]) * mVoxels.mNormals.size(), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] normals;

	glBindBuffer(GL_ARRAY_BUFFER, mColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVoxels.mColors[0]) * mVoxels.mColors.size(), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float)*3, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] colors;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mVoxels.mIndices[0]) * mVoxels.mIndices.size(), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] indices;

	glBindVertexArray(0);
}

Voxel::VoxelMesh::~VoxelMesh() {
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mPositionVBO);
	glDeleteBuffers(1, &mNormalVBO);
	glDeleteBuffers(1, &mColorVBO);
	glDeleteBuffers(1, &mEBO);
}

void Voxel::VoxelMesh::Render() {
	glBindVertexArray(mVAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

	glDrawElements(GL_TRIANGLES, mVoxels.mIndices.size(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
