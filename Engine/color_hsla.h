#pragma once
class ColorR;

class ColorH {
public:
	float h = 0.0f;
	float s = 0.0f;
	float l = 0.0f;
	float a = 1.0f;

	ColorH() {}
	ColorH(float h, float s, float l) : h(h), s(s), l(l) {}
	ColorH(float h, float s, float l, float a) : h(h), s(s), l(l), a(a) {}

	ColorH& operator=(const ColorH& other);

	explicit operator ColorR() const;

	ColorR to_rgba() const;
};