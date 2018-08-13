#pragma once

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>

glm::mat4 GetTransformMatrix(glm::vec3 position, glm::vec3 rotations, glm::vec3 scale);

