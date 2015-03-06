#pragma once

#include "ePredefine.h"

class eMaterialValue
{
public:
    eMaterialValue();

    void BindUniform(glh::ShaderUniform* uniform);

    void Update();

protected:
    virtual void UpdateUniform(glh::ShaderUniform* uniform) = 0;

private:
    glh::ShaderUniform* mUniform;
};

class eMaterialValueFloatConstant : public eMaterialValue
{
public:
    eMaterialValueFloatConstant(GLfloat value);

protected:
    virtual void UpdateUniform(glh::ShaderUniform* uniform);

private:
    GLfloat mValue;
};

class eMaterialValueFloatSlider : public eMaterialValue
{
public:
    eMaterialValueFloatSlider(GLfloat initialValue, GLfloat min, GLfloat max, GLfloat changeSpeed, int decreaseKey, int increaseKey);

protected:
    virtual void UpdateUniform(glh::ShaderUniform* uniform);

private:
    GLfloat mValue;
    GLfloat mMin;
    GLfloat mMax;
    GLfloat mSpeed;
    int mDecreaseKey;
    int mIncreaseKey;
};