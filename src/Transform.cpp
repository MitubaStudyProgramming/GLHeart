#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

NS_GLH_BEGIN

mat4 Transform::toMat4() const
{
    mat4 mat_s = glm::scale(mat4(), scale);
    mat4 mat_r = glm::toMat4(rotation);
    mat4 mat_t = glm::translate(mat4(), position);
    return mat_t * mat_r * mat_s;
}

NS_GLH_END