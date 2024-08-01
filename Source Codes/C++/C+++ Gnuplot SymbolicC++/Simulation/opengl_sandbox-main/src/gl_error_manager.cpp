/*********************************************************************************************************************
 * File : gl_error_manager.cpp                                                                                       *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "gl_error_manager.h"

#define GlCall(x)   \
    GlClearError(); \
    x;              \
    assert(GlLogCall())

void GlClearError()
{
    while (glGetError())
    {
    };
}

bool GlLogCall()
{
    while (GLenum e = glGetError())
    {
        std::stringstream ss;
        ss << std::hex << e; // Error in hexadecimal
        std::cout << "[OpenGL error] " << ss.str() << std::endl;
        return false;
    }
    return true;
}
