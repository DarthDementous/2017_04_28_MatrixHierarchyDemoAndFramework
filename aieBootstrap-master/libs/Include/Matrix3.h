#pragma once

// FYI this would be required if you were creating a dll rather than a lib file
#ifdef LIBRARY_EXPORTS
#define LIBRARY_API   __declspec( dllexport ) 
#else 
#define LIBRARY_API   __declspec(dllimport) 
#endif                                                                                                                                  

#include "Vector3.h"
#include "Vector2.h"

class Matrix2;

class Matrix3 {
public:
	Matrix3();
	Matrix3(float *a_ptr);
	Matrix3(float a_m1, float a_m2, float a_m3, float a_m4, float a_m5, float a_m6, float a_m7, float a_m8, float a_m9);

	static Matrix3 createIdentity();
	static Matrix3 createTranslation(float a_x, float a_y, float a_z = 1);
	static Matrix3 createTranslation(const Vector3 &a_vec);
	static Matrix3 createTranslation(const Vector2 &a_vec, float a_z = 1);
	static Matrix3 createRotation(float a_rot);
	static Matrix3 createScale(float a_xScale, float a_yScale);

	explicit operator float* () { return m; }

	// rebuild the matrix
	void set(float a_m1, float a_m2, float a_m3, float a_m4, float a_m5, float a_m6, float a_m7, float a_m8, float a_m9);

	// rebuild the matrix - expects pointer to array of 9 floats
	void set(float *a_ptr);

	Matrix3  operator *(const Matrix3 &a_rhs) const;
	Matrix3 &operator *=(const Matrix3 &a_rhs);

	Matrix3 &operator =(const Matrix3 & a_rhs);
	Vector3 operator * (const Vector3 &a_rhs) const;
	Vector2 operator * (const Vector2 &a_rhs) const;

	// only set the translation component of the matrix
	void setTranslation(float a_x, float a_y);
	// only set the translation component of the matrix
	void setTranslation(const Vector2 &a_vec);

	void setRotateX(float a_rot);
	void setRotateY(float a_rot);
	void setRotateZ(float a_rot);

	//float getRotationZ();

	// add x and y onto the translation component of the matrix
	void translate(float a_x, float a_y);
	// add x and y onto the translation component of the matrix
	void translate(const Vector2 &a_vec);

	// returns the translation component of the matrix
	Vector2 getTranslation() const;

	Vector3 &operator[] (int a_index) {
		return v[a_index];
	} 

	union{
		struct { float m1; float m2; float m3; float m4; float m5; float m6; float m7; float m8; float m9; };
		struct { float m[9]; };
		struct { float m_floats[3][3]; };
		struct { Vector3 v[3]; };
	};
};

