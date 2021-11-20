#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utility.hpp"

class camera {
public:

private:
	point3 _origin;
	point3 _lowerLeftCorner;
	vec3 _horizontal;
	vec3 _vertical;

public:
	camera() {
		double const aspectRatio{ 16.0 / 9.0 };
		double const viewportHeight{ 2.0 };
		double const viewportWidth{ aspectRatio * viewportHeight };
		double const focalLength{ 1.0 };

		_origin = point3{ 0.0, 0.0, 0.0 };
		_horizontal = vec3{ viewportWidth, 0.0, 0.0 };
		_vertical = vec3{ 0.0, viewportHeight, 0.0 };
		_lowerLeftCorner = _origin - _horizontal * 0.5 - _vertical * 0.5 - vec3{0.0, 0.0, focalLength};
	}

	ray getRay(double const u, double const v) const {
		return ray(_origin, _lowerLeftCorner + u * _horizontal + v * _vertical - _origin);
	}

private:
};


#endif