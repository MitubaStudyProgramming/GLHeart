#include "eMaterial.h"
#include "eMaterialValue.h"

using namespace glh;

eMaterial::eMaterial()
:mProgram(NULL)
,mTexture(NULL)
{

}

eMaterial::~eMaterial()
{
    for(GLuint i=0;i<mMaterialValues.size();++i){
        delete mMaterialValues[i];
    }
    if (mProgram != NULL) delete mProgram;
    if (mTexture != NULL) delete mTexture;
}

void eMaterial::LoadShader(const char *vertexShaderFilePath, const char *fragmentShaderFilePath)
{
    mProgram = ShaderProgram::QuickLoad(vertexShaderFilePath, fragmentShaderFilePath);
}

glh::ShaderUniform *eMaterial::GetUniform(const char *name) {
    if (mProgram != NULL) {
        return mProgram->GetUniform(name);
    }
    return NULL;
}

void eMaterial::BindUniformValue(const char *uniformName, eMaterialValue *value) {
    mMaterialValues.push_back(value);
    if (mProgram != NULL)
    {
        ShaderUniform* uniform = mProgram->GetUniform(uniformName);
        value->BindUniform(uniform);
    }
}

void eMaterial::BindUniformValue(const char *name, GLfloat value) {
    ShaderUniform* uniform = GetUniform(name);
    if (uniform != NULL)
    {
        eMaterialValueFloatConstant* p = new eMaterialValueFloatConstant(value);
        p->BindUniform(uniform);
        mMaterialValues.push_back(p);
    }
}

void eMaterial::LoadTexture(const char *filePath)
{
    mTexture = new Texture();
    mTexture->LoadFile(filePath);
}

void eMaterial::Active()
{
    if (mProgram != NULL) {
        mProgram->Use();
        for(GLuint i=0;i<mMaterialValues.size();++i){
            mMaterialValues[i]->Update();
        }
    }

    if (mTexture != NULL) {
        Texture::Active(Texture::TEXTURE0);
        mTexture->Bind(Texture::TEXTURE_2D);
    }
}