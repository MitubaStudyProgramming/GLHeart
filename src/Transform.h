#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class Transform
{
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

public:
    glm::mat4 toMat4() const ;
};

NS_GLH_END