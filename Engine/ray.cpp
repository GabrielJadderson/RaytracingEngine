#include "ray.h"

ray::ray()
{
	// Default constructor
}

ray::ray(Vector3 origin, Vector3 direction)
{
	this->origin = origin;
	this->direction = direction;
}

void ray::traceray(ray_info &info)
{

}