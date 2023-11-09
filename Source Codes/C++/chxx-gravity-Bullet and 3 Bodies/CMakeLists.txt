cmake_minimum_required(VERSION 3.17)

project(result LANGUAGES CXX)

add_executable(result main.cpp Mesh.cpp LightRenderer.cpp MeshRenderer.cpp ShaderLoader.cpp TextureLoader.cpp Camera.cpp)
target_link_libraries(result GLEW glfw GL BulletCollision BulletDynamics LinearMath)
target_include_directories(result PRIVATE /usr/include /usr/include/stb-master)
