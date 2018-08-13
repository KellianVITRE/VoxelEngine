#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <glm.hpp>

#include <GL/glew.h>

namespace Voxel {

	struct VoxelType {
		glm::vec3 mColor;
	};

	struct VoxelData {
		std::vector<glm::vec3> mNormals;
		std::vector<glm::vec3> mVertices;
		std::vector<unsigned int> mIndices;
	};

	class VoxelInstance {
	public:
		VoxelInstance(int x, int y, int z, int voxelType);

		const VoxelType &getType();
		const VoxelData &getData();

	private:
		VoxelType mType;
		VoxelData mData;
	};

	VoxelType getVoxelType(int voxelType);
	VoxelData getVoxelData(int _x, int _y, int _z);

	struct VoxelDataBase {

		std::vector<glm::vec3> mNormals;
		std::vector<glm::vec3> mVertices;
		std::vector<glm::vec3> mColors;
		std::vector<unsigned int> mIndices;
	};

	void addVoxelInstanceToDataBase(VoxelDataBase* database, VoxelInstance &voxel);

	class VoxelMesh {
	public:
		VoxelMesh(const VoxelDataBase& voxels);
		~VoxelMesh();

		void Render();
	private:
		
		GLuint mVAO;

		GLuint mPositionVBO;
		GLuint mNormalVBO;
		GLuint mColorVBO;

		GLuint mEBO;

		VoxelDataBase mVoxels;
	};
}