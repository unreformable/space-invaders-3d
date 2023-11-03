#include "Program.hpp"

#include "Utils.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>



Program::Program()
:   m_Handle{}
{
}

Program::~Program()
{
    glDeleteProgram(m_Handle);
}

void Program::Load(const char* vs_file_path, const char* fs_file_path)
{
    this->~Program();

    std::string vs_data;
    std::string fs_data;

    Utils::Load(vs_file_path, vs_data);
    Utils::Load(fs_file_path, fs_data);

    const char* vs_source = vs_data.c_str();
    const char* fs_source = fs_data.c_str();

    GLint success = GL_TRUE;
    GLchar info_log[512];
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        glGetShaderInfoLog(vs, 512, NULL, info_log);
        std::cerr << "Could not compile vertex shader\n" << info_log << std::endl;
    }
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        glGetShaderInfoLog(fs, 512, NULL, info_log);
        std::cerr << "Could not compile fragment shader\n" << info_log << std::endl;
    }
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(success == GL_FALSE)
    {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        std::cerr << "Could not link program\n" << info_log << std::endl;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);

    m_Handle = program;
}

void Program::Use()
{
    glUseProgram(m_Handle);
}

void Program::SetUniform(const char* name, const glm::mat4& mat4)
{
    glProgramUniformMatrix4fv(m_Handle, glGetUniformLocation(m_Handle, name), 1, GL_FALSE, glm::value_ptr(mat4));
}