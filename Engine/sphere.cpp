#include "sphere.h"

sphere::sphere(Vector3 position, float radius, material mat)
{
	this->position = position;
	this->radius = radius;
	this->mat = mat;
}

bool sphere::intersect(ray& r, ray_info& info)
{
	float t0, t1; // solutions for t if the ray intersects 
#if 0 
				  // geometric solution
	Vec3f L = center - orig;
	float tca = L.dotProduct(dir);
	// if (tca < 0) return false;
	float d2 = L.dotProduct(L) - tca * tca;
	if (d2 > radius2) return false;
	float thc = sqrt(radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;
#else 
				  // analytic solution
	Vector3 L = r.origin - position;
	float a = dot(r.direction,r.direction);//dir.dotProduct(dir);
	float b = 2 * dot(r.direction, L);//dir.dotProduct(L);
	float c = dot(L,L) - radius;
	if (!solve_quadratic(a, b, c, t0, t1)) return false;
#endif 
	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0) 
	{
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0)
			return false; // both t0 and t1 are negative 
	}


	info.t = t0;
	info.mat = &mat;
	info.point = r.point_at_perimeter(t0);
	Vector3 normal = info.point - position;
	info.normal = normal.normalize();

	return true;
}

bool sphere::solve_quadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}

bool sphere::hit(ray& r, ray_info& info, float t_min, float t_max)
{
	bool did_hit = false;

	Vector3 OC = r.origin - position;
	float a = dot(r.direction, r.direction);
	float b = dot(OC, r.direction);
	float c = dot(OC, OC) - (radius * radius);
	float discriminant = (b * b) - (a * c);

	if (discriminant > 0)
	{
		float temp = (-b - sqrt((b * b) - (a * c))) / a;
		if (temp < t_max && temp > t_min)
		{
			info.t = temp;
			info.point = r.point_at_perimeter(temp);
			info.normal = (info.point - position) / radius;
			did_hit = true;
		}
		temp = (-b + sqrt((b*b) - (a*c)) / a);
		if (temp < t_max && temp > t_min)
		{
			info.t = temp;
			info.point = r.point_at_perimeter(temp);
			info.normal = (info.point - position) / radius;
			did_hit = true;
		}
	}

	info.mat = &mat;

	return did_hit;
}