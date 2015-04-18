//
// Created by ck01- on 2015/4/18.
//

#ifndef GLHEART_SCENEBASEPREINCLUDES_H
#define GLHEART_SCENEBASEPREINCLUDES_H

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "eCamera.h"
#include "ePointLight.h"
#include "eTime.h"
#include "eMaterial.h"
#include "eMaterialValue.h"
#include "ePostprocessEffect.h"

#define _P(_FILE_NAME_) "W:\\GLHeart\\resources\\" _FILE_NAME_
#define _MESH(_NAME_) _P("mesh\\" _NAME_ ".obj")
#define _TEX(_NAME_) _P("tex\\" _NAME_ ".bmp")
#define _SHADER(_NAME_) _P("shader\\" _NAME_ ".vert"), _P("shader\\" _NAME_ ".frag")

using namespace glh;
using std::cout;
using std::endl;

#endif //GLHEART_SCENEBASEPREINCLUDES_H
