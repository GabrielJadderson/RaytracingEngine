#pragma once
#include "include.h"
#include "Vector3.h"

enum
{
	STANDARD,
	GLASS
};

class material
{
public:
	material();
	material(Vector3 color);
	Vector3 color;

private:
	int type;
};