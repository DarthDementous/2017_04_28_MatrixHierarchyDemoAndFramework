#pragma once

#include <MathLib_Utility.h>
#include <DLL.h>
///Vector2 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector2
{
public:
	///Constructor
	Vector2(T a_val);
	Vector2();
	Vector2(T a_x, T a_y);
	Vector2(const Vector2& a_rhs); //Copy/reference constructor

	///Variables
	union
	{
		struct { T x, y; };
		struct { T v[2]; };
	};
#pragma region Base Operators
	Vector2 operator + (const Vector2& a_rhs) const;

	Vector2 operator - (const Vector2& a_rhs) const;

	Vector2& operator = (const Vector2& a_rhs);

	Vector2 operator * (T a_scalar) const;

	Vector2 operator / (T a_scalar) const;

	// Technically not apart of the class, needs separate LIBRARY_API with the function.
	// Definition needs to be with declaration so that each specialisation of class template defines and declares the function
	LIBRARY_API friend Vector2 operator*(T a_scalar, const Vector2& a_rhs) {
		return a_rhs * a_scalar;
	}

	Vector2 operator -() const;

	///Conditions
	bool operator == (const Vector2 &a_rhs) const;

	bool operator != (const Vector2 &a_rhs) const;

#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector2& operator += (const Vector2& a_rhs);

	Vector2& operator -= (const Vector2& a_rhs);

	Vector2& operator *= (T a_scalar);

	Vector2& operator /= (T a_scalar);
#pragma endregion

#pragma region Functions
	T dot(const Vector2& a_rhs);

	T magnitude();

	void normalise();

	Vector2 getNormal();
#pragma endregion
	//Casts vector to pointer of type T
	explicit operator T* ();

	T & operator [] (unsigned int index);    //Allows you to treat vector like an array by indexing memory to access variables
};