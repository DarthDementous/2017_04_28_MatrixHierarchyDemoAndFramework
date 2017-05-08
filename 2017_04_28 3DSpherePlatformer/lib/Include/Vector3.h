#pragma once
///Vector3 = 3D Vector with no translation capabilities
template <class T>
class Vector3
{
public:
	///Constructor
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T a_x, T a_y, T a_z) : x(a_x), y(a_y), z(a_z) {}
	Vector3(const Vector3& a_rhs) : x(a_rhs.x), y(a_rhs.y), z(a_rhs.z) {}   //Copy/reference constructor
	~Vector3() = default;
	///Variables
	union
	{
		struct { T x, y, z; };
		struct { T v[3]; };
	};
#pragma region Base Operators
	Vector3 operator + (const Vector3& a_rhs) const                       // V3 = V3 + V3 
	{
		return Vector3<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z);             //Constructing a template class, have to specify the data-type in <T>
	}

	Vector3 operator - (const Vector3& a_rhs) const						// V3 = V3 - V3 
	{
		return Vector3<T>(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z);
	}
	Vector3& operator = (const Vector3& a_rhs)							// V3 = V3
	{
		x = a_rhs.x, y = a_rhs.y, z = a_rhs.z;
		return *this;                                           //Return de-referenced Vector3 after operations
	}

	template <typename S>       //Scalar
	Vector3 operator * (S a_scalar) const								// V3 * f
	{
		return Vector3<T>(x * a_scalar, y * a_scalar, z * a_scalar);
	}

	template <typename S>
	//If its not a friend, the left hand side will HAVE to be a Vector3 when that's not necessarily always the case.
	friend Vector3 operator * (S a_scalar, const Vector3& a_rhs)		//  f * V3
	{
		return Vector3<T>(a_scalar * a_rhs.x, a_scalar * a_rhs.y, a_scalar * a_rhs.z);   /*Return a Vector3 which concatenates the scalar and the
																						 right hand side*/
	}

	Vector3 operator -() const									// -V3
	{
		return Vector3<T>(-x, -y, -z);                          // Return negative version of vector3
	}
	///Conditions
	bool operator == (const Vector3 &a_rhs) const				// V3 == V3
	{
		if (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z) {              //Also compare translation points, Point != Vector
			return true;
		}
		return false;
	}
	bool operator != (const Vector3 &a_rhs) const				// V3 != V3
	{
		if (!(*this == a_rhs)) {
			return true;                                        //Yes, the vectors are not equal
		}
		return false;                                           //No, the vectors are equal
	}
#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector3& operator += (const Vector3& a_rhs)							// V3 += V3 
	{
		*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
		return *this;
	}

	Vector3& operator -= (const Vector3& a_rhs)							// V3 -= V3
	{
		*this = *this - a_rhs;
		return *this;
	}

	template <typename S>
	Vector3& operator *= (S a_scalar)									// V3 *= f
	{
		*this = *this * a_scalar;
		return *this;
	}

	template <typename S>
	Vector3& operator /= (S a_scalar)                                   // V3 /= f
	{
		*this = *this / a_scalar;
	}
#pragma endregion

#pragma region Functions
	float dot(const Vector3& a_rhs)										// dot product, checks if vectors cast a shadow
	{
		return ((x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z));
	}

	Vector3 cross(const Vector3& a_rhs) {                               // Returns vector perpendicular to the two vectors
		/*
		x   a_x         x | y z x y | z
		y   a_y         x | y z x y | z
		z   a_z
		*/
		return Vector3<T>((y * a_rhs.z - z * a_rhs.y), (z * a_rhs.x - x * a_rhs.z), (x * a_rhs.y - y * a_rhs.x));
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
	Vector3 getNormal() {
		float m = magnitude();
		return Vector3<T>(x /= m, y /= m, z /= m);                       //Return normalized version of lhs
	}
#pragma endregion
	//Casts vector to float
	explicit operator float* () { return &x; }								// * Return start of memory address for Vector3
	//Access vector via index
	float & operator [] (unsigned int index) { return v[index]; }           //Return specified axis of Vector
};
