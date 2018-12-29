#include "stdafx.h"
#include <Engine/Core/MathUtils.h>

namespace Internal 
{
	static const double PI = 3.14159265358979323846;
}

double MathUtils::DegreesToRadians(double degrees)
{
	return degrees * Internal::PI / 180.0;
}
