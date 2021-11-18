// Kubrick.cpp : Defines the entry point for the application.
//

#include "kubrick.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"

#include <iostream>

using namespace std;

bool hitSphere(point3 const& center, double const radius, ray const & r) {
	vec3 const oc{ r.getOrigin() - center };
	double const a{ dot(r.getDirection(), r.getDirection()) };
	double const b{ 2.0 * dot(oc, r.getDirection()) };
	double const c{ dot(oc, oc) - radius * radius };
	double const discriminant{ b * b - 4.0 * a * c };
	return (discriminant > 0.0);
}

color rayColor(ray const& r) {
	if (hitSphere(point3{ 0.0, 0.0, -1.0 }, 0.5, r)) {
		return color{ 1.0, 0.0, 0.0 };
	}
	vec3 const unitDirection{ unitVector(r.getDirection()) };
	double const t{ 0.5 * (unitDirection.y() + 1.0) };
	return (1.0 - t) * color { 1.0, 1.0, 1.0 } + t * color{ 0.5, 0.7, 1.0 };
}

int main()
{
	// Image
	double const aspectRatio{ 16.0 / 9.0 };
	int const imageWidth{ 400 };
	int const imageHeight{ static_cast<int>(imageWidth / aspectRatio) };

	// Camera
	double const viewportHeight{ 2.0 };
	double const viewportWidth{ aspectRatio * viewportHeight };
	double const focalLength{ 1.0 };

	point3 const origin{ 0.0, 0.0, 0.0 };
	vec3 const horizontal{ viewportWidth, 0.0, 0.0 };
	vec3 const vertical{ 0.0, viewportHeight, 0.0 };
	vec3 const lowerLeftCorner{ origin - horizontal * 0.5 - vertical * 0.5 - vec3{0.0, 0.0, focalLength} };

	// Render
	cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int j{ imageHeight - 1 }; j >= 0; --j) {
		cerr << "\rScanlines remaining: " << j << " " << flush;
		for (int i{ 0 }; i < imageWidth; ++i) {
			auto u = double(i) / (imageWidth - 1);
			auto v = double(j) / (imageHeight - 1);
			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			color pixelColor = rayColor(r);
			writeColor(cout, pixelColor);
		}
	}
	cerr << "\nDone.\n";





	return 0;
}
