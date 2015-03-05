#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class Transform
{
public:
    vec3 position;
    quat rotation;
    vec3 scale;

public:
    mat4 toMat4() const ;
};

NS_GLH_END