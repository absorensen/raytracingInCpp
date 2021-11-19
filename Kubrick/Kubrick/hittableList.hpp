#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittableList : public hittable {
public:
	std::vector<shared_ptr<hittable>> objects;

public:
	hittableList() {}
	hittableList(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(ray const& r, double tMin, double tMax, hitRecord& rec) const override;

};

bool hittableList::hit(ray const& r, double tMin, double tMax, hitRecord& rec) const {
	hitRecord tempRec;
	bool hitAnything{ false };
	double closestSoFar{ tMax };

	for (shared_ptr<hittable> const& object : objects) {
		if (object->hit(r, tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

#endif