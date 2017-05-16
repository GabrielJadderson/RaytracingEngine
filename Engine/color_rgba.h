#pragma once
class ColorH;

class ColorR {
public:
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	ColorR() {}
	ColorR(int r, int g, int b) : r(r), g(g), b(b) {}
	ColorR(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

	ColorR& operator=(const ColorR& other);

	explicit operator ColorH() const;

	ColorH to_hsla() const;
};