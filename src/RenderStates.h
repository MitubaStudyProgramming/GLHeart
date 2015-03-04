#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

namespace RenderStates
{

    namespace Depth
    {
        struct Range
        {
            GLfloat near;
            GLfloat far;
        };

        void SetEnable(GLboolean enable);
        GLboolean IsEnable();

        void SetDepthFunc(DepthFunc depthFunc);
        DepthFunc GetDepthFunc();

        void SetEnableWrite(GLboolean enable);
        GLboolean IsEnableWrite();

        void SetRange(GLclampd near, GLclampd far);
        void SetRange(const Range& range);
        Range GetRange();
    }
}

NS_GLH_END