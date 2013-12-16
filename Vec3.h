#pragma once
class Vec3
{
public:

	Vec3(float xIn = 0.0, float yIn = 0.0, float zIn = 0.0);
	~Vec3(void);

	Vec3& operator+=(const Vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}

	float x;
	float y;
	float z;
};

inline Vec3 operator+(Vec3 lhs, const Vec3& rhs)
{
	lhs += rhs;
	return lhs;
}