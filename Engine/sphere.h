#pragma once
#include "object.h"

class sphere : public object
{
public:
	sphere(Vector3 position, float radius, material mat);

	bool intersect(ray& r, ray_info& info);
	bool solve_quadratic(const float &a, const float &b, const float &c, float &x0, float &x1);
	bool hit(ray& r, ray_info& info, float t_min, float t_max);
	
	Vector3 position;
	float radius;
	material mat;
};