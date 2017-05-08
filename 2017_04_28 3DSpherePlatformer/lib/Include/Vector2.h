#pragma once

#include "Utility.h"
///Vector2 = 2D Vector with no translation capabilities
template <class T>
class Vector2
{
public:
	///Constructor
	Vector2() : x(0), y(0) {}
	Vector2(T a_x, T a_y) : x(a_x), y(a_y) {}              
	Vector2(const Vector2& a_rhs) : x(a_rhs.x), y(a_rhs.y) {}   //Copy/reference constructor
	~Vector2() = default;
	///Variables
	union
	{
		struct { T x, y; };
		struct { T v[2]; };
	};
#pragma region Base Operators
	Vector2 operator + (const Vector2& a_rhs) const                       // V2 = V2 + V2 
	{
		return Vector2<T>(x + a_rhs.x, y + a_rhs.y);             //Constructing a template class, have to specify the data-type in <T>
	}

	Vector2 operator - (const Vector2& a_rhs) const						// V2 = V2 - V2 
	{
		return Vector2<T>(x - a_rhs.x, y - a_rhs.y);
	}
	Vector2& operator = (const Vector2& a_rhs)							// V2 = V2
	{
		x = a_rhs.x, y = a_rhs.y;
		return *this;                                           //Return de-referenced Vector2 after operations
	}

	template <typename S>       //Scalar
	Vector2 operator * (S a_scalar) const								// V2 * f
	{
		return Vector2<T>(x * a_scalar, y * a_scalar);
	}

	template <typename S>
	//If its not a friend, the left hand side will HAVE to be a Vector2 when that's not necessarily always the case.
	friend Vector2 operator * (S a_scalar, const Vector2& a_rhs)		//  f * V2
	{
		return Vector2<T>(a_scalar * a_rhs.x, a_scalar * a_rhs.y);      //Return a Vector2 which concatenates the scalar and the right hand side
	}

	Vector2 operator -() const									// -V2
	{
		return Vector2<T>(-x, -y);                          // Return negative version of vector2
	}
	///Conditions
	bool operator == (const Vector2 &a_rhs) const				// V2 == V2
	{
		if (x == a_rhs.x && y == a_rhs.y) {              //Also compare translation points, Point != Vector
			return true;
		}
		return false;
	}
	bool operator != (const Vector2 &a_rhs) const				// V2 != V2
	{
		if (!(*this == a_rhs)) {
			return true;                                        //Yes, the vectors are not equal
		}
		return false;                                           //No, the vectors are equal
	}

#pragma endregion
//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector2& operator += (const Vector2& a_rhs)							// V2 += V2 
	{
		*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
		return *this;
	}

	Vector2& operator -= (const Vector2& a_rhs)							// V2 -= V2
	{
		*this = *this - a_rhs;
		return *this;
	}

	template <typename S>
	Vector2& operator *= (S a_scalar)									// V2 *= f
	{
		*this = *this * a_scalar;
		return *this;
	}

	template <typename S>
	Vector2& operator /= (S a_scalar)                                   // V2 /= f
	{
		*this = *this / a_scalar;
	}
#pragma endregion

#pragma region Functions
	float dot(const Vector2& a_rhs)										// dot product, checks if vectors cast a shadow
	{
		return ((x * a_rhs.x) + (y * a_rhs.y));
	}

	float magnitude()                                                  // magnitude, get length of vector
	{
		return float(sqrt14((x * x) + (y * y)));                       //Square root returns a double, typecast to float
	}
	void normalise()                                               // divide by magnitude
	{
		float m = magnitude();                                        //Compute magnitude only once for efficiency
		x /= m, y /= m;
	}
	Vector2 getNormal() {
		float m = magnitude();
		return Vector2<T>(x /= m, y /= m);                       //Return normalized version of lhs
	}
#pragma endregion
	//Casts vector to float pointer
	explicit operator float* () { return &x; }								// * Return start of memory address for Vector2
	float & operator [] (unsigned int index) { return v[index]; }           //Return specified axis of Vector
};
