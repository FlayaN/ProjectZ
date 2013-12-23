#pragma once

#include "Vec2.h"

#ifndef VEC3_H
#define VEC3_H

class Vec3 : public Vec2
{
public:

	Vec3(float xIn = 0.0, float yIn = 0.0, float zIn = 0.0);
	Vec3(const Vec3& other);
	~Vec3(void);

	Vec3& operator+=(const Vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}

	Vec3& operator-=(const Vec3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}

	Vec3& operator/=(const Vec3& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		return *this;
	}
    
    Vec3& operator*=(const Vec3& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}
    
    bool operator==(const Vec3 &other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	float z;
};

inline Vec3 operator+(Vec3 lhs, const Vec3& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Vec3 operator-(Vec3 lhs, const Vec3& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Vec3 operator/(Vec3 lhs, const Vec3& rhs)
{
	lhs /= rhs;
	return lhs;
}

inline Vec3 operator*(Vec3 lhs, const Vec3& rhs)
{
	lhs *= rhs;
	return lhs;
}

#endif