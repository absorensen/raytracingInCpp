#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


double const infinity{ std::numeric_limits<double>::infinity() };
double const pi{ 3.1415926535897932385 };


inline double degreesToRadians(double degrees) {
	return degrees * pi / 180.0;
}

#include "ray.hpp"
#include "vec3.hpp"

#endif