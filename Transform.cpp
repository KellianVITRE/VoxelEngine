#include "Transform.h"

glm::mat4 GetTransformMatrix(glm::vec3 position, glm::vec3 rotations, glm::vec3 scale)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotXMatrix = glm::rotate(glm::mat4(1.0f), rotations.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(glm::mat4(1.0f), rotations.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(glm::mat4(1.0f), rotations.z, glm::vec3(1, 0, 0));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	glm::mat4 transformmatrix = scaleMatrix * rotMatrix * translationMatrix;

	return transformmatrix;
}
