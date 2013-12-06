#pragma once
class Coordinate
{
public:

	Coordinate(float xIn = 0.0, float yIn = 0.0, float zIn = 0.0);
	~Coordinate(void);

	float x;
	float y;
	float z;
};