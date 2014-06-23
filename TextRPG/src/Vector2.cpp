#ifndef VECTOR2_CPP
#define VECTOR2_CPP

#include <assert.h>
#include <complex>
#include "Vector2.h"
 
template <typename T> Vector2<T>::Vector2(T x, T y) : X(x), Y(y)
{
}

template <typename T> Vector2<T>::Vector2(const Vector2<T>& otherVector)
{
	X = otherVector.X;
	Y = otherVector.Y;
}
 
template <typename T> Vector2<T>::~Vector2(void)
{
}

/**
 * Get length of the vector
 */
template <typename T> 
T Vector2<T>::Length() const
{
	return (T)std::sqrt(X * X + Y * Y);
}

template <typename T> 
T Vector2<T>::DistanceTo(const Vector2<T>& other) const
{
    return (T)std::sqrt((other.X - X) * (other.X - X) + (other.Y - Y) * (other.Y - Y));
}

/**
 * Normalize the vector so that its length become 1
 * If vector is 0 => do nothing
 */
template <typename T> 
void Vector2<T>::Normalize()
{
	T len = Length();

	if (len != 0)
	{
		X = X / len;
		Y = Y / len;
	}
}

//template <typename T> 
//COORD Vector2<T>::ConvertToCoord()
//{
//	COORD coord = { (short)X, (short)Y };
//	return coord;
//}

/**
 * Rotate the vector 
 * @param angle - angle of rotate. Unit: radian
 */
template <typename T> 
Vector2<T> Vector2<T>::Rotate(const double angle)
{
	T x = (T)(X * std::cos(angle) - Y * std::sin(angle));
	T y = (T)(Y * std::cos(angle) + X * std::sin(angle));
	return Vector2(x, y);
}

// Calculate Dot product between this vector with other
template <typename T>
T Vector2<T>::Dot(const Vector2<T>& otherVector) const
{
	T result = X * otherVector.X + Y * otherVector.Y;
	return result;
}

// Find projection vector onto other vector
// REQUIRE otherVec != 0
template <typename T>
Vector2<T> Vector2<T>::ProjectOn(const Vector2<T>& otherVec)
{
	assert((otherVec.X != 0) || (otherVec.Y != 0));

	// project(v, u) = ((v . u) / (u . u)) * u
	Vector2<T> projectVec = otherVec * (this->Dot(otherVec) / otherVec.Dot(otherVec));

	return projectVec;
}

// Get a vector which orthogonal with this vector
template <typename T> 
Vector2<T> Vector2<T>::GetOrthogonal()
{
	Vector2<T> orthoVec = Vector2<T>(-Y, X);
	return orthoVec;
}

// Operator overloading functions
template <typename T> 
Vector2<T>& Vector2<T>::operator = (const Vector2<T>& otherVector)
{
	X = otherVector.X;
	Y = otherVector.Y;

	return *this;
}

template <typename T> 
Vector2<T>& Vector2<T>::operator += (const Vector2<T>& otherVector)
{
	this->X += otherVector.X;
	this->Y += otherVector.Y;

	return *this;
}

template <typename T> 
Vector2<T>& Vector2<T>::operator -= (const Vector2<T>& otherVector)
{
	X -= otherVector.X;
	Y -= otherVector.Y;

	return *this;
}

template <typename T> 
Vector2<T>& Vector2<T>::operator *= (T t)
{
	X *= t;
	Y *= t;

	return *this;
}

template <typename T> 
Vector2<T>& Vector2<T>::operator /= (T t)
{
	assert(t != 0);

	X /= t;
	Y /= t;

	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator - ()
{
	Vector2<T> negVec(-X, -Y);

	return negVec;
}

template <typename T>
bool Vector2<T>::operator == (const Vector2<T>& otherVector)
{
	return ((X == otherVector.X) && (Y == otherVector.Y));
}

template <typename T>
bool Vector2<T>::operator != (const Vector2<T>& otherVector)
{
	return ((X != otherVector.X) || (Y != otherVector.Y));
}


template <typename T>
Vector2<T> operator + (const Vector2<T>& vector1, const Vector2<T>& vector2)
{
	Vector2<T> sum(vector1);
	sum += vector2;

	return sum;
}

template <typename T>
Vector2<T> operator - (const Vector2<T>& vector1, const Vector2<T>& vector2)
{
	Vector2<T> result(vector1);
	result -= vector2;

	return result;
}

template <typename T>
Vector2<T> operator * (const Vector2<T>& vector, T t)
{
	Vector2<T> result(vector);
	result *= t;

	return result;
}

template <typename T> 
Vector2<T> operator * (T t, const Vector2<T>& vector)
{
	Vector2<T> result(vector);
	result *= t;

	return result;
}

template <typename T>
Vector2<T> operator / (const Vector2<T>& vector, T t)
{
	assert(t != 0);

	Vector2<T> result(vector);
	result /= t;

	return result;
}

#endif