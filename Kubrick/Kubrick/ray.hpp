#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class ray {
public:
	point3 origin;
	vec3 direction;

private:

public:
	ray() {}
	ray(point3 const & origin, vec3 const & direction) : origin{origin}, direction{direction}
	{}

	point3 getOrigin() const { return origin; }
	vec3 getDirection() const { return direction; }

	point3 at(double const t) const {
		return origin + t * direction;
	}

private:

};


#endif