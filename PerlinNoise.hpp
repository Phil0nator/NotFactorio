
#include <math.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
class PerlinNoise{


	private:
		
		
		vector<int> p;
	 	double fade(double t);
 		double lerp(double t, double a, double b);
		double grad(int hash, double x, double y, double z);



	public:
		PerlinNoise();
		PerlinNoise(unsigned int seed);
		double noise(double x, double y, double z);

};


PerlinNoise::PerlinNoise(unsigned int seed){

	p.resize(256);
	std::iota(p.begin(), p.end(), 0);






}