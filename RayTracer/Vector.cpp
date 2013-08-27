#include "StdAfx.h"
#include "Vector.h"
#include "Essential.h"
#include <cmath>

Vector::Vector(void)
	: x(0.0f), y(0.0f), z(0.0f)
{
}

Vector::Vector(float t)
	: x(t), y(t), z(t)
{
}

Vector::Vector(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector::~Vector(void)
{
}

float& Vector::operator[](int id)
{
	return *(&x+id);
}

float Vector::operator[](int id) const
{
	return *(&x+id);
}

Vector Vector::operator+(const Vector &v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator+=(const Vector &v)
{
	return *this = *this + v;
}

Vector Vector::operator-(const Vector &v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator-=(const Vector &v)
{
	return *this = *this - v;
}

Vector Vector::operator*(float t) const
{
	return Vector(t * x, t * y, t * z);
}

Vector Vector::operator*(const Vector &v) const
{
	return Vector(v.x * x, v.y * y, v.z * z);
}

Vector Vector::operator/(float t) const
{
	return Vector(x / t, y / t, z / t);
}

Vector Vector::operator/=(float t)
{
	return *this = *this / t;
}

Vector Vector::operator*=(float t)
{
	return *this = *this * t;
}

bool Vector::operator<(const Vector &v) const
{
	return x < v.x || x == v.x && (y < v.y || y == v.y && z < v.z);
}

bool Vector::operator>(const Vector &v) const
{
	return x > v.x || x == v.x && (y > v.y || y == v.y && z > v.z);
}

bool Vector::operator<=(const Vector &v) const
{
	return !(*this > v);
}

bool Vector::operator>=(const Vector &v) const
{
	return !(*this < v);
}

Vector Vector::operator-(void) const
{
	return Vector(-x, -y, -z);
}

float Vector::length(void) const
{
	return sqrt(length2());
}

float Vector::length2(void) const
{
	return x * x + y * y + z * z;
}
	
float Vector::distance(const Vector &v) const
{
	return (*this - v).length();
}

float Vector::distance2(const Vector &v) const
{
	return (*this - v).length2();
}

Vector Vector::normalized(void) const
{
	if(!x && !y && !z)
		return *this;
	return *this / length();
}

Vector Vector::normalize(void)
{
	if(!x && !y && !z)
		return *this;
	return *this /= length();
}

bool Vector::operator==(const Vector &v) const
{
	return x == v.x && y == v.y && z == v.z;
}

bool Vector::operator!=(const Vector &v) const
{
	return x != v.x || y != v.y || z != v.z;
}

float dotProduct(const Vector &a, const Vector &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector crossProduct(const Vector &a, const Vector &b)
{
	return Vector
	(
		a.y * b.z - b.y * a.z,
		b.x * a.z - a.x * b.z,
		a.x * b.y - b.x * a.y
	);
}

Vector pairwiseProduct(const Vector &a, const Vector &b)
{
	return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}

float mixedProduct(const Vector &a, const Vector &b, const Vector &c)
{
	return dotProduct(a, crossProduct(b, c));
}

Vector operator*(float t, const Vector &v)
{
	return v * t;
}
