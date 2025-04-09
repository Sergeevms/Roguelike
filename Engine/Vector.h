#pragma once

namespace MaxrEngine
{
	template<typename T>
	struct Vector2D
	{
		T x;
		T y;

		Vector2D() : x(T(0)), y(T(0)) {};
		Vector2D(T x, T y) : x(x), y(y) {};

		Vector2D& operator-()
		{
			x *= -1;
			y *= -1;
			return *this;
		}
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
		//Hadamard product
		Vector2D& operator*= (const Vector2D& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		T DotProduct(const Vector2D& other)
		{
			return x * other.x + y * other.y;
		}
		float GetLength()
		{
			return sqrtf(x * x + y * y);
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
	bool operator==(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}

	template<typename T>
	bool operator!=(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return !(left == right);
	}	

	template<typename T>
	T DotProduct(Vector2D<T> left, const Vector2D<T>& right)
	{
		return left.DotProduct(right);
	}

	//Hadamard product
	template<typename T>
	Vector2D<T> operator*(Vector2D<T> left, const Vector2D<T>& rigth)
	{
		return left *= rigth;
	}

	template<typename T>
	Vector2D<T> operator*(Vector2D<T> left, const T scalar)
	{
		return left *= scalar;
	}

	template<typename T>
	Vector2D<T> operator*(const T scalar, Vector2D<T> rigth)
	{
		return rigth *= scalar;
	}

	template<typename U, typename V>
	U Convert(const V& v)
	{
		return { static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y) };
	}
}