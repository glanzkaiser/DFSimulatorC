add_executable(main ${COMMON_SOURCES} main.cpp)
target_link_libraries(main glfw OpenGL::GL GLEW::GLEW)