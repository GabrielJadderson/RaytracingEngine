#pragma once
#include "include.h"
#include "object.h"

class Game;

class camera
{
public:
	//static camera* get();
	camera(Vector3 originPos, Vector3 lookDirection, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist);
	void set_size(int w, int h);
	ray get_ray(float u, float v);
	void add_object(object* o);

	void render(Game game);

private:
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 u, v, w;
	float lens_radius;
	int width, height;
	std::vector<object*> objects;
};
