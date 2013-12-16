#pragma once
class Vec2
{
public:

	Vec2(float xIn = 0.0, float yIn = 0.0);
	~Vec2(void);

	Vec2& operator+=(const Vec2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	float x;
	float y;
};

inline Vec2 operator+(Vec2 lhs, const Vec2& rhs)
{
	lhs += rhs;
	return lhs;
}