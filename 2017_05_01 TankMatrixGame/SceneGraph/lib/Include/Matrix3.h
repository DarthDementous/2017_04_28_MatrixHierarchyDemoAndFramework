#pragma once

#include "Vector3.h"
#include "DLL.h"

template <class T>
///Matrix4 = 3D Matrix with translations
LIBRARY_API class Matrix3
{

public:
	///Constructors
	Matrix3() : m11(1), m12(0), m13(0),                                                         //Identity matrix by default
		        m21(0), m22(1), m23(0),
		        m31(0), m32(0), m33(1) {}

	Matrix3(Matrix3 &a_rhs) : m11(a_rhs.m11), m12(a_rhs.m12), m13(a_rhs.m13),                 //Copy constructor, copy information from Matrix into the other
						      m21(a_rhs.m21), m22(a_rhs.m22), m23(a_rhs.m23),
							  m31(a_rhs.m31), m32(a_rhs.m32), m33(a_rhs.m33) {}             

	Matrix3(float *a_ptr) : m11(a_ptr[0]), m12(a_ptr[1]), m13(a_ptr[2]),                                          //Construct from list of floats
		                    m21(a_ptr[3]), m22(a_ptr[4]), m23(a_ptr[5]),
		                    m31(a_ptr[6]), m32(a_ptr[7]), m33(a_ptr[8]) {}

	Matrix3(T a_m11, T a_m12, T a_m13,
		    T a_m21, T a_m22, T a_m23,
		    T a_m31, T a_m32, T a_m33) : m11(a_m11), m12(a_m12), m13(a_m13),
		                                 m21(a_m21), m22(a_m22), m23(a_m23),
		                                 m31(a_m31), m32(a_m32), m33(a_m33) {}
	///Variables
	union
	{
		struct {
		T m11, m12, m13,
		  m21, m22, m23,
		  m31, m32, m33;
		};
		struct { T m[9]; };
		struct { T mm[3][3]; };
		struct { Vector3<T> v[3]; };               //Array of vectors (reads each row like a vector, do not use this to modify an axis!)
	};
#pragma region Base Operators
	Matrix3 operator * (const Matrix3 &a_rhs) const {
		/*
		[m11, m12, m13]      *     [a_m11, a_m12, a_m13]
		[m21, m22, m23]            [a_m21, a_m22, a_m23]
		[m31, m32, m33]			   [a_m31, a_m32, a_m33]
		*/
		Matrix3<T> tmp;
		//Do the matrix multiplication process in a for-loop for readability
		for (auto r = 0; r < 3; r++) {
			for (auto c = 0; c < 3; c++) {
				tmp.mm[r][c] = (mm[0][c] * a_rhs.mm[r][0] +                    //For each position, find the value for the equivalent position and it to the new Matrix
					            mm[1][c] * a_rhs.mm[r][1] +
					            mm[2][c] * a_rhs.mm[r][2]);
			}
		}
		return tmp;
	}

	Vector3<T> operator * (const Vector3<T> &a_rhs) const {                      /*Because we're not in the Vector2 template class, we need to specify what type it is in all uses.
																				 DO NOT #define because it'll inherit everywhere*/
		/*
		[m11, m12, m13]      *     [x,         =   [c_m11]
		[m21, m22, m23]             y,             [c_m21]
		[m31, m32, m33]			    z]			   [c_m31]
		*/
		return Vector3<T>
			((m11 * a_rhs.x + m21 * a_rhs.y + m31 * a_rhs.z), //NOTE: When multiplying a matrice with a vector, it has to be treated cxr instead of rxc because the vector is
			 (m12 * a_rhs.x + m22 * a_rhs.y + m32 * a_rhs.z), //technically a row vector, even though we're still getting the rows from the lhs and the columns from the rhs.
			 (m13 * a_rhs.x + m23 * a_rhs.y + m33 * a_rhs.z));
	}

	Matrix3 operator = (const Matrix3 &a_rhs) {
		m11 = a_rhs.m11, m12 = a_rhs.m12, m13 = a_rhs.m13,
		m21 = a_rhs.m21, m22 = a_rhs.m22, m23 = a_rhs.m23,
		m31 = a_rhs.m31, m32 = a_rhs.m32, m33 = a_rhs.m33;
		return *this;
	}
#pragma endregion
	//Operators that rely on base operators
#pragma region Advanced Operators
	Matrix3& operator *=(const Matrix3 &a_rhs) {
		*this = *this * a_rhs;
		return *this;
	}
#pragma endregion

#pragma region Functions
	///Creators
	static Matrix3 createIdentity() {                                      //Return default matrix
		return Matrix3<T>(1, 0, 0
			              0, 1, 0
			              0, 0, 1);
	}

	static Matrix3 createRotationX(float a_rot) {                          //Return X rotated Matrix3
		Matrix3<T> tmp;
		//Express via indexes for readability, we only change the relevant default values (rows x columns) 
		//Do not touch axis or values for what we're rotating with. (X and x in this case)
		tmp.mm[1][1] = cosf(a_rot);    //Yy
		tmp.mm[2][1] = -sinf(a_rot);    //Yz
		tmp.mm[1][2] = sinf(a_rot);   //Zy
		tmp.mm[2][2] = cosf(a_rot);    //Zz
		return tmp;
	}

	static Matrix3 createRotationY(float a_rot) {
		Matrix3<T> tmp;
		tmp.mm[0][0] = cosf(a_rot);   //Xx
		tmp.mm[2][0] = sinf(a_rot);   //Xz
		tmp.mm[0][2] = -sinf(a_rot);  //Zx
		tmp.mm[2][2] = cosf(a_rot);   //Zz
		return tmp;
	}

	static Matrix3 createRotationZ(float a_rot) {                          
		Matrix3<T> tmp;
		tmp.mm[0][0] = cosf(a_rot);   //Xx
		tmp.mm[1][0] = -sinf(a_rot);  //Xy
		tmp.mm[0][1] = sinf(a_rot);   //Yx
		tmp.mm[1][1] = cosf(a_rot);   //Yy
		return tmp;
	}

	static Matrix3 createScale(float a_xScale, float a_yScale, float a_zScale) {           //Return scaled Matrix2
		Matrix3<T> tmp;
		tmp.mm[0][0] = a_xScale;          //Xx
		tmp.mm[1][1] = a_yScale;		  //Yy
		tmp.mm[2][2] = a_zScale;	      //Zz
		return tmp;
	}
	///Setters
	void set
		(float a_m11, float a_m12, float a_m13,          // Rebuild the matrix with parameters
		 float a_m21, float a_m22, float a_m23,
		 float a_m31, float a_m32, float a_m33)
	{
		m11 = a_m11, m12 = a_m12, m13 = a_m13,
		m21 = a_m21, m22 = a_m22, m23 = a_m23,
		m31 = a_m31, m32 = a_m32, m33 = a_m33;
	}

	void set(float *a_ptr)                                        	// rebuild the matrix - expects pointer to array of 4 floats
	{
		//Assign values with for loop for readability
		auto index = 0;
		for (auto r = 0; i < 3; r++) {
			for (auto c = 0; i < 3; c++) {
				mm[r][c] = a_ptr[index];
				index++;
			}
		}
	}

	void setRotateX(float a_rot) {                          //Rotate Matrix3 around X axis
		//Express via indexes for readability, we only change the relevant values. 
		//Do not touch axis or values for what we're rotating with. (X and x in this case)
		mm[1][1] = cosf(a_rot);    //Yy
		mm[2][1] = -sinf(a_rot);    //Yz
		mm[1][2] = sinf(a_rot);   //Zy
		mm[2][2] = cosf(a_rot);    //Zz
	}

	void setRotateY(float a_rot) {
		mm[0][0] = cosf(a_rot);   //Xx
		mm[2][0] = sinf(a_rot);   //Xz
		mm[0][2] = -sinf(a_rot);  //Zx
		mm[2][2] = cosf(a_rot);   //Zz
	}

	void setRotateZ(float a_rot) {                          
		mm[0][0] = cosf(a_rot);   //Xx
		mm[1][0] = -sinf(a_rot);  //Xy
		mm[0][1] = sinf(a_rot);   //Yx
		mm[1][1] = cosf(a_rot);   //Yy
	}

	void setScale(float a_scaleX, float a_scaleY, float a_scaleZ)                 // Scale matrix by given values
	{
		m[0][0] = a_scaleX; //Xx
		m[1][1] = a_scaleY; //Yy
		m[2][2] = a_scaleZ; //Zz
	}
	/// Getters
	Vector3<T> getTranslation() {
		return Vector3<T>{mm[0][2], mm[1][2], mm[2][2]};         //Matrix3 can double as a 2D Matrix with translation capabilities, return translation axis
	}
	float getRotation(char a_axis) {
		switch (a_axis)
		{
		// ONLY WORKS IF NOT SKEWED (FORMS A RIGHT ANGLED TRIANGLE)
		case 'Z' :                                                     //atan2 = takes 2 arguments
			return -atan2(mm[1][1], [0][1]);                             //Get the angle between the Y global axis and the local Y axis tan(adj/opp = Yy/Yx). Negative = counter-clockwise
		}
	}
#pragma endregion
	//Casts matrix to float pointer
	explicit operator float* () { return m; }                   //Return start of matrix memory address
	Vector3<T> & operator [] (unsigned int index) { return v[index]; } //Return vector at specified index
};

