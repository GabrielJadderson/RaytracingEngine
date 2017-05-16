#include "color_hsla.h"
#include "color_rgba.h"

ColorH& ColorH::operator=(const ColorH& other)
{
	h = other.h;
	s = other.s;
	l = other.l;
	a = other.a;
	return *this;
}

ColorH::operator ColorR() const
{
	auto rf = 0.0f;
	auto gf = 0.0f;
	auto bf = 0.0f;

	if (s == 0.0f) {
		rf = l;
		gf = l;
		bf = l;
	}
	else {
		auto hue_to_rgb = [](float p, float q, float t) -> float
		{
			if (t > 1.0f)
				t -= 1.0f;
			else if (t < 0.0f)
				t += 1.0f;

			if (t < 1.0f / 6.0f)
				return p + (q - p) * 6.0f * t;
			if (t < 1.0f / 2.0)
				return q;
			if (t < 2.0f / 3.0f)
				return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
			return p;
		};

		auto q = 0.0f;
		if (l < 0.5f)
			q = l * (1.0f + s);
		else
			q = l + s - l * s;

		auto p = 2.0f * l - q;

		rf = hue_to_rgb(p, q, h + 1.0f / 3.0f);
		gf = hue_to_rgb(p, q, h);
		bf = hue_to_rgb(p, q, h - 1.0f / 3.0f);
	}

	return ColorR(rf * 255.0f, gf * 255.0f, bf * 255.0f, a * 255.0f);
}

ColorR ColorH::to_rgba() const
{
	return static_cast<ColorR>(*this);
}