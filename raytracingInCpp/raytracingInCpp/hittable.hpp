#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "utility.hpp"

class material;


struct hitRecord {
	point3 p;
	vec3 normal;
	shared_ptr<material> matPtr;
	double t;
	bool frontFace;


	inline void setFaceNormal(ray const& r, vec3 const& outwardNormal) {
		frontFace = dot(r.getDirection(), outwardNormal) < 0.0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class hittable {
public:
	virtual bool hit(ray const& r, double tMin, double tMax, hitRecord& rec) const = 0;
};

#endif