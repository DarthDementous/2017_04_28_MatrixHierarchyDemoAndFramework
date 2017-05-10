#pragma once

class Vector3
{
public:

	Vector3();
	Vector3(float a_x, float a_y, float a_z);

	void get(float& a_x, float& a_y, float& a_z) const;
	void set(const float& a_x, const float& a_y, const float& a_z);

	Vector3 operator + (const Vector3 &a_rhs) const;		// V3 = V3 + V3 
	Vector3 operator - (const Vector3 &a_rhs) const;		// V3 = V3 - V3 
	Vector3 operator * (const Vector3 &a_rhs) const;		// V3 = V3 * V3 
	Vector3 operator / (const Vector3 &a_rhs) const;		// V3 = V3 / V3
	Vector3 operator * (const float    a_rhs) const;		// V3 = V3 * f
	Vector3 operator / (const float    a_rhs) const;		// V3 = V3 / f

	Vector3& operator += (const Vector3 &a_rhs);			// V3 += V3
	Vector3& operator -= (const Vector3 &a_rhs);			// V3 -= V3
	Vector3& operator *= (const Vector3 &a_rhs);			// V3 *= V3
	Vector3& operator /= (const Vector3 &a_rhs);			// V3 /= V3
	Vector3& operator *= (const float    a_rhs);			// V3 *= f
	Vector3& operator /= (const float    a_rhs);			// V3 /= f

	bool operator == (const Vector3 &a_rhs) const;			// V3 == V3
	bool operator != (const Vector3 &a_rhs) const;			// V3 != V3

	Vector3 operator -() const;								// -V3

	explicit operator float* () { return &x; }				// *


	float & operator [] (unsigned int index) { return v[index]; }
	Vector3 operator = (const Vector3 &rhs);

	float magnitude() const;
	float dot(const Vector3 &a_rhs) const;					// dot product
	Vector3 cross(const Vector3 &a_rhs) const;				// cross product

	Vector3 &normalise();
	Vector3 getNormalised();

	union
	{
		struct { float x, y, z; };
		struct { float v[3]; };
	};
};

Vector3 operator * (float a_scalar, const Vector3& a_other);
