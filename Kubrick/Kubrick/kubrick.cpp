// Kubrick.cpp : Defines the entry point for the application.
//

#include "camera.hpp"
#include "utility.hpp"
#include "color.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"

#include <iostream>

using namespace std;

color rayColor(ray const& r, hittable const & world, int const depth) {
	hitRecord rec;

	if (depth <= 0) {
		return color{ 0.0, 0.0, 0.0};
	}

	if (world.hit(r, 0.0000000000001, infinity, rec)) {
		point3 const target{ rec.p + rec.normal + randomInHemisphere(rec.normal) };
		return 0.5 * rayColor(ray{ rec.p, target - rec.p }, world, depth - 1);
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
	int const samplesPerPixel{ 100 };
	int const maxDepth{ 50 };

	// World
	hittableList world;
	world.add(make_shared<sphere>(point3{ 0.0, 0.0, -1.0 }, 0.5));
	world.add(make_shared<sphere>(point3{ 0.0, -100.5, -1.0 }, 100.0));


	// Camera
	camera cam;

	// Render
	cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int j{ imageHeight - 1 }; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << " " << flush;
		for (int i{ 0 }; i < imageWidth; ++i) {
			color pixelColor{ 0.0, 0.0, 0.0 };
			for (int s{ 0 }; s < samplesPerPixel; ++s) {
				double const u{ (static_cast<double>(i) + randomDouble()) / static_cast<double>(imageWidth - 1) };
				double const v{ (static_cast<double>(j) + randomDouble()) / static_cast<double>(imageHeight - 1) };
				ray r{ cam.getRay(u, v) };
				pixelColor += rayColor(r, world, maxDepth);
			}
			writeColor(cout, pixelColor, samplesPerPixel);
		}
	}
	std::cerr << "\nDone.\n";





	return 0;
}
