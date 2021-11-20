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

class dielectric : public material {
public:
	double ir;

private:


public: 
	dielectric(double indexOfRefraction) : ir(indexOfRefraction){}

	virtual bool scatter(ray const& rIn, hitRecord const& rec, color& attenuation, ray& scattered) const override{
		attenuation = color(1.0, 1.0, 1.0);
		double const refractionRatio{ rec.frontFace ? (1.0 / ir) : ir };

		vec3 const unitDirection{ unitVector(rIn.getDirection()) };

		double const cosTheta{ fmin(dot(-unitDirection, rec.normal), 1.0) };
		double const sinTheta{ sqrt(1.0 - cosTheta * cosTheta) };

		bool const cannotRefract{ refractionRatio * sinTheta > 1.0 };
		
		vec3 direction;

		if (cannotRefract || _reflectance(cosTheta, refractionRatio) > randomDouble()) {
			direction = reflect(unitDirection, rec.normal);
		}
		else {
			direction = refract(unitDirection, rec.normal, refractionRatio);
		}

		scattered = ray{ rec.p, direction };

		return true;
	}

private:

	static double _reflectance(double const cosine, double const reflectanceIndex) {
		double r0{ (1.0 - reflectanceIndex) / (1.0 + reflectanceIndex) };
		r0 = r0 * r0;
		return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
	}

};

#endif