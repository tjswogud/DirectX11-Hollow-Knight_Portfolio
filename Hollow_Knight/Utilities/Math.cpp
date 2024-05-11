#include "Framework.h"
#include "Math.h"

double Math::Distance(Vector2 p1, Vector2 p2)
{
    Vector2 distance = p1 - p2;

    return sqrt(pow(distance.x, 2) + pow(distance.y, 2));
}

double Math::ToRadian(double degree)
{
    return degree * XM_PI / 180;
}

double Math::ToDegree(double radian)
{
    return radian * 180 / XM_PI;
}

// 50~100
// rand() % 51 + 50;
// rate , ratio
// 

int Math::Random(const int& min, const int& max)
{
    return rand() % (max - min) + min;
}

// 70~100
// rand/RAND_MAX = 0~1
// 0 ~ 30   + 70 
// * (max - min) + min
double Math::Random(const double& min, const double& max)
{
    return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}
