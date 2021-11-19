#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {
public:
	point3 center;
	double radius;


public:
	sphere(){}
	sphere(point3 cen, double r) : center(cen), radius(r) {};

	virtual bool hit(ray const& r, double tMin, double tMax, hitRecord& rec) const override;
};

bool sphere::hit(ray const& r, double tMin, double tMax, hitRecord& rec) const {
	vec3 const oc{ r.getOrigin() - center };
	double const a{ r.getDirection().lengthSquared() };
	double const halfB{ dot(oc, r.getDirection()) };
	double const c{ oc.lengthSquared() - radius * radius };
	double const discriminant{ halfB * halfB - a * c };

	if (discriminant < 0.0) {
		return false;
	}
	
	double const sqrtD{ sqrt(discriminant) };

	double root{ (-halfB - sqrtD) / a };
	if (root < tMin || tMax < root) {
		root = (-halfB + sqrtD) / a;
		if (root < tMin || tMax < root) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 const outwardNormal{ (rec.p - center) / radius };
	rec.setFaceNormal(r, outwardNormal);

	return true;
}

#endif