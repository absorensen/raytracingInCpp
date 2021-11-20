#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
	double e[3];

private:

public:
	vec3() : e{ 0.0, 0.0, 0.0 }{}
	vec3( double e0, double e1, double e2): e{e0, e1, e2} {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(vec3 const & v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];

		return *this;
	}

	vec3& operator*=(double const t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(double const t) {
		return *this *= 1.0 / t;
	}

	double length() const {
		return sqrt(lengthSquared());
	}

	double lengthSquared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline static vec3 random() {
		return vec3{ randomDouble(), randomDouble(), randomDouble() };
	}

	inline static vec3 random(double const min, double const max) {
		return vec3{ randomDouble(min, max), randomDouble(min, max), randomDouble(min, max) };
	}


private:

};


inline std::ostream& operator<<(std::ostream& out, vec3 const& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(vec3 const & u, vec3 const & v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(vec3 const & u, vec3 const & v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(vec3 const & u, vec3 const & v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, vec3 const & v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(vec3 const & v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1.0 / t) * v;
}

inline static double dot(vec3 const & u, vec3 const & v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline static vec3 cross(vec3 const & u, vec3 const & v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline static vec3 unitVector(vec3 v) {
	return v / v.length();
}

inline static vec3 randomInUnitSphere() {
	for (;;) {
		vec3 const p{ vec3::random(-1.0, 1.0) };
		if (p.lengthSquared() >= 1.0) continue;
		return p;
	}
}

inline static vec3 randomUnitVector() {
	return unitVector(randomInUnitSphere());
}

inline static vec3 randomInHemisphere(vec3 const& normal) {
	vec3 const inUnitSphere{ randomInUnitSphere() };
	return dot(inUnitSphere, normal) > 0.0 ? inUnitSphere : -inUnitSphere;
}

using point3 = vec3;
using color = vec3;

#endif