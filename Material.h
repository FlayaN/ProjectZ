#pragma once
#include <string>

class Material
{
public:
	Material(std::string, float);
	~Material(void);

	void setLabel(std::string);
	void setDensity(float);

	std::string getLabel(void);
	float getDensity(void);

private:
	std::string label;
	float density;
};

