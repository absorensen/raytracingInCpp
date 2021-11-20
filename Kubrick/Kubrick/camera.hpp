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
	vec3 _u;
	vec3 _v;
	vec3 _w;
	double _lensRadius;

public:
	camera(
		point3 const lookFrom,
		point3 const lookAt,
		vec3 const vUp,
		double const vFOV,
		double const aspectRatio,
		double const aperture,
		double focusDist
	) {
		double const theta{ degreesToRadians(vFOV) };
		double const h{ tan(theta * 0.5) };
		double const viewportHeight{ 2.0 * h };
		double const viewportWidth{ aspectRatio * viewportHeight };
		
		_w = unitVector(lookFrom - lookAt);
		_u = unitVector(cross(vUp, _w));
		_v = unitVector(cross(_w, _u));

		_origin = lookFrom;
		_horizontal = focusDist * viewportWidth * _u;
		_vertical = focusDist * viewportHeight * _v;
		_lowerLeftCorner = _origin - _horizontal * 0.5 - _vertical * 0.5 - focusDist * _w;
	
		_lensRadius = aperture * 0.5;
	}

	ray getRay(double const s, double const t) const {
		vec3 const rd{ _lensRadius * randomInUnitDisk() };
		vec3 const offset{ _u * rd.x() + _v * rd.y() };

		return ray(_origin + offset, _lowerLeftCorner + s * _horizontal + t * _vertical - _origin - offset);
	}

private:
};


#endif