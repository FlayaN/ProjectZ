#pragma once
#include <string>

class Material
{
public:
	Material(std::string labelIn = "unknown", float densityIn = 0.0);
	~Material(void);

	void setLabel(std::string);
	void setDensity(float);

	std::string getLabel(void);
	float getDensity(void);

private:
	std::string label;
	float density;
};

