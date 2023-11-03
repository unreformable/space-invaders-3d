#pragma once

#include "glad/glad.h"
#include "glm/mat4x4.hpp"



class Program
{
public:
    Program();
    ~Program();

    void Load(const char* vs_file_path, const char* fs_file_path);
    void Use();
    void SetUniform(const char* name, const glm::mat4& mat4);

private:
    Program(const Program& other);
    Program& operator=(const Program& other);
    Program(Program&& other);
    Program& operator=(Program&& other);

private:
    GLuint m_Handle;
};