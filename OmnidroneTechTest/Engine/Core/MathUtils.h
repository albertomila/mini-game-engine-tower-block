#pragma once

namespace MathUtils 
{
	double DegreesToRadians(double degrees);

	float CoordsTransform(float xf, float xo, float yf, float yo, float inputX);
	float Clamp(float value, float min, float max);
	float IsFloatEqual(float value1, float value2);
}