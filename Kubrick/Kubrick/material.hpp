#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "utility.hpp"

struct hitRecord;

class material {
public:
	virtual bool scatter(ray const& rIn, hitRecord const& rec, color& attenuation, ray& scattered) const = 0;

};

class lambertian : public material {
public:
	color albedo;

private:

public:
	lambertian(color const& a) : albedo(a){}

	virtual bool scatter(ray const& rIn, hitRecord const & rec, color& attenuation, ray& scattered) const override {
		vec3 scatterDirection{ rec.normal + randomUnitVector() }; // Try randomInHemisphere(rec.normal) 

		if (scatterDirection.nearZero()) {
			scatterDirection = rec.normal;
		}

		scattered = ray{ rec.p, scatterDirection }; // Try to normalize scatter direction
		attenuation = albedo; // Try to only scatter with some probability p and let this line be albedo/p
		return true;
	}

private:


};

class metal : public material {
public:
	color albedo;
	double fuzz;
private:

public:
	metal(color const& a, double const f) : albedo{ a }, fuzz{f < 1.0 ? f : 1.0} {}

	virtual bool scatter(ray const& rIn, hitRecord const& rec, color& attenuation, ray& scattered) const override {
		vec3 const reflected{ reflect(unitVector(rIn.getDirection()), rec.normal) };
		scattered = ray{ rec.p, reflected + fuzz * randomInUnitSphere()};
		attenuation = albedo;
		return dot(scattered.getDirection(), rec.normal) > 0.0;
	}

private:
};

#endif