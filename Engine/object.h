#pragma once
#include "include.h"
#include "ray.h"

class object
{
public:
	virtual bool hit(ray& r, ray_info& info, float t_min, float t_max) = 0;
	int x;
};