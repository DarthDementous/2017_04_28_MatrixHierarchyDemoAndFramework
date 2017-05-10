#pragma once

class Vector4
{
public:

	Vector4();
	Vector4(float a_x, float a_y, float a_z, float a_w);

	void get(float& a_x, float& a_y, float& a_z, float& a_w) const;
	void set(const float& a_x, const float& a_y, const float& a_z, const float& a_w);

	Vector4 operator + (const Vector4 &a_rhs) const;			// V4 = V4 + V4
	Vector4 operator - (const Vector4 &a_rhs) const;			// V4 = V4 - V4
	Vector4 operator * (const Vector4 &a_rhs) const;			// V4 = V4 * V4
	Vector4 operator / (const Vector4 &a_rhs) const;			// V4 = V4 / V4
	Vector4 operator * (const float    a_rhs) const;			// V4 = V4 * f
	Vector4 operator / (const float    a_rhs) const;			// V4 = V4 / f

	Vector4& operator += (const Vector4 &a_rhs);				// V4 += V4
	Vector4& operator -= (const Vector4 &a_rhs);				// V4 -= V4
	Vector4& operator *= (const Vector4 &a_rhs);				// V4 *= V4
	Vector4& operator /= (const Vector4 &a_rhs);				// V4 /= V4
	Vector4& operator *= (const float    a_rhs);				// V4 *= f
	Vector4& operator /= (const float    a_rhs);				// V4 /= f

	bool operator == (const Vector4 &a_rhs) const;				// V4 == V4
	bool operator != (const Vector4 &a_rhs) const;				// V4 != V4

	Vector4 operator -() const;									// -V4

	explicit operator float* () { return &x; }					// *

	float magnitude() const;
	float dot(const Vector4 &a_rhs) const;						// dot product
	Vector4 cross(const Vector4 &a_rhs) const;					// cross product

	Vector4 &normalise();
	Vector4 getNormalised();

	float x, y, z, w;
};

Vector4 operator * (float a_scalar, const Vector4& a_other);	// V4 = f * V4
