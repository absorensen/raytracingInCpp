#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include <limits>
#include <memory>
//#include <cstdlib>
#include <random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


double const infinity{ std::numeric_limits<double>::infinity() };
double const pi{ 3.1415926535897932385 };


inline double degreesToRadians(double degrees) {
	return degrees * pi / 180.0;
}

//inline double randomDouble() {
//	return rand() / (RAND_MAX + 1.0);
//}

inline double randomDouble() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double randomDouble(double min, double max) {
	return min + (max - min) * randomDouble();
}

inline double clamp(double const x, double const min, double const max) {
	if (x < min) return min;
	if (max < x) return max;
	return x;
}


#include "ray.hpp"
#include "vec3.hpp"

#endif