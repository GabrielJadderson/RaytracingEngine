#include "include.h"
#include "color_rgba.h"
#include "Vector3.h"
#include "sphere.h"
#include "camera.h"
#include "raytracer.h"
#include "Game.h"

void raytracer::dotrace(Game &game)
{
	sphere* gabe = new sphere(Vector3(0, 0, -2), 1, material(Vector3(255, 0, 0)));
	sphere* fred = new sphere(Vector3(0, 0, -3), 1, material(Vector3(0, 255, 0)));

	Vector3 origin(0, 0, 0);
	Vector3 lookDirection(0, 0, 0);
	float aperture = 2;
	float fov = 10;
	float focus_distance = 10;
	float aspect = 10;
	camera camera(origin, lookDirection, Vector3(0, 1, 0), fov, aspect, aperture, focus_distance);

	camera.render(&game);

	//camera::get()->set_size(500, 500);

	//camera::get()->add_object(gabe);

	//camera::get()->add_object(fred);

	//camera::get()->render();
}