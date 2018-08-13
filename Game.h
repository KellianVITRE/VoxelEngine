#pragma once
#include "Renderer.h"
#include <math.h>

class Game
{
public:
	Game(unsigned int width, unsigned int height, std::string title);
	~Game();

	void Update(double t);
	void Render(double t);

	inline bool open() { return m_open; }

private:
	Renderer * m_renderer = 0;

	Context * m_context = 0;

	Camera * m_camera = 0;

	GameObject * m_mesh = 0;
	Voxel::VoxelMesh * m_mesh1 = 0;

	bool m_open = false;
};

