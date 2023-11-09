#include "Box.hpp"

#include "Utils.hpp"



void Box::CreateFromBitmap(const Bitmap3D& bitmap)
{
    Utils::BoundingBoxFromBitmap(bitmap, *this);
}