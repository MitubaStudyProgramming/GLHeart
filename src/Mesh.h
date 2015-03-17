#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class Mesh
{
public:
    Mesh(const char* filePath);
    Mesh(std::vector<vec3>& vertices, std::vector<vec2>& uvs, std::vector<vec3>& normals, std::vector<GLuint>& indices);

    void Draw();

private:
    void Load(const char* filePath);

private:
    GLsizei mIndexCount;
    Buffer* mPositionBuffer;
    Buffer* mUVBuffer;
    Buffer* mNormalBuffer;
    Buffer* mIndexBuffer;
};

NS_GLH_END