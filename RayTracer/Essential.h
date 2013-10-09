#pragma once

namespace efl
{
	const float ZERO = 1e-4;
	const float INF = 1e10;
	const float PI = 3.14159265359;
	const float bias = 1e-4;

	template<class T>
	T abs(T x)
	{
		return x < 0 ? -x : x;
	}

	template<class T>
	int sgn(T x)
	{
		return abs(x) < 0.0f ? 0 : (x < 0 ? -1 : 1);
	}

	template<class T>
	T min(T x, T y)
	{
		return x < y ? x : y;
	}

	template<class T>
	T max(T x, T y)
	{
		return x > y ? x : y;
	}

	template<class T>
	T min(T x, T y, T z)
	{
		return x < y ? (x < z ? x : z) : (y < z ? y : z);
	}

	template<class T>
	T max(T x, T y, T z)
	{
		return x > y ? (x > z ? x : z) : (y > z ? y : z);
	}

	template<class T>
	bool isBetween(T x, T a, T b)
	{
		return a <= x && x <= b;
	}

	template<class T>
	T intervalIntersection(T a1, T a2, T b1, T b2)
	{
		return max(min(a2, b2) - max(a1, b1), 0);
	}

	template<class T>
	T intervalDistance(T a1, T a2, T b1, T b2)
	{
		return max(a1, b1) - min(a2, b2);
	}

	template<class T>
	T mix(const T &a, const T &b, const T &mix)
	{
		return b * mix + a * (T(1) - mix);
	}

	template<class T>
	T pow(T a, int b)
	{
		T ret;
		for(ret = a; --b; ret *= a);
		return ret;
	}

	template<class T>
	T fastPow(T b, int e) 
	{
		T ret = 1;
		for(; e; e >>= 1)
		{
			if(e & 1)
				ret *= b;
			b *= b;
		}
		return ret;
	}
}