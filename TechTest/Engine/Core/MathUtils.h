#pragma once

namespace MathUtils 
{
	double DegreesToRadians(double degrees);

	float CoordsTransform(float xo, float xf, float yo, float yf, float inputX);
	float Clamp(float value, float min, float max);
	float IsFloatEqual(float value1, float value2);
}