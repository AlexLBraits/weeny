#ifndef OPEN_GL_CHECKERROR_H
#define OPEN_GL_CHECKERROR_H

#include <base/debug.h>
#ifndef NDEBUG
#define CHECK_GRAPHICS_ERROR \
    { \
        int e = (int)glGetError(); \
        if (e != 0) \
        { \
            const char * errorString = ""; \
            switch(e) \
            { \
            case GL_INVALID_ENUM:       errorString = "GL_INVALID_ENUM";        break; \
            case GL_INVALID_VALUE:      errorString = "GL_INVALID_VALUE";       break; \
            case GL_INVALID_OPERATION:  errorString = "GL_INVALID_OPERATION";   break; \
            case GL_OUT_OF_MEMORY:      errorString = "GL_OUT_OF_MEMORY";       break; \
            default:                                                            break; \
            } \
            LOGE("OpenGL 0x%04X %s in %s at line %i", e, errorString, __PRETTY_FUNCTION__, __LINE__); \
        } \
    }
#else
#define GRAPHICS_CHECK_ERROR
#endif

#endif /* OPEN_GL_CHECKERROR_H*/
