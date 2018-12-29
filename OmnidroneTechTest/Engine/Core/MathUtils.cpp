#include "stdafx.h"
#include <Engine/Core/MathUtils.h>
#include <cmath>
#include <limits>

namespace Internal 
{
	static const double PI = 3.14159265358979323846;
}

double MathUtils::DegreesToRadians(double degrees)
{
	return degrees * Internal::PI / 180.0;
}

float MathUtils::CoordsTransform(float xf, float xo, float yf, float yo, float inputX)
{
	/*
			  (yf - yo)
	Y - yo = ----------- (X - xo)
		      (xf - xo)
	

		 (yf - yo)
	Y = ----------- (X - xo) + yo
		 (xf - xo)




	*/

	float A = (yf - yo);
	float B = (xf - xo);
	float C = (inputX - xo);

	if (MathUtils::IsFloatEqual(B,0.0f))
	{
		return 0.0f;
	}

	float outputY = ((A / B)*C) + yo;
	return outputY;
}

float MathUtils::Clamp(float value, float min, float max)
{
	return std::min(std::max(value, min), max);
}

float MathUtils::IsFloatEqual(float value1, float value2)
{
	return fabs(value1 - value2) < std::numeric_limits<double>::epsilon();
}
