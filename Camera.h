#pragma once
#include <glm.hpp>
#include "Shader.h"
#include "Context.h"
#include <ext.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 rotation, GLfloat FOV, GLfloat aspect, GLfloat renderDistance);
	~Camera();

	void setAspect(GLfloat aspect);

	void update();

	void setYaw(float y) { m_rotation.x = y; }
	void setPitch(float p) { m_rotation.y = p; }
	void setRoll(float r) { m_rotation.z = r; }

	void setX(float x) { m_position.x = x; }
	void setY(float y) { m_position.y = y; }
	void setZ(float z) { m_position.z = z; }

	void addYaw(float y) { m_rotation.x += y; }
	void addPitch(float p) { m_rotation.y += p; }
	void addRoll(float r) { m_rotation.z += r; }

	void addX(float x) { m_position.x += x; }
	void addY(float y) { m_position.y += y; }
	void addZ(float z) { m_position.z += z; }


	glm::vec3 getRotation() { return m_rotation; }
	glm::vec3 getPosition() { return m_position; }

	glm::mat4 getProjectionView();

	glm::vec3 getFrontVector() { return m_front; }
	glm::vec3 getRightVector() { return m_right; }

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_up;

	glm::vec3 m_rotation;

	GLfloat m_aspect;
	GLfloat m_FOV;
	GLfloat m_renderDistance;
};

