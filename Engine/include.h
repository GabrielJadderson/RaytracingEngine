#pragma once
#ifndef INCLUDE_H
#define INCLUDE_H

#include <Windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <time.h>
#include <math.h>
#include <string>
#include <memory>
#include <map>
#include <iterator>
#include <thread>
#include <chrono>
#include <mutex>

#ifndef FLT_EPSILON
#define FLT_EPSILON      1.192092896e-07F        // smallest such that 1.0+FLT_EPSILON != 1.0
#endif

typedef FLOAT               *PFLOAT;

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif


#define INRANGE(x, a, b)(x >= a && x <= b)
#define GETBITS(x)(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GETBYTE(x)(GETBITS(x[0]) << 4 | GETBITS(x[1]))

#endif

#define WIDTH 500;
#define HEIGHT 500;
#define SAMPLE_COUNT 1;


double randd()
{
	return (double) rand() / (RAND_MAX + 1.0);
}
