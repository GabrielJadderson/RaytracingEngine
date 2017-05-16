#include "camera.h"
#include "Game.h"

camera::camera(Vector3 originPos, Vector3 lookDirection, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist)
{
	lens_radius = aperture / 2;
	float theta = vfov * 3.14159265359 / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	origin = originPos;
	w = unit_vector(originPos - lookDirection);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
	horizontal = 2 * half_width * focus_dist * u;
	vertical = 2 * half_height * focus_dist * v;
	width = WIDTH;
	height = HEIGHT;
}


//camera* camera::get()
//{
//static camera g_camera;
//return &g_camera;
//}


void camera::add_object(object* o)
{
	objects.push_back(o);
}

double randd()
{
	return (double) rand() / (RAND_MAX + 1.0);
}

Vector3 random_in_unit_disk()
{
	Vector3 p;
	do
	{
		p = 2.0 * Vector3(randd(), randd(), 0) - Vector3(1, 1, 0);
	}
	while (dot(p, p) >= 1.0);
	return p;
}



ray camera::get_ray(float s, float t)
{
	Vector3 rd = lens_radius * random_in_unit_disk();
	Vector3 offset = u * rd.x() + v * rd.y();
	return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}


void camera::render(Game game)
{

	for (int y = height; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			Vector3 color;

			float ndc_x = (x + 0.5f) / width;
			float ndc_y = (y + 0.5f) / height;

			float screen_x = 2 * ndc_x - 1;
			float screen_y = 1 - 2 * ndc_y;

			ray r(Vector3(0, 0, 0), Vector3(screen_x, screen_y, -1));
			ray_info info;

			for (auto it : objects)
			{
				if (it->hit(r, info, 0.f, FLT_MAX))
				{
					color = info.mat->color;
				}
			}

			game.drawPixel(x, y, color.x(), color.y(), color.z());
		}
	}
}