#pragma once
#include "include.h"
#include "Vector3.h"
#include "material.h"

struct ray_info
{
	Vector3 point;
	Vector3 normal;
	float t;
	material* mat;
};

class ray
{
public:
	ray();
	ray(Vector3 origin, Vector3 direction);
	Vector3 origin, direction;


	inline Vector3 point_at_perimeter(float t)
	{
		return origin + (direction * t);
	}

	void traceray(ray_info &info);
};