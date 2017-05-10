#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(float a_x, float a_y);
	Vector2(const Vector2& a_other);
	~Vector2() = default;

	Vector2 operator + (const Vector2& a_other) const;						// V2 = V2 + V2 
	Vector2 operator - (const Vector2& a_other) const;						// V2 = V2 - V2 
	Vector2& operator += (const Vector2& a_other);							// V2 += V2 
	Vector2& operator -= (const Vector2& a_other);							// V2 -= V2
	Vector2& operator = (const Vector2& a_other);							// V2 = V2

	Vector2 operator * (float a_scalar) const;								// V2 * f
	friend Vector2 operator * (float a_scalar, const Vector2& a_other);		//  f * V2

	Vector2& operator *= (float a_scalar);									// V2 *= f
	Vector2& operator /= (float a_scalar);

	explicit operator float* () { return &x; }								// *

	float dot(const Vector2& a_other);										// dot product

	float magnitude();
	void normalise();
	Vector2 normal();

	float x;
	float y;
};

Vector2 operator * (float a_scalar, const Vector2& a_other);			//  f * V2

