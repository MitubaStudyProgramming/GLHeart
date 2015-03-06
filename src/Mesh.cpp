#include "Mesh.h"
#include "Buffer.h"
#include <cstring>

NS_GLH_BEGIN

static inline void _print(const vec3& v)
{
    printf("(%f, %f, %f) ", v.x, v.y, v.z);
}

static inline void _print(const vec2& v)
{
    printf("(%f, %f) ", v.x, v.y);
}

Mesh::Mesh(const char *filePath)
{
    mPositionBuffer = new Buffer();
    mUVBuffer = new Buffer();
    mNormalBuffer = new Buffer();
    mIndexBuffer = new Buffer();
    Load(filePath);
}

void Mesh::Draw()
{
    mPositionBuffer->Bind(Buffer::ARRAY_BUFFER);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    mUVBuffer->Bind(Buffer::ARRAY_BUFFER);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    mNormalBuffer->Bind(Buffer::ARRAY_BUFFER);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    mIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);

    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(2);
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
            fscanf( file, "%f %f %f\n", &vertex.z, &vertex.x, &vertex.y );
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
            fscanf( file, "%f %f %f\n", &normal.z, &normal.x, &normal.y );
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

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::map<GLuint, GLuint> indexLookupTable;
    std::vector<GLuint> indices;

    for(GLuint i=0; i<vertexIndices.size();++i)
    {
        GLuint vertexIndex = vertexIndices[i];
        GLuint uvIndex = uvIndices[i];
        GLuint normalIndex = normalIndices[i];

        GLuint finalIndex = 0;

        GLuint lookupIndex = (vertexIndex << 20) + (uvIndex << 10) + (normalIndex << 0);
        if (indexLookupTable.find(lookupIndex) == indexLookupTable.end())
        {
            finalIndex = vertices.size();

            indexLookupTable[lookupIndex] = finalIndex;
            vertices.push_back(temp_vertices[vertexIndex]);
            uvs.push_back(temp_uvs[uvIndex]);
            normals.push_back(temp_normals[normalIndex]);

//            printf("[%3d] ", finalIndex);
//            _print(temp_vertices[vertexIndex]);
//            _print(temp_uvs[uvIndex]);
//            _print(temp_normals[normalIndex]);
//            printf("\n");
        }
        else
        {
            finalIndex = indexLookupTable[lookupIndex];
        }
        indices.push_back(finalIndex);
    }

    mIndexCount = indices.size();

    mPositionBuffer->Bind(Buffer::ARRAY_BUFFER);
    mPositionBuffer->Data(Buffer::ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], STATIC_DRAW);

    mUVBuffer->Bind(Buffer::ARRAY_BUFFER);
    mUVBuffer->Data(Buffer::ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], STATIC_DRAW);

    mNormalBuffer->Bind(Buffer::ARRAY_BUFFER);
    mNormalBuffer->Data(Buffer::ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], STATIC_DRAW);

    mIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
    mIndexBuffer->Data(Buffer::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], STATIC_DRAW);

    return;
}

NS_GLH_END