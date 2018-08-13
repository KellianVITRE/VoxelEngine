#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 rotation, GLfloat FOV, GLfloat aspect, GLfloat renderDistance)
	: m_position(position), m_rotation(rotation), m_FOV(FOV), m_aspect(aspect), m_renderDistance(renderDistance)
{

	m_front.x = cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
	m_front.y = sin(glm::radians(m_rotation.y));
	m_front.z = sin(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));

	m_up = glm::vec3(0, 1, 0);

	m_right = glm::normalize(glm::cross(m_front, m_up));
}


Camera::~Camera()
{
}

void Camera::setAspect(GLfloat aspect)
{
	m_aspect = aspect;
}

void Camera::update()
{
	m_front.x = cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
	m_front.y = sin(glm::radians(m_rotation.y));
	m_front.z = sin(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));

	m_right = glm::normalize(glm::cross(m_front, m_up));
}

glm::mat4 Camera::getProjectionView()
{

	glm::mat4 projection = glm::perspective(m_FOV, m_aspect, 0.01f, m_renderDistance);
	glm::mat4 view = glm::lookAt(m_position, m_position + m_front, glm::vec3(0, 1, 0));

	glm::mat4 VP = projection * view;

	return VP;
}