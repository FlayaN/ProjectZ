#ifndef PERLINNOISE_H
#define PERLINNOISE_H

class PerlinNoise
{
public:

    static PerlinNoise& getInstance(void)
	{
	static PerlinNoise instance;
	return instance;
	}
	~PerlinNoise(void);

	void SetValues(double, double, double, int, int);
	void SetPersistence(double);
	void SetFrequency(double);
	void SetAmplitude(double);
	void SetOctaves(int);
	void SetSeed(int);

	double GetHeight(double, double);
	double getPersistance(void);
	double getFrequency(void);
	double getAmplitude(void);
	int getOctaves(void);
	int getSeed(void);

private:

	PerlinNoise(double persistenceIn = 0.0, double frequencyIn = 0.0, double amplitudeIn = 0.0, int octavesIn = 0, int seedIn = 0);
	PerlinNoise(PerlinNoise const&);
	PerlinNoise &operator=(PerlinNoise const&);

	// help functions
    double Total(double, double);
    double GetValue(double, double);
    double Interpolate(double, double, double);
    double Noise(int, int);

    double persistence;
	double frequency;
	double amplitude;
    int octaves;
	int seed;
};

#endif