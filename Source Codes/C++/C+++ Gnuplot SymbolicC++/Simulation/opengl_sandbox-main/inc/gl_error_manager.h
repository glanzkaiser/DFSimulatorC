/*********************************************************************************************************************
 * File : gl_error_manager.h                                                                                         *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef GL_ERROR_MANAGER_H
#define GL_ERROR_MANAGER_H

#include <assert.h>
#include <iostream>
#include <sstream>
#include <GL/glew.h>

#define GlCall(x)   \
    GlClearError(); \
    x;              \
    assert(GlLogCall())

void GlClearError();

bool GlLogCall();

#endif // GL_ERROR_MANAGER_H
