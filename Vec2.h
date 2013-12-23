#pragma once

#include <iostream>

#include "Defines.h"
#include "Utility.h"

#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:

	Vec2(float xIn = 0.0, float yIn = 0.0);
	~Vec2(void);
    
    Vec2 inTileCoord(void);
    Vec2 inChunkCoord(void);

	Vec2& operator+=(const Vec2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
    
	Vec2& operator-=(const Vec2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
    
	Vec2& operator/=(const Vec2& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}
    
    Vec2& operator*=(const Vec2& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}
    
    bool operator==(const Vec2 &other) const
	{
		return (x == other.x && y == other.y);
	}

	Vec2 withinRange(void);

	float x;
	float y;
};

inline Vec2 operator+(Vec2 lhs, const Vec2& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Vec2 operator-(Vec2 lhs, const Vec2& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Vec2 operator/(Vec2 lhs, const Vec2& rhs)
{
	lhs /= rhs;
	return lhs;
}

inline Vec2 operator*(Vec2 lhs, const Vec2& rhs)
{
	lhs *= rhs;
	return lhs;
}

inline std::ostream &operator<<(std::ostream &out, Vec2 c)
{
    out << c.x << " : " << c.y << " ";
    return out;
}

namespace std
{
	template <>
	struct hash<Vec2>
	{
		std::size_t operator()(const Vec2& k) const
		{
			using std::size_t;
			using std::hash;
            
			return ((hash<int>()(k.x)
                     ^ (hash<int>()(k.y) << 1))
                    );
		}
	};
}

#endif