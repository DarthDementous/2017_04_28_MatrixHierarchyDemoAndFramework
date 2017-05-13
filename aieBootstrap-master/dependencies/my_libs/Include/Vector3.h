#pragma once

#include <DLL.h>
///Vector3 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector3
{
public:
	///Constructor
	Vector3(T a_val);
	Vector3();
	Vector3(T a_x, T a_y, T a_z);
	Vector3(const Vector3& a_rhs); //Copy/reference constructor

								   ///Variables
	union
	{
		struct { T x, y, z; };
		struct { T v[3]; };
	};
#pragma region Base Operators
	Vector3 operator + (const Vector3& a_rhs) const;

	Vector3 operator - (const Vector3& a_rhs) const;

	Vector3& operator = (const Vector3& a_rhs);

	Vector3 operator * (T a_scalar) const;

	Vector3 operator / (T a_scalar) const;

	// Technically not apart of the class, needs separate LIBRARY_API with the function.
	// Definition needs to be with declaration so that each specialisation of class template defines and declares the function
	LIBRARY_API friend Vector3 operator*(T a_scalar, const Vector3& a_rhs) {
		return a_rhs * a_scalar;
	}

	Vector3 operator -() const;
	///Conditions
	bool operator == (const Vector3 &a_rhs) const;

	bool operator != (const Vector3 &a_rhs) const;

#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector3& operator += (const Vector3& a_rhs);

	Vector3& operator -= (const Vector3& a_rhs);

	
	Vector3& operator *= (T a_scalar);

	
	Vector3& operator /= (T a_scalar);
#pragma endregion

#pragma region Functions
	T dot(const Vector3& a_rhs);										// dot product, checks if vectors cast a shadow

	Vector3 cross(const Vector3& a_rhs);                               // Returns vector perpendicular to the two vectors

	T magnitude();                                                  // magnitude, get length of vector

	void normalise();                                               // divide by magnitude

	Vector3 getNormal();
#pragma endregion
	//Casts vector to pointer of type T
	explicit operator T* ();

	T & operator [] (unsigned int index);    //Allows you to treat vector like an array by indexing memory to access variables
};



