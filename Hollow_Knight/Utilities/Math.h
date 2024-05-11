#pragma once

class Vector2;

namespace Math
{
	double Distance(Vector2 p1, Vector2 p2);

	double ToRadian(double degree);
	double ToDegree(double radian);

	   int Random(const    int& min, const    int& max); //max exclusive 
	double Random(const double& min, const double& max); //max inclusive 
}