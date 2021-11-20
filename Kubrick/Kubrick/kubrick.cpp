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

hittableList randomBallsScene() {
	hittableList world;

	shared_ptr<lambertian> ground_material{ make_shared<lambertian>(color{ 0.5, 0.5, 0.5 }) };
	world.add(make_shared<sphere>(point3{ 0.0, -1000.0, 0 }, 1000.0, ground_material));

	for (int a = -11; a < 11; ++a) {
		for (int b = -11; b < 11; ++b) {
			double const choose_mat{ randomDouble() };
			point3 center{ a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble() };

			if ((center - point3{ 4, 0.2, 0 }).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					vec3 const albedo{ color::random() * color::random() };
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					color const albedo{ color::random(0.5, 1) };
					double const fuzz{ randomDouble(0, 0.5) };
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	shared_ptr<dielectric> material1{ make_shared<dielectric>(1.5) };
	world.add(make_shared<sphere>(point3{ 0.0, 1.0, 0.0 }, 1.0, material1));

	shared_ptr<lambertian> material2{ make_shared<lambertian>(color{0.4, 0.2, 0.1 }) };
	world.add(make_shared<sphere>(point3{ -4.0, 1.0, 0.0 }, 1.0, material2));

	shared_ptr<metal> material3{ make_shared<metal>(color{0.7, 0.6, 0.5 }, 0.0)};
	world.add(make_shared<sphere>(point3{ 4.0, 1.0, 0.0 }, 1.0, material3));

	return world;
}

int main()
{
	// Image
	double const aspectRatio{ 3.0 / 2.0 };
	int const imageWidth{ 600 };
	int const imageHeight{ static_cast<int>(imageWidth / aspectRatio) };
	int const samplesPerPixel{ 100 };
	int const maxDepth{ 20 };

	// World
	hittableList world { randomBallsScene() };


	// Camera
	point3 const lookFrom{ 13.0, 2.0, 3.0 };
	point3 const lookAt{ 0.0, 0.0, 0.0 };
	vec3 const vUp{ 0.0, 1.0, 0.0 };
	double const distToFocus{ 10.0 };
	double const aperture{ 0.1 };
	camera cam{ lookFrom, lookAt, vUp, 20.0, aspectRatio, aperture, distToFocus };

	// Render
	cout << "P3\n" << imageWidth << " " << imageHeight << "\n65535\n";

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
