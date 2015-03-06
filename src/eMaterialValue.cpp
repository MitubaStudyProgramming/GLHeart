#include "eMaterialValue.h"

#include "eTime.h"

extern GLFWwindow* gWindow;

eMaterialValue::eMaterialValue()
:mUniform(NULL)
{

}

void eMaterialValue::BindUniform(glh::ShaderUniform *uniform)
{
    mUniform = uniform;
}

void eMaterialValue::Update()
{
    if (mUniform != NULL)
        this->UpdateUniform(mUniform);
}

eMaterialValueFloatConstant::eMaterialValueFloatConstant(GLfloat value)
:mValue(value)
{

}

void eMaterialValueFloatConstant::UpdateUniform(glh::ShaderUniform *uniform)
{
    uniform->SetValue(mValue);
}

eMaterialValueFloatSlider::eMaterialValueFloatSlider(GLfloat initialValue, GLfloat min, GLfloat max, GLfloat changeSpeed, int decreaseKey, int increaseKey)
:mValue(initialValue)
,mMin(min)
,mMax(max)
,mSpeed(changeSpeed)
,mDecreaseKey(decreaseKey)
,mIncreaseKey(increaseKey)
{

}
void eMaterialValueFloatSlider::UpdateUniform(glh::ShaderUniform *uniform)
{
    bool changed = false;
    if (glfwGetKey(gWindow, mDecreaseKey) == GLFW_PRESS)
    {
        changed = true;
        mValue -= mSpeed * eTime::GetDeltaTime();
    }
    if (glfwGetKey(gWindow, mIncreaseKey) == GLFW_PRESS)
    {
        changed = true;
        mValue += mSpeed * eTime::GetDeltaTime();
    }
    if (changed)
        printf("Float Value Changed: %f\n", mValue);
    mValue = glh::clamp(mValue, mMin, mMax);
    uniform->SetValue(mValue);
}
