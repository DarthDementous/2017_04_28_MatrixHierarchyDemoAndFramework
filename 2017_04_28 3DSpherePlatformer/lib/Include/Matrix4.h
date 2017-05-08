#pragma once

// FYI this would be required if you were creating a dll rather than a lib file
#ifdef LIBRARY_EXPORTS
#define LIBRARY_API   __declspec( dllexport ) 
#else 
#define LIBRARY_API   __declspec(dllimport) 
#endif

#include "Vector4.h"

template <class T>
///Matrix4 = 3D Matrix with translation
class Matrix4
{

public:
	///Constructors
	Matrix4() : m11(1), m12(0), m13(0), m14(0),                                                       //Identity by default
		        m21(0), m22(1), m23(0), m24(0),
		        m31(0), m32(0), m33(1), m34(0),
		        m41(0), m42(0), m43(0), m44(1) {}

	Matrix4(Matrix4 &a_rhs) : m11(a_rhs.m11), m12(a_rhs.m12), m13(a_rhs.m13), m14(a_rhs.m14),    //Copy constructor, copy information from Matrix into the other
		                      m21(a_rhs.m21), m22(a_rhs.m22), m23(a_rhs.m23), m24(a_rhs.m24),
		                      m31(a_rhs.m31), m32(a_rhs.m32), m33(a_rhs.m33), m34(a_rhs.m34),
							  m41(a_rhs.m41), m42(a_rhs.m42), m43(a_rhs.m43), m44(a_rhs.m44) {}
								
	Matrix4(float *a_ptr) : m11(a_ptr[0]), m12(a_ptr[1]), m13(a_ptr[2]), m14(a_ptr[3]),                                   //Construct from list of floats
		                    m21(a_ptr[4]), m22(a_ptr[5]), m23(a_ptr[6]), m24(a_ptr[7]),
		                    m31(a_ptr[8]), m32(a_ptr[9]), m33(a_ptr[10]),m34(a_ptr[11]),
							m41(a_ptr[12]),m42(a_ptr[13]),m43(a_ptr[14]),m44(a_ptr[15]) {}

	Matrix4(T a_m11, T a_m12, T a_m13, T a_m14,
		    T a_m21, T a_m22, T a_m23, T a_m24,
		    T a_m31, T a_m32, T a_m33, T a_m34,
		    T a_m41, T a_m42, T a_m43, T a_m44) : m11(a_m11), m12(a_m12), m13(a_m13), m14(a_m14),
											      m21(a_m21), m22(a_m22), m23(a_m23), m24(a_m24),
											      m31(a_m31), m32(a_m32), m33(a_m33), m34(a_m34),
											      m41(a_m41), m42(a_m42), m43(a_m43), m44(a_m44) {}
	///Variables
	union
	{
		struct {
			T   m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
		};
		struct { T m[16]; };
		struct { T mm[4][4]; };
		struct { Vector4<T> v[4]; };               //Array of vectors (reads each row like a vector, do not use this to modify an axis!)
	};
#pragma region Base Operators
	Matrix4 operator * (const Matrix4 &a_rhs) const {
		/*
		[m11, m12, m13, m14]      *     [a_m11, a_m12, a_m13, a_m14]
		[m21, m22, m23, m24]            [a_m21, a_m22, a_m23, a_m24]
		[m31, m32, m33, m34]			[a_m31, a_m32, a_m33, a_m34]
		[m41, m42, m43, m44]            [a_m41, a_m42, a_m43, a_m44]
		*/
		Matrix4<T> tmp;
		//Do the matrix multiplication process in a for-loop for readability
		for (auto r = 0; r < 4; r++) {
			for (auto c = 0; c < 4; c++) {
				tmp.mm[r][c] = (mm[0][c] * a_rhs.mm[r][0] +                    //For each position, find the value for the equivalent position and it to the new Matrix
					            mm[1][c] * a_rhs.mm[r][1] +
					            mm[2][c] * a_rhs.mm[r][2] +
					            mm[3][c] * a_rhs.mm[r][3]);
			}
		}
		return tmp;
	}

	Vector4<T> operator * (const Vector4<T> &a_rhs) const {                      /*Because we're not in the Vector4 template class, we need to specify what type it is in all uses.
																				 DO NOT #define because it'll inherit everywhere*/
		/*
		[m11, m12, m13, m14]      *     [x,         =   [c_m11]
		[m21, m22, m23, m24]             y,             [c_m21]
		[m31, m32, m33, m34]			 z,	            [c_m31]
		[m41, m42, m43, m44]			 w]             [c_m41]
		*/
		return Vector4<T>
			((m11 * a_rhs.x + m21 * a_rhs.y + m31 * a_rhs.z + m41 * a_rhs.w), //NOTE: When multiplying a matrice with a vector, it has to be treated cxr instead of rxc because the vector is
			 (m12 * a_rhs.x + m22 * a_rhs.y + m32 * a_rhs.z + m42 * a_rhs.w), //technically a row vector, even though we're still getting the rows from the lhs and the columns from the rhs.
			 (m13 * a_rhs.x + m23 * a_rhs.y + m33 * a_rhs.z + m43 * a_rhs.w),
			 (m14 * a_rhs.x + m24 * a_rhs.y + m34 * a_rhs.z + m44 * a_rhs.w));
	}

