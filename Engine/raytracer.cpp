#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include <float.h>
#include "camera.h"
#include "material.h"
#include "Game.h"
#include <fstream>
#include "raytracer.h"


Vector3 color(const ray& r, hitable* world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		ray scattered;
		Vector3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return Vector3(0, 0, 0);
		}
	}
	else
	{
		Vector3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
	}
}


hitable* random_scene()
{
	int n = 500;
	hitable** list = new hitable*[n + 1];
	list[0] = new sphere(Vector3(0, -1000, 0), 1000, new lambertian(Vector3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = randd();
			Vector3 center(a + 0.9 * randd(), 0.2, b + 0.9 * randd());
			if ((center - Vector3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{ // diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(Vector3(randd() * randd(), randd() * randd(), randd() * randd())));
				}
				else if (choose_mat < 0.95)
				{ // metal
					list[i++] = new sphere(center, 0.2,
										   new metal(Vector3(0.5 * (1 + randd()), 0.5 * (1 + randd()), 0.5 * (1 + randd())), 0.5 * randd()));
				}
				else
				{ // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(Vector3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(Vector3(-4, 1, 0), 1.0, new lambertian(Vector3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(Vector3(4, 1, 0), 1.0, new metal(Vector3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}


void raytracer::dotrace(Game *game, int width, int height, int sample_count)
{
	int nx = width;
	int ny = height;
	int ns = sample_count;

	/*
	hitable* list[5];
	float R = cos(3.14159265359 / 4);
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable* world = new hitable_list(list, 5);
	world = random_scene();
	*/
	hitable* list[1];
	list[0] = new sphere(Vector3(0, 0, -1), 0.5, new lambertian(Vector3(0.1, 0.2, 0.5)));
	hitable* world = new hitable_list(list, 1);

	Vector3 lookfrom(5, 2, 8);
	Vector3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;

	camera cam(lookfrom, lookat, Vector3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vector3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + randd()) / float(nx);
				float v = float(j + randd()) / float(ny);
				ray r = cam.get_ray(u, v);
				Vector3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			game->drawPixel(i, j, ir, ig, ib);
		}
	}
}