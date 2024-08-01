/*********************************************************************************************************************
 * File : shader.h                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <fstream>

#include "gl_error_manager.h"
#include "shader.h"

Shader::Shader(const std::string &filepath)
{

    ProgramSource source = parse_shader(filepath);
    GlCall(rendered_id_ = create_shader(source.VertexSource, source.FragmentSource));
}

Shader::~Shader()
{
    GlCall(glDeleteProgram(rendered_id_));
}

Shader::ProgramSource Shader::parse_shader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType // Use the type as an index in the array
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
            ss[(int)type] << line << '\n';
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compile_shader(unsigned int type, const std::string &source)
{
    GlCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GlCall(glShaderSource(id, 1, &src, nullptr));
    GlCall(glCompileShader(id));

    int result;
    GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length];
        GlCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Fail to compile shader: "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << std::endl;
        std::cout << message << std::endl;
        GlCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int Shader::create_shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    GlCall(unsigned int program = glCreateProgram());
    GlCall(unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader));
    GlCall(unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader));

    GlCall(glAttachShader(program, vs));
    GlCall(glAttachShader(program, fs));
    GlCall(glLinkProgram(program));
    GlCall(glValidateProgram(program));

    GlCall(glDeleteShader(vs));
    GlCall(glDeleteShader(fs));

    return program;
}

void Shader::bind() const
{
    GlCall(glUseProgram(rendered_id_));
}

void Shader::unbind() const
{
    GlCall(glUseProgram(0));
}

void Shader::set_uniform1i(const std::string &name, int value)
{
    GlCall(glUniform1i(get_uniform_location(name), value));
}

void Shader::set_uniform1f(const std::string &name, float value)
{
    GlCall(glUniform1f(get_uniform_location(name), value));
}

void Shader::set_uniform2f(const std::string &name, const glm::vec2 &value)
{
    GlCall(glUniform2f(get_uniform_location(name), value.x, value.y));
}

void Shader::set_uniform3f(const std::string &name, const glm::vec3 &value)
{
    GlCall(glUniform3f(get_uniform_location(name), value.x, value.y, value.z));
}

void Shader::set_uniform4f(const std::string &name, const glm::vec4 &value)
{
    GlCall(glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w));
}

void Shader::set_uniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    GlCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::set_uniform1iv(const std::string &name, unsigned int count, int *data)
{
    GlCall(glUniform1iv(get_uniform_location(name), count, data));
}

int Shader::get_uniform_location(const std::string &name)
{
    auto it = uniform_location_cache_.find(name);
    if (it != uniform_location_cache_.end())
        return it->second;

    GlCall(const int location = glGetUniformLocation(rendered_id_, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist." << std::endl;

    uniform_location_cache_[name] = location;
    return location;
}