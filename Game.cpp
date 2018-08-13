#include "Game.h"
#include <cstdlib>


Game::Game(unsigned int width, unsigned int height, std::string title)
{
	Renderer::InitializeGLFW();
	m_context = new Context(width, height, title);
	m_renderer = new Renderer(m_context);

	std::vector<unsigned int> i = {
			0, 1, 2,
			0, 2, 5,
			0, 3, 5,
			1, 2, 5,
			1, 4, 5,
			3, 4, 5,
			0, 1, 3,
			3, 4, 1
	};

	m_camera = new Camera(glm::vec3(0.0, 0.0, -10.0), glm::vec3(-270.0, 0.0, 0.0), glm::radians(45.0f), 1.33f, 1000.0f);

	std::vector<Voxel::VoxelInstance> voxs;

	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				voxs.push_back(Voxel::VoxelInstance(x, y, z, rand() % 3));
			}
		}
	}

	Voxel::VoxelDataBase dataBase;

	for (int i = 0; i < 16 * 16 * 16; i++) {
		Voxel::addVoxelInstanceToDataBase(&dataBase, voxs[i]);
	}

	m_mesh1 = new Voxel::VoxelMesh(dataBase);

	m_open = true;
}


Game::~Game()
{
	delete[] m_renderer;
	delete[] m_context;
}

void Game::Update(double t)
{
	if (m_context->open()) {
		glfwPollEvents();
		m_camera->setYaw(-270.0f);
		m_camera->setX(cos(t) * 30);
		m_camera->setY(sin(t) * 30);
		m_camera->setZ(-20);
		m_camera->update();
	}
	else {
		m_open = false;
	}
}

void Game::Render(double t)
{
	if (m_context->open()) {
		m_renderer->ClearContext((float)55/255, (float)193/255, (float)255/255, 1.0f);
		m_renderer->Draw(m_mesh1, m_camera);
		m_renderer->SwapBuffers();
	}
	else {
		m_open = false;
	}
}