	Matrix4 operator = (const Matrix4 &a_rhs) {
		m11 = a_rhs.m11, m12 = a_rhs.m12, m13 = a_rhs.m13, m14 = a_rhs.m14;
		m21 = a_rhs.m21, m22 = a_rhs.m22, m23 = a_rhs.m23, m24 = a_rhs.m24;
		m31 = a_rhs.m31, m32 = a_rhs.m32, m33 = a_rhs.m33, m34 = a_rhs.m34;
		m41 = a_rhs.m41, m42 = a_rhs.m42, m43 = a_rhs.m43, m44 = a_rhs.m44;
		return *this;
	}
#pragma endregion
	//Operators that rely on base operators
#pragma region Advanced Operators
	Matrix4& operator *=(const Matrix4 &a_rhs) {
		*this = *this * a_rhs;
		return *this;
	}
#pragma endregion

#pragma region Functions
	///Creators
	static Matrix4 createIdentity() {                                      //Return default matrix
		return Matrix4<T>
			(1, 0, 0, 0,
			 0, 1, 0, 0,
			 0, 0, 1, 0,
			 0, 0, 0, 1);
	}

	static Matrix4 createRotationX(float a_rot) {                          //Return X rotated Matrix4
		Matrix4<T> tmp;
		//Express via indexes for readability, we only change the relevant default values.
		//Do not touch axis or values for what we're rotating with. (X and x in this case)
		tmp.mm[1][1] = cosf(a_rot);    //Yy
		tmp.mm[2][1] = -sinf(a_rot);    //Yz
		tmp.mm[1][2] = sinf(a_rot);   //Zy
		tmp.mm[2][2] = cosf(a_rot);    //Zz
		return tmp;
	}

	static Matrix4 createRotationY(float a_rot) {
		Matrix4<T> tmp;
		tmp.mm[0][0] = cosf(a_rot);   //Xx
		tmp.mm[2][0] = sinf(a_rot);   //Xz
		tmp.mm[0][2] = -sinf(a_rot);  //Zx
		tmp.mm[2][2] = cosf(a_rot);   //Zz
		return tmp;
	}

	static Matrix4 createRotationZ(float a_rot) {                          //Return rotated Matrix4
		Matrix4<T> tmp;
		tmp.mm[0][0] = cosf(a_rot);   //Xx
		tmp.mm[1][0] = -sinf(a_rot);  //Xy
		tmp.mm[0][1] = sinf(a_rot);   //Yx
		tmp.mm[1][1] = cosf(a_rot);   //Yy
		return tmp;
	}

	static Matrix4 createScale(float a_xScale, float a_yScale, float a_zScale) {           //Return scaled Matrix4
		Matrix4<T> tmp;
		tmp.mm[0][0] = a_xScale;          //Xx
		tmp.mm[1][1] = a_yScale;		  //Yy
		tmp.mm[2][2] = a_zScale;	      //Zz
		return tmp;
	}
	///Setters
	void set
		(float a_m11, float a_m12, float a_m13, float a_m14,          // Rebuild the matrix with parameters
		 float a_m21, float a_m22, float a_m23, float a_m24,
		 float a_m31, float a_m32, float a_m33, float a_m34,
		 float a_m41, float a_m42, float a_m43, float a_m44)
	{
		m11 = a_m11, m12 = a_m12, m13 = a_m13, m14 = a_m14;
		m21 = a_m21, m22 = a_m22, m23 = a_m23, m24 = a_m24;
		m31 = a_m31, m32 = a_m32, m33 = a_m33, m34 = a_m34;
		m41 = a_m41, m42 = a_m42, m43 = a_m43, m44 = a_m44;
	}

	void set(float *a_ptr)                                        	// rebuild the matrix - expects pointer to array of 4 floats
	{
		//Assign values with for loop for readability
		auto index = 0;
		for (auto r = 0; i < 4; r++) {
			for (auto c = 0; i < 4; c++) {
				mm[r][c] = a_ptr[index];
				index++;
			}
		}
	}

	void setRotateX(float a_rot) {                   
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

	void setTranslate(float a_transX, float a_transY, float a_transZ)            // Translate matrix by given values (move origin)
	{
		m[0][3] = a_transX; //Wx
		m[1][3] = a_transY; //Wy
		m[2][3] = a_transZ; //Wz
	}
#pragma endregion
	//Casts matrix to float pointer
	explicit operator float* () { return m; }                   //Return start of matrix memory address
	Vector4<T> & operator [] (unsigned int index) { return v[index]; } //Return vector at specified index
};

