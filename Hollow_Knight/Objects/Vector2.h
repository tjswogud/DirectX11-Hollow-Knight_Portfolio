#pragma once

#define V_LEFT  Vector2(-1 ,  0)
#define V_RIGHT Vector2(+1 ,  0)
#define V_UP    Vector2( 0 , +1)
#define V_DOWN  Vector2( 0 , -1)
#define V_LUP   Vector2(-1 , +1).Normal()
#define V_LDOWN Vector2(-1 , -1).Normal()
#define V_RUP   Vector2(+1 , +1).Normal()
#define V_RDOWN Vector2(+1 , -1).Normal()

class Vector2 : public XMFLOAT2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(XMFLOAT2 value);

	float Length();

	void    Normalize();
	Vector2 Normal();

	float Dot(Vector2 other);
	float Cross(Vector2 other);

	bool IsBetween(Vector2 v1, Vector2 v2);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const   float& value) const;
	Vector2 operator/(const   float& value) const;

	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);
	void operator*=(const   float& value);
	void operator/=(const   float& value);

	Vector2 operator* (const Matrix& value) const;

	static float      Dot(const Vector2& v1, const Vector2& v2);
	static float    Cross(const Vector2& v1, const Vector2& v2);
	static float Distance(const Vector2& v1, const Vector2& v2);

	static Vector2 Lerp(const Vector2& start, const Vector2& end, const float& factor); // 선형보간 
};
