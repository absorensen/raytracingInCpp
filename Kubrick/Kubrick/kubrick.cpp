// Kubrick.cpp : Defines the entry point for the application.
//

#include "utility.hpp"
#include "color.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"

#include <iostream>

using namespace std;

color rayColor(ray const& r, hittable const & world) {
	hitRecord rec;
	if (world.hit(r, 0.0, infinity, rec)) {
		return 0.5 * (rec.normal + color{1.0, 1.0, 1.0});
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

	// World
	hittableList world;
	world.add(make_shared<sphere>(point3{ 0.0, 0.0, -1.0 }, 0.5));
	world.add(make_shared<sphere>(point3{ 0.0, -100.5, -1.0 }, 100.0));


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
			color pixelColor = rayColor(r, world);
			writeColor(cout, pixelColor);
		}
	}
	cerr << "\nDone.\n";





	return 0;
}
