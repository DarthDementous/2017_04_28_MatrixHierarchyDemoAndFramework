#pragma once

///Vector4 = 3D Vector with translation capabilities
template <class T>
class Vector4
{
public:
	///Constructor
	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(T a_x, T a_y, T a_z, T a_w) : x(a_x), y(a_y), z(a_z), w(a_w) {}     //Translation parameter, float because everything in a Matrix has to be the same
	Vector4(const Vector4& a_rhs) : x(a_rhs.x), y(a_rhs.y), z(a_rhs.z), w(a_rhs.w) {}   //Copy/reference constructor
	~Vector4() = default;
	///Variables
	union
	{
		struct { T x, y, z, w; };   //w = Translation
		struct { T v[4]; };
	};           
#pragma region Base Operators
	Vector4 operator + (const Vector4& a_rhs) const                       // V3 = V3 + V3 
	{
		return Vector4<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w); //Constructing a template class, have to specify the data-type in <T>
	}

	Vector4 operator - (const Vector4& a_rhs) const						// V3 = V3 - V3 
	{
		return Vector4<T>(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w);
	}
	Vector4& operator = (const Vector4& a_rhs)							// V3 = V3
	{
		x = a_rhs.x, y = a_rhs.y, z = a_rhs.z, w = a_rhs.w;
		return *this;                                           //Return de-referenced Vector4 after operations
	}

	template <typename S>       //Scalar
	Vector4 operator * (S a_scalar) const								// V3 * f
	{
		return Vector4<T>(x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);
	}

	template <typename S>
	//If its not a friend, the left hand side will HAVE to be a Vector4 when that's not necessarily always the case.
	friend Vector4 operator * (S a_scalar, const Vector4& a_rhs)		//  f * V3
	{
		return Vector4<T>(a_scalar * a_rhs.x, a_scalar * a_rhs.y, a_scalar * a_rhs.z, a_scalar * a_rhs.w);   /*Return a Vector4 which concatenates the scalar and the
																						 right hand side*/
	}

	Vector4 operator -() const									// -V3
	{
		return Vector4<T>(-x, -y, -z, -w);                          // Return negative version of Vector4
	}
	///Conditions
	bool operator == (const Vector4 &a_rhs) const				// V3 == V3
	{
		if (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z && w == a_rhs.w) {              //Also compare translation points, Point != Vector
			return true;
		}
		return false;
	}
	bool operator != (const Vector4 &a_rhs) const				// V3 != V3
	{
		if (!(*this == a_rhs)) {
			return true;                                        //Yes, the vectors are not equal
		}
		return false;                                           //No, the vectors are equal
	}
#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector4& operator += (const Vector4& a_rhs)							// V3 += V3 
	{
		*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
		return *this;
	}

	Vector4& operator -= (const Vector4& a_rhs)							// V3 -= V3
	{
		*this = *this - a_rhs;
		return *this;
	}

	template <typename S>
	Vector4& operator *= (S a_scalar)									// V3 *= f
	{
		*this = *this * a_scalar;
		return *this;
	}

	template <typename S>
	Vector4& operator /= (S a_scalar)                                   // V3 /= f
	{
		*this = *this / a_scalar;
	}
#pragma endregion

#pragma region Functions
	float dot(const Vector4& a_rhs)										// dot product, checks if vectors cast a shadow
	{
		return ((x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z));
	}

	Vector4 cross(const Vector4& a_rhs) {                               // Returns vector perpendicular to the two vectors
		/*
		x   a_x         x | y z x y | z
		y   a_y         x | y z x y | z
		z   a_z
		*/
		return Vector4<T>((y * a_rhs.z - z * a_rhs.y), (z * a_rhs.x - x * a_rhs.z), (x * a_rhs.y - y * a_rhs.x), w * a_rhs.w);
	}

	float magnitude()                                                  // magnitude, get length of vector
	{
		return float(sqrt14((x * x) + (y * y) + (z * z)));                       //Square root returns a double, typecast to float
	}
	void normalise()                                               // divide by magnitude
	{
		float m = magnitude();                                        //Compute magnitude only once for efficiency
		x /= m, y /= m, z /= m;
	}
	Vector4 getNormal() {
		float m = magnitude();
		return Vector4<T>(x /= m, y /= m, z /= m, w);                       //Return normalized version of lhs
	}
#pragma endregion
	//Casts vector to float
	explicit operator float* () { return &x; }								// * Return start of memory address for Vector4
																			//Access vector via index
	float & operator [] (unsigned int index) { return v[index]; }           //Return specified axis of Vector
};