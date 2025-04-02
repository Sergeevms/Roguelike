#pragma once

namespace Roguelike
{
	template<typename T>
	struct Vector2D
	{
		T x = T(0);
		T y = T(0);

		Vector2D& operator+= (const Vector2D& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Vector2D& operator-= (const Vector2D& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		Vector2D& operator*= (const T& scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}
	};

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Position = Vector2Df;

	template<typename T>
	Vector2D<T> operator+(Vector2D<T> left, const Vector2D<T>& right)
	{
		return left += right;
	}

	template<typename T>
	Vector2D<T> operator-(Vector2D<T> left, const Vector2D<T>& right)
	{
		return left -= right;
	}

	template<typename T>
	Vector2D<T> operator==(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return left.x == right.x && left.y == right.y;
	}

	template<typename T>
	float GetVectorLength(const Vector2D<T>& vector)
	{
		return sqrtf(vector.x * vector.x + vector.y * vector.y);
	}

	template<typename U, typename V>
	U Convert(const V& v)
	{
		return { static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y) };
	}
}