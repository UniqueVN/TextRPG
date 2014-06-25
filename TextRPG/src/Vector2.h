/******************************************************************************
 Author		: THANG HONG TO
 Project	: Math Library

 Class		: Vector2 - represent a vector in 2 dimension space.
			  Can be used to represent coordinate of point in 2D space.
 ******************************************************************************/
#pragma once

/**
 * Vector2 - represent a vector in 2 dimension space.
			  Can be used to represent coordinate of point in 2D space.
 */
template <typename T>
class Vector2
{
public:
    Vector2(T x = T(), T y = T());
    Vector2(const Vector2<T>& otherVector);
    ~Vector2(void);

    T Length() const;
    T DistanceTo(const Vector2<T>&) const;

    void Normalize();						// Normalize the vector - length of vector will be 1
	
    Vector2<T> Rotate(const double angle);	// Rotate the vector 

    T Dot(const Vector2<T>&) const;			// Calculate Dot product between this vector with other

    Vector2<T> ProjectOn(const Vector2<T>&);// Find projection vector onto other vector

    // Get a vector which orthogonal with this vector
    Vector2<T> GetOrthogonal();
	
    // Operator overloading functions
    Vector2<T>& operator = (const Vector2<T>& otherVector);
    Vector2<T>& operator += (const Vector2<T>& otherVector);
    Vector2<T>& operator -= (const Vector2<T>& otherVector);
    Vector2<T>& operator *= (T t);
    Vector2<T>& operator /= (T t);	// REQUIRE (t != 0)
    Vector2<T>  operator - ();
    bool operator == (const Vector2<T>& otherVector);
    bool operator != (const Vector2<T>& otherVector);

    T X;
    T Y;
};

// Operator overloading functions
template <typename T> Vector2<T> operator + (const Vector2<T>& vector1, const Vector2<T>& vector2);
template <typename T> Vector2<T> operator - (const Vector2<T>& vector1, const Vector2<T>& vector2);
template <typename T> Vector2<T> operator * (const Vector2<T>& vector, T t);
template <typename T> Vector2<T> operator * (T t, const Vector2<T>& vector);
template <typename T> Vector2<T> operator / (const Vector2<T>& vector, T t); // REQUIRE (t != 0)

typedef Vector2<float> vector2f;
typedef Vector2<int> vector2i;

#include "Vector2.cpp"