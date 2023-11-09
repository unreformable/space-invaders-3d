#pragma once

#include "Mesh.hpp"
#include "Program.hpp"

#include <unordered_map>



class RenderSystem
{
public:
    ~RenderSystem()
    {
        for(auto pair : m_Meshes)
            delete pair.second;
        
        for(auto pair : m_Programs)
            delete pair.second;
    }

    inline Mesh* CreateMesh(const char* name) { Mesh* mesh = new Mesh; m_Meshes[name] = mesh; return mesh; }
    inline Program* CreateProgram(const char* name) { Program* program = new Program; m_Programs[name] = program; return program; }

    inline Mesh* GetMesh(const char* name) { return m_Meshes[std::string(name)]; }
    inline Program* GetProgram(const char* name) { return m_Programs[std::string(name)]; }

private:
    std::unordered_map<std::string, Mesh*> m_Meshes;
    std::unordered_map<std::string, Program*> m_Programs;
};