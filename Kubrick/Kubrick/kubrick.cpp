// Kubrick.cpp : Defines the entry point for the application.
//

#include "camera.hpp"
#include "utility.hpp"
#include "color.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"
#include "material.hpp"

#include <iostream>

using namespace std;

color rayColor(ray const& r, hittable const & world, int const depth) {
	hitRecord rec;

	if (depth <= 0) {
		return color{ 0.0, 0.0, 0.0};
	}

	if (world.hit(r, 0.0000000000001, infinity, rec)) {
		ray scattered;
		color attenuation;
		if (rec.matPtr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * rayColor(scattered, world, depth - 1);
		}
		return color{ 0.0, 0.0, 0.0 };
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
	int const maxDepth{ 10 };

	// World
	double const R{ cos(pi * 0.25) };
	hittableList world;

	shared_ptr<lambertian> material_ground { make_shared<lambertian>(color{0.8, 0.8, 0.0}) };
	shared_ptr<lambertian> material_center{ make_shared<lambertian>(color{0.1, 0.2, 0.5}) };
	shared_ptr<dielectric> material_left { make_shared<dielectric>(1.5) };
	shared_ptr<metal> material_right{ make_shared<metal>(color{0.8, 0.6, 0.2}, 0.0) };

	world.add(make_shared<sphere>(point3{ 0.0, -100.5, -1.0 }, 100.0, material_ground));
	world.add(make_shared<sphere>(point3{0.0, 0.0, -1.0 }, 0.5, material_center));
	world.add(make_shared<sphere>(point3{-1.0, 0.0, -1.0 }, 0.5, material_left));
	world.add(make_shared<sphere>(point3{1.0, 0.0, -1.0 }, 0.5, material_right));


	// Camera
	camera cam{ point3{-2.0, 2.0, 1.0 }, point3{ 0.0, 0.0, -1.0 }, vec3{ 0.0, 1.0, 0.0 }, 90.0, aspectRatio };

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
