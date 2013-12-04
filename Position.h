#pragma once
class Position
{
public:

	Position(float xIn = 0.0, float yIn = 0.0, float zIn = 0.0);
	~Position(void);

	float x;
	float y;
	float z;
};