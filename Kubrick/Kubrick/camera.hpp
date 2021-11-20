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
	camera(
		point3 const lookFrom,
		point3 const lookAt,
		vec3 const vUp,
		double const vFOV,
		double const aspectRatio
	) {
		double const theta{ degreesToRadians(vFOV) };
		double const h{ tan(theta * 0.5) };
		double const viewportHeight{ 2.0 * h };
		double const viewportWidth{ aspectRatio * viewportHeight };
		
		vec3 const w{ unitVector(lookFrom - lookAt) };
		vec3 const u{ unitVector(cross(vUp, w)) };
		vec3 const v{ unitVector(cross(w, u)) };

		_origin = lookFrom;
		_horizontal = viewportWidth * u;
		_vertical = viewportHeight * v;
		_lowerLeftCorner = _origin - _horizontal * 0.5 - _vertical * 0.5 - w;
	}

	ray getRay(double const s, double const t) const {
		return ray(_origin, _lowerLeftCorner + s * _horizontal + t * _vertical - _origin);
	}

private:
};


#endif