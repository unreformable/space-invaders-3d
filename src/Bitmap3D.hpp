#pragma once

#include <ostream>
#include <stdint.h>



class Bitmap3D
{
public:
    Bitmap3D();
    ~Bitmap3D();

    void Load(const char* file_path);
    void ReverseEachFrame();
    inline uint32_t Frames() const { return m_Frames; }
    inline uint32_t Width() const { return m_Width; }
    inline uint32_t Height() const { return m_Height; }
    inline uint32_t PixelCount() const { return m_PixelCount; }
    inline const uint8_t* Data() const { return m_Data; }

private:
    Bitmap3D(const Bitmap3D& other);
    Bitmap3D& operator=(const Bitmap3D& other);
    Bitmap3D(Bitmap3D&& other);
    Bitmap3D& operator=(Bitmap3D&& other);

private:
    uint8_t* m_Data;
    uint32_t m_Frames;
    uint32_t m_Width;
    uint32_t m_Height;
    uint32_t m_PixelCount;
};

std::ostream& operator<<(std::ostream& os, const Bitmap3D& bitmap);