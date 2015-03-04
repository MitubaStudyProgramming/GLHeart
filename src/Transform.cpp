#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

NS_GLH_BEGIN

glm::mat4 Transform::toMat4() const
{
    glm::mat4 mat_s = glm::scale(glm::mat4(), scale);
    glm::mat4 mat_r = glm::toMat4(rotation);
    glm::mat4 mat_t = glm::translate(glm::mat4(), position);
    return mat_t * mat_r * mat_s;
}

NS_GLH_END