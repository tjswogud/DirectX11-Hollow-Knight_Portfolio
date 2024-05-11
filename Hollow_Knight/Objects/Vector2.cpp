#include "Framework.h"
#include "Vector2.h"

Vector2::Vector2()
	:XMFLOAT2(0, 0)
{
}

Vector2::Vector2(float x, float y)
	: XMFLOAT2(x, y)
{
}

Vector2::Vector2(XMFLOAT2 value)
	: XMFLOAT2(value)
{
}

float Vector2::Length()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector2::Normalize()
{
	*this /= Length();
}

Vector2 Vector2::Normal()
{
	return Vector2(*this / Length());
}

float Vector2::Dot(Vector2 other)
{
	return this->x * other.x + this->y * other.y;
}

float Vector2::Cross(Vector2 other)
{
	return this->x * other.y - this->y * other.x;
}

bool Vector2::IsBetween(Vector2 v1, Vector2 v2)
{
	return this->Cross(v1) * this->Cross(v2) < 0;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(this->x * value, this->y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
	return Vector2(this->x / value, this->y / value);
}


void Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
}

void Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
}

void Vector2::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;
}

void Vector2::operator/=(const float& value)
{
	this->x /= value;
	this->y /= value;
}

Vector2 Vector2::operator*(const Matrix& value) const
{
	XMVECTOR vector = XMLoadFloat2(this);

	vector = XMVector2TransformCoord(vector, value); // vector2 * matrix ¸¦ °öÇÑ ÇÔ¼ö

	Vector2 position;
	XMStoreFloat2(&position, vector);

	return position;
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.y + v1.y * v2.x;
}

float Vector2::Distance(const Vector2& v1, const Vector2& v2)
{
	return (v1 - v2).Length();
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, const float& factor)
{
	return start + (end - start) * factor;
}
