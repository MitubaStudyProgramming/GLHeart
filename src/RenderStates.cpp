#include "RenderStates.h"

NS_GLH_BEGIN

namespace RenderStates
{

    namespace Depth
    {

        void SetEnable(GLboolean enable)
        {
            if (enable)
                glEnable(GL_DEPTH_TEST);
            else
                glDisable(GL_DEPTH_TEST);
        }

        GLboolean IsEnable()
        {
            GLboolean result;
            glGetBooleanv(GL_DEPTH_TEST, &result);
            return result;
        }

        void SetDepthFunc(DepthFunc depthFunc)
        {
            glDepthFunc((GLenum)depthFunc);
        }

        DepthFunc GetDepthFunc()
        {
            GLint result;
            glGetIntegerv(GL_DEPTH_FUNC, &result);
            return (DepthFunc)result;
        }

        void SetEnableWrite(GLboolean enable)
        {
            glDepthMask(enable);
        }

        GLboolean IsEnableWrite()
        {
            GLboolean result;
            glGetBooleanv(GL_DEPTH_WRITEMASK, &result);
            return result;
        }

        void SetRange(GLclampd near, GLclampd far)
        {
            glDepthRange(near, far);
        }

        void SetRange(const Range& range)
        {
            glDepthRange((GLclampd)range.near, (GLclampd)range.far);
        }

        Range GetRange()
        {
            Range range;
            glGetFloatv(GL_DEPTH_RANGE, &range.near);
            return range;
        }
    }
}

NS_GLH_END