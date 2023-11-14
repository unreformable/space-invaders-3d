#pragma once

#include "Bitmap3D.hpp"
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
        
        for(auto pair : m_Bitmaps)
            delete pair.second;
    }

    // void UpdatePrograms(const Camera& camera);


    inline Mesh* CreateMesh(const char* name) { return m_Meshes[name] = new Mesh; }
    inline Program* CreateProgram(const char* name) { return m_Programs[name] = new Program; }
    inline Bitmap3D* CreateBitmap(const char* name) { return m_Bitmaps[name] = new Bitmap3D; }

    inline Mesh* GetMesh(const char* name) { return m_Meshes[std::string(name)]; }
    inline Program* GetProgram(const char* name) { return m_Programs[std::string(name)]; }
    inline Bitmap3D* GetBitmap(const char* name) { return m_Bitmaps[std::string(name)]; }

private:
    std::unordered_map<std::string, Mesh*> m_Meshes;
    std::unordered_map<std::string, Program*> m_Programs;
    std::unordered_map<std::string, Bitmap3D*> m_Bitmaps;
};