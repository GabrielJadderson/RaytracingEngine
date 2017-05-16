#include "color_rgba.h"
#include "color_hsla.h"
#include <algorithm>

ColorR& ColorR::operator=(const ColorR& other)
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
	return *this;
}

ColorR::operator ColorH() const
{
	auto rf = r / 255.0f;
	auto gf = g / 255.0f;
	auto bf = b / 255.0f;

	auto min = std::min(std::min(rf, gf), bf);
	auto max = std::max(std::max(rf, gf), bf);

	auto h = 0.0f;
	auto s = 0.0f;
	auto l = (min + max) / 2.0f;

	if (min != max) {
		auto delta = max - min;
		if (l > 0.5f)
			s = delta / (2.0f - max - min);
		else
			s = delta / (max + min);

		if (max == rf) {
			h = (gf - bf) / delta;
			if (gf < bf)
				h += 6.0f;
		}
		else if (max == gf) {
			h = (bf - rf) / delta + 2.0f;
		}
		else {
			h = (rf - gf) / delta + 4.0f;
		}

		h /= 6.0f;
	}

	return ColorH(h, s, l, a / 255.0f);
}

ColorH ColorR::to_hsla() const
{
	return static_cast<ColorH>(*this);
}