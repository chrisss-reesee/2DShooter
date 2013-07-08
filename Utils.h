#pragma once

#include <limits>
#include "DarkGDK.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAMES_PER_SECOND	60

//a few useful constants
const int     MaxInt    = (std::numeric_limits<int>::max)();
const double  MaxDouble = (std::numeric_limits<double>::max)();
const double  MinDouble = (std::numeric_limits<double>::min)();
const float   MaxFloat  = (std::numeric_limits<float>::max)();
const float   MinFloat  = (std::numeric_limits<float>::min)();

void dbRectangle( int left, int top, int right, int bottom );

//compares two real numbers. Returns true if they are equal
inline bool isEqual(float a, float b)
{
  if (fabs(a-b) < 1E-12)
  {
    return true;
  }

  return false;
}

inline bool isEqual(double a, double b)
{
  if (fabs(a-b) < 1E-12)
  {
    return true;
  }

  return false;
}

inline double min(double a, double b)
{
	if( a < b )
		return a;
	return b;
}