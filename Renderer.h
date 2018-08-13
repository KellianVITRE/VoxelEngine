#pragma once
#include <iostream>
#include <GL/glew.h>
#include "Camera.h"
#include "Voxel.h"
#include "GameObject.h"

enum {
	NO_PROBLEM,
	GLFW_INIT_PROBLEM,
	GLEW_INIT_PROBLEM
};

class Renderer
{
public:
	Renderer() = default;
	Renderer(Context* context);
	~Renderer();

	void ClearContext(float r, float g, float b, float a);
	void SwapBuffers();

	void Draw(GameObject* mesh, Camera* camera);
	void Draw(Voxel::VoxelMesh* mesh, Camera* camera);

	static bool InitializeGLFW();
	static bool InitializeGLEW();
private:
	Context * m_context = 0;
	ShaderProgram * m_shader = 0;
};

