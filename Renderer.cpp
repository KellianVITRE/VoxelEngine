#include "Renderer.h"


Renderer::Renderer(Context * context)
	: m_context(context)
{
	m_context->Use();
	glfwSwapInterval(0);

	Renderer::InitializeGLEW();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	m_shader = new ShaderProgram("Shader/VertexShader.vs", "Shader/FragmentShader.fs");
}

Renderer::~Renderer()
{
}

void Renderer::ClearContext(float r, float g, float b, float a)
{

	glClearColor(r, g, b, a);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers()
{
	m_context->SwapBuffers();

}

void Renderer::Draw(GameObject* mesh, Camera* camera)
{

	m_shader->Bind();

	glm::mat4 VP = camera->getProjectionView();
	glm::mat4 M = mesh->getModel();

	glm::mat4 MVP = VP * M;

	m_shader->SetUniformMat4(MVP, "MVP");

	mesh->DrawGO();

	m_shader->Unbind();

}

void Renderer::Draw(Voxel::VoxelMesh* mesh, Camera* camera)
{

	m_shader->Bind();

	glm::mat4 VP = camera->getProjectionView();
	glm::mat4 M = glm::mat4(1.0f);

	glm::mat4 MVP = VP * M;

	m_shader->SetUniformMat4(MVP, "MVP");

	mesh->Render();

	m_shader->Unbind();

}

bool Renderer::InitializeGLFW()
{
	if (glfwInit()) {
		return true;
	}
	system("PAUSE");
	exit(GLFW_INIT_PROBLEM);
}

bool Renderer::InitializeGLEW()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err == GLEW_OK) {
		return true;
	}
	else {
		std::cerr << "Error:" << glewGetErrorString(err) << std::endl;
		system("PAUSE");
		exit(GLEW_INIT_PROBLEM);
	}
}
