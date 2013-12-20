#include "Vec3.h"

Vec3::Vec3(float xIn, float yIn, float zIn) : Vec2(xIn, yIn), z(zIn)
{
	
}

Vec3::Vec3(const Vec3& other)// : x( other.x ), y( other.y ), z( other.z )
{
    Vec3(other.x, other.y, other.z);
}

Vec3::~Vec3(void)
{

}