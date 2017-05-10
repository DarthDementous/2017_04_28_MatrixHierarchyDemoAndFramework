#pragma once

class Vector2;

class Matrix2
{
public:
	Matrix2();
	Matrix2(float *a_ptr);
	Matrix2(float a_m1, float a_m2, float a_m3, float a_m4);

	static Matrix2 createIdentity();
	static Matrix2 createTranslation(float a_x, float a_y);
	static Matrix2 createTranslation(const Vector2 &a_vec);
	static Matrix2 createRotation(float a_rot);
	static Matrix2 createScale(float a_xScale, float a_yScale);

	Matrix2  operator * (const Matrix2 &a_rhs) const;
	//Matrix2& operator *=(const Matrix2 &a_rhs) const;
	Matrix2& operator *=(const Matrix2 &a_rhs);

	Vector2 operator * (const Vector2 &a_rhs) const;

	explicit operator float* () { return m; };

	// rebuild the matrix
	void set(float a_m1, float a_m2, float a_m3, float a_m4);

	// rebuild the matrix - expects pointer to array of 9 floats
	void set(float *a_ptr);

	// only set the translation component of the matrix
	void setTranslation(float a_x, float a_y);
	// only set the translation component of the matrix
	void setTranslation(const Vector2 &a_vec);

	void setRotateZ(float a_rot);

	float getRotationZ();

	// add x and y onto the translation component of the matrix
	void translate(float a_x, float a_y);
	// add x and y onto the translation component of the matrix
	void translate(const Vector2 &a_vec);

	// returns the translation component of the matrix
	Vector2 getTranslation() const;

	union
	{
		struct { float m1, m2, m3, m4; };
		struct { float m[4]; };
		struct { float mm[2][2]; };
	};
};
