#pragma once

#include <iostream>

class Vector
{
public:
	float x, y, z;

	Vector(void);
	Vector(float t);
	Vector(float x, float y, float z);
	~Vector(void);

	float& operator[](int id);
	float operator[](int id) const;

	Vector operator+(const Vector &v) const;
	Vector operator-(const Vector &v) const;
	Vector operator*(float t) const;
	Vector operator*(const Vector &v) const;
	Vector operator/(float t) const;

	Vector operator+=(const Vector &v);
	Vector operator-=(const Vector &v);
	Vector operator*=(float t);
	Vector operator/=(float t);
	
	bool operator<(const Vector &v) const;
	bool operator>(const Vector &v) const;
	bool operator<=(const Vector &v) const;
	bool operator>=(const Vector &v) const;
	bool operator==(const Vector &v) const;
	bool operator!=(const Vector &v) const;

	Vector operator-(void) const;
	float length(void) const;
	float length2(void) const;
	
	float distance(const Vector &v) const;
	float distance2(const Vector &v) const;

	Vector normalized(void) const;
	Vector normalize(void);

	friend std::ostream& operator<<(std::ostream &os, const Vector &v)
	{
		os << "[" << v.x << " " << v.y << " " << v.z << "]";
		return os;
	}
};

float dotProduct(const Vector &a, const Vector &b);
Vector crossProduct(const Vector &a, const Vector &b);
Vector pairwiseProduct(const Vector &a, const Vector &b);
float mixedProduct(const Vector &a, const Vector &b, const Vector &c);

Vector operator*(float t, const Vector &v);
