#include "Bitmap3D.hpp"

#include <algorithm>    // std::reverse
#include <fstream>
#include <iostream>
#include <stdlib.h>



Bitmap3D::Bitmap3D()
:   m_Data{},
    m_Frames{},
    m_Width{},
    m_Height{},
    m_PixelCount{}
{
}

Bitmap3D::~Bitmap3D()
{
    if(m_Data != nullptr)
        free(m_Data);
}

void Bitmap3D::CreateFromFile(const char* file_path)
{
    this->~Bitmap3D();

    std::ifstream file(file_path, std::ios::in | std::ios::binary);

    file >> m_Width;
    file >> m_Height;
    file >> m_Frames;
    m_PixelCount = m_Width * m_Height * m_Frames;

    if(file.is_open() == false)
    {
        std::cerr << "Could not load bitmap 3D from path: " << file_path << std::endl;
        return;
    }

    m_Data = (uint8_t*) malloc(m_PixelCount);
    for(uint32_t i = 0; i < m_PixelCount; i++)
    {
        file >> m_Data[i];
    }
}

void Bitmap3D::ReverseEachFrame()
{
    const uint32_t offset_delta = m_Width*m_Height;
    uint32_t offset = 0;
    for(uint32_t i = 0 ; i < m_Frames; i++)
    {
        std::reverse(&m_Data[offset], &m_Data[offset + offset_delta]);
        offset += offset_delta;
    }
}

std::ostream& operator<<(std::ostream& os, const Bitmap3D& bitmap)
{
    for(uint32_t i = 0; i < bitmap.Frames(); i++)
    {
        for(uint32_t j = 0; j < bitmap.Height(); j++)
        {
            for(uint32_t k = 0; k < bitmap.Width(); k++)
            {
                os << bitmap.Data()[i * bitmap.Width() * bitmap.Height() + j * bitmap.Width() + k] << ' ';
            }
            os << '\n';
        }
        os << '\n';
    }
    return os;
}