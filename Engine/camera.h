#ifndef CAMERAH
#define CAMERAH
#include "ray.h"

double randd()
{
	return (double) rand() / (RAND_MAX + 1.0);
}

Vector3 random_in_unit_disk()
{
	Vector3 p;
	do
	{
		p = 2.0*Vector3(randd(), randd(), 0) - Vector3(1, 1, 0);
	}
	while (dot(p, p) >= 1.0);
	return p;
}

class camera
{
public:
	camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist)
	{ // vfov is top to bottom in degrees
		lens_radius = aperture / 2;
		float theta = vfov*3.14159265359 / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
		horizontal = 2 * half_width*focus_dist*u;
		vertical = 2 * half_height*focus_dist*v;
	}
	ray get_ray(float s, float t)
	{
		Vector3 rd = lens_radius*random_in_unit_disk();
		Vector3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
	}

	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 u, v, w;
	float lens_radius;
};
#endif
