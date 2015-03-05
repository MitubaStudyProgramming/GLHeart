#include "Mesh.h"
#include "Buffer.h"
#include <cstring>

NS_GLH_BEGIN

Mesh::Mesh(const char *filePath)
{
    mPositionBuffer = new Buffer();
    mUVBuffer = new Buffer();
    mNormalBuffer = new Buffer();
    mPositionIndexBuffer = new Buffer();
    mUVIndexBuffer = new Buffer();
    mNormalIndexBuffer = new Buffer();
    Load(filePath);
}

void Mesh::Draw()
{
    mPositionBuffer->Bind(Buffer::ARRAY_BUFFER);
    mPositionIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    mUVBuffer->Bind(Buffer::ARRAY_BUFFER);
    mUVIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

//    mNormalBuffer->Bind(Buffer::ARRAY_BUFFER);
//    mNormalIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);

//    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

void Mesh::Load(const char *filePath)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE * file = fopen( filePath, "r" );
    if( file == NULL )
    {
        printf( "Impossible to open the file !\n" );
        return;
    }

    while( 1 )
    {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf( file, "%s", lineHeader );
        if( res == EOF )
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader
        if( strcmp( lineHeader, "v" ) == 0 )
        {
            glm::vec3 vertex;
            fscanf( file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back( vertex );
        }
        else if( strcmp( lineHeader, "vt" ) == 0 )
        {
            glm::vec2 uv;
            fscanf( file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back( uv );
        }
        else if( strcmp( lineHeader, "vn" ) == 0 )
        {
            glm::vec3 normal;
            fscanf( file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back( normal );
        }
        else if( strcmp( lineHeader, "f" ) == 0 )
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf( file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if( matches != 9 )
            {
                printf( "File can't be read by our simple parser : ( Try exporting with other options\n" );
                return;
            }
            vertexIndices.push_back( vertexIndex[0]-1 );
            vertexIndices.push_back( vertexIndex[1]-1 );
            vertexIndices.push_back( vertexIndex[2]-1 );
            uvIndices.push_back( uvIndex[0]-1 );
            uvIndices.push_back( uvIndex[1]-1 );
            uvIndices.push_back( uvIndex[2]-1 );
            normalIndices.push_back( normalIndex[0]-1 );
            normalIndices.push_back( normalIndex[1]-1 );
            normalIndices.push_back( normalIndex[2]-1 );
        }
        else
        {
            fgets( lineHeader, 128, file );
            //printf( lineHeader );
        }
    }

    mPositionBuffer->Bind(Buffer::ARRAY_BUFFER);
    mPositionBuffer->Data(Buffer::ARRAY_BUFFER, temp_vertices.size() * sizeof(vec3), &temp_vertices[0], STATIC_DRAW);

    mPositionIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
    mPositionIndexBuffer->Data(Buffer::ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], STATIC_DRAW);

    mUVBuffer->Bind(Buffer::ARRAY_BUFFER);
    mUVBuffer->Data(Buffer::ARRAY_BUFFER, temp_uvs.size() * sizeof(vec2), &temp_uvs[0], STATIC_DRAW);

    mUVIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
    mUVIndexBuffer->Data(Buffer::ELEMENT_ARRAY_BUFFER, uvIndices.size() * sizeof(unsigned int), &uvIndices[0], STATIC_DRAW);

//    for (int i = 0; i < uvIndices.size(); ++i) {
//        vec2 uv = temp_uvs[uvIndices[i]];
//        printf("(%f, %f)\n", uv.x, uv.y);
//    }

    mNormalBuffer->Bind(Buffer::ARRAY_BUFFER);
    mNormalBuffer->Data(Buffer::ARRAY_BUFFER, temp_normals.size() * sizeof(vec3), &temp_normals[0], STATIC_DRAW);

    mNormalIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
    mNormalIndexBuffer->Data(Buffer::ELEMENT_ARRAY_BUFFER, normalIndices.size() * sizeof(unsigned int), &normalIndices[0], STATIC_DRAW);

    mIndexCount = vertexIndices.size();

    return;
}

NS_GLH_END