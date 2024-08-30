#pragma once
#include <arithmatic.h>
#include <SFML/Graphics.hpp>
#include <cmath>

namespace LLGP 
{
	template<typename T> requires arithmetic<T>

	struct Vector2 
	{
	public:
		T x, y;

		// Constructors
		Vector2() : x(0), y(0) {}
		Vector2(const Vector2&) = default;
		Vector2(T _x, T _y) : x(_x), y(_y) {}

		// Conversion to LLGP Vector2
		template<typename U> requires arithmetic<U>
		explicit Vector2(const sf::Vector2<U>& in) : x(static_cast<T>(in.x)), y(static_cast<T>(in.y)) {}

		template<typename U> requires arithmetic<U>
		explicit Vector2(const Vector2<U>& in) : x(static_cast<T>(in.x)), y(static_cast<T>(in.y)) {}

		// Conversion back to SFML Vector2
		template<typename U> requires arithmetic<U>
		operator sf::Vector2<U>() { return sf::Vector2<U>(static_cast<U>(x), static_cast<U>(y)); }

		// Functions
		std::string ToString() { return std::to_string(x) + ", " + std::to_string(y); }
		float GetSqrMagnitude() { return x * x + y * y; }
		float GetMagnitude() { return sqrtf(GetSqrMagnitude()); }
		Vector2<T> Normalise() { *this /= GetMagnitude(); return *this; }
		Vector2<T> Normalised() { return *this / GetMagnitude(); }

		static float Dot(const Vector2<T>& lhs, const Vector2<T>& rhs) { return static_cast<float>(lhs.x * rhs.x + lhs.y * rhs.y); }
		static float Angle(const Vector2<T>& lhs, const Vector2<T>& rhs) { return acos(Dot(lhs.Normalised(), rhs.Normalised())); }

		static Vector2<T> Lerp(Vector2<T> a, Vector2<T> b, float t)
		{
			return a + (b - a) * t;
		}

		// Constants
		static const Vector2 zero;
		static const Vector2 one;
		static const Vector2 left;
		static const Vector2 right;
		static const Vector2 up;
		static const Vector2 down;
	};

	//
	template<typename T> requires arithmetic<T>
	Vector2<T> operator - (const Vector2<T>& rhs) { return Vector2<T>(-rhs.x, -rhs.y); }

	template<typename T> requires arithmetic<T>
	Vector2<T>& operator += (Vector2<T>& lhs, const Vector2<T> rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }

	template<typename T> requires arithmetic<T>
	Vector2<T> operator + (Vector2<T> lhs, const Vector2<T>& rhs) { return lhs += rhs; }

	template<typename T> requires arithmetic<T>
	Vector2<T>& operator -= (Vector2<T>& lhs, const Vector2<T> rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }

	template<typename T> requires arithmetic<T>
	Vector2<T> operator - (Vector2<T> lhs, const Vector2<T>& rhs) { return lhs -= rhs; }

	template<typename T> requires arithmetic<T>
	Vector2<T> operator *= (Vector2<T>& lhs, const Vector2<T> rhs) { lhs.x *= rhs.x; lhs.y * rhs.y; return lhs; }

	template<typename T> requires arithmetic<T>
	Vector2<T> operator * (Vector2<T> lhs, const Vector2<T>& rhs) { return lhs *= rhs; }

	template<typename T, typename U> requires arithmetic<T> and arithmetic<U>
	Vector2<T>& operator *= (Vector2<T>& v, const U a) { v.x *= a; v.y *= a; return v; }

	template<typename T, typename U> requires arithmetic<T> and arithmetic<U>
	Vector2<T> operator * (Vector2<T> v, const U a) { return v *= a; }

	template<typename T, typename U> requires arithmetic<T> and arithmetic<U>
	Vector2<T>& operator /= (Vector2<T>& v, const U a)
	{
		if (v.GetSqrMagnitude() != 0.f)
		{
			v.x /= a;
			v.y /= a;
		}

		return v;
	}

	template<typename T, typename U> requires arithmetic<T> and arithmetic<U>
	Vector2<T> operator / (Vector2<T> v, const U a) { return v /= a; }

	template<typename T, typename U> requires arithmetic<T> and arithmetic<U>
	Vector2<T> operator / (const U a, Vector2<T> v) { return v /= a; }

	template<typename T> requires arithmetic<T>
	bool operator == (Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		Vector2<T> dist = lhs - rhs;
		float num4 = dist.x * dist.x + dist.y * dist.y;
		return num4 < 9.9999999E-11f;
	}

	template<typename T> requires arithmetic<T>
	bool operator != (Vector2<T>& lhs, const Vector2<T>& rhs) { return !(lhs == rhs); }

	template<typename T> requires arithmetic<T>
	const Vector2<T> Vector2<T>::zero(static_cast<T>(0), static_cast<T>(0));

	template<typename T> requires arithmetic<T>
	const Vector2<T> Vector2<T>::one(static_cast<T>(1), static_cast<T>(1));

	template<typename T> requires arithmetic<T>
	const Vector2<T> Vector2<T>::left(static_cast<T>(-1), static_cast<T>(0));

	template<typename T> requires arithmetic<T>
	const Vector2<T> Vector2<T>::right(static_cast<T>(1), static_cast<T>(0));

	template<typename T> requires arithmetic<T>
	const Vector2<T> Vector2<T>::up(static_cast<T>(0), static_cast<T>(-1));

	template<typename T> requires arithmetic<T>
	const Vector2<T> Vector2<T>::down(static_cast<T>(0), static_cast<T>(1));

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2u;
}
