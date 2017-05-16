#include "material.h"

material::material()
{
	this->color = Vector3(0, 0, 0);
}

material::material(Vector3 color)
{
	this->color = color;
}