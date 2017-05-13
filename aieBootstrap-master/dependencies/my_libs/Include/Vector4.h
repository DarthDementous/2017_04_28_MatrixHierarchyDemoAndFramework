#pragma once

#include <DLL.h>
///Vector4 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector4
{
public:
	///Constructor
	Vector4(T a_val);
	Vector4();
	Vector4(T a_x, T a_y, T a_z, T a_w);
	Vector4(const Vector4& a_rhs); //Copy/reference constructor

								   ///Variables
	union
	{
		struct { T x, y, z, w; };
		struct { T v[4]; };
	};
#pragma region Base Operators
	Vector4 operator + (const Vector4& a_rhs) const;

	Vector4 operator - (const Vector4& a_rhs) const;

	Vector4& operator = (const Vector4& a_rhs);

	Vector4 operator * (T a_scalar) const;

	Vector4 operator / (T a_scalar) const;

	// Technically not apart of the class, needs separate LIBRARY_API with the function.
	// Definition needs to be with declaration so that each specialisation of class template defines and declares the function.
	LIBRARY_API friend Vector4 operator*(T a_scalar, const Vector4& a_rhs) {
		return a_rhs * a_scalar;
	}

	LIBRARY_API friend T dot(const Vector4& a_vecA, const Vector4& a_vecB) {
		return ((a_vecA.x * a_vecB.x) + (a_vecA.y * a_vecB.y) + (a_vecA.z * a_vecB.z));
	}

	LIBRARY_API friend Vector4 cross(const Vector4& a_vecA, const Vector4& a_vecB) {
		return Vector4<T>((a_vecA.y * a_vecB.z - a_vecA.z * a_vecB.y), (a_vecA.z * a_vecB.x - a_vecA.x * a_vecB.z), (a_vecA.x * a_vecB.y - a_vecA.y * a_vecB.x), a_vecA.w * a_vecB.w);
	}

	LIBRARY_API friend Vector4 normal(Vector4& a_vec) {
		T m = a_vec.magnitude();
		return Vector4<T>(a_vec.x /= m, a_vec.y /= m, a_vec.z /= m, a_vec.w);                       //Return normalized version of parameters
	}

	Vector4 operator -() const;
	///Conditions
	bool operator == (const Vector4 &a_rhs) const;

	bool operator != (const Vector4 &a_rhs) const;

#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector4& operator += (const Vector4& a_rhs);

	Vector4& operator -= (const Vector4& a_rhs);

	
	Vector4& operator *= (T a_scalar);

	
	Vector4& operator /= (T a_scalar);
#pragma endregion

#pragma region Functions
	T dot(const Vector4& a_rhs);										// dot product, checks if vectors cast a shadow

	Vector4 cross(const Vector4& a_rhs);                               // Returns vector perpendicular to the two vectors

	T magnitude();                                                  // magnitude, get length of vector

	void normalise();                                               // divide by magnitude

	Vector4 getNormal();
#pragma endregion
	//Casts vector to pointer of type T
	explicit operator T* ();

	T & operator [] (unsigned int index);    //Allows you to treat vector like an array by indexing memory to access variables
};

