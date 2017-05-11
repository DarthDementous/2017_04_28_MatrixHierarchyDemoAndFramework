#pragma once
#include "Vector3.h"
#include "DLL.h"
template <class T>

///Matrix3 = 3D Matrix with no translation OR 2D Matrix with translation
class LIBRARY_API Matrix3
{
public:
	///Constructors
	Matrix3();

	Matrix3(Matrix3 &a_rhs);                      //Copy constructor, copy information from Matrix into the other

	Matrix3(T *a_ptr);                          //Construct from list of floats

	Matrix3(T a_m11, T a_m12, T a_m13,
		T a_m21, T a_m22, T a_m23,
		T a_m31, T a_m32, T a_m33);
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
	Matrix3 operator * (const Matrix3 &a_rhs) const;

	Vector3<T> operator * (const Vector3<T> &a_rhs) const;           //Because we're not in the Vector3 template class, we need to specify what type it is in all uses.

	Matrix3 operator = (const Matrix3 &a_rhs);
#pragma endregion
	//Operators that rely on base operators
#pragma region Advanced Operators
	Matrix3& operator *=(const Matrix3 &a_rhs);
#pragma endregion

#pragma region Functions
	///Created out of the lhs
	static Matrix3 createIdentity();                                      //Return default matrix

	static Matrix3 createRotationX(float a_rot);

	static Matrix3 createRotationY(float a_rot);

	static Matrix3 createRotationZ(float a_rot);                         //Return rotated Matrix3

	static Matrix3 createScale(T a_xScale, T a_yScale, T a_zScale);           //Return scaled Matrix3
																		  ///Setters
	void set(T a_m11, T a_m12, T a_m13,          // Rebuild the matrix with parameters
		T a_m21, T a_m22, T a_m23,
		T a_m31, T a_m32, T a_m33);   	// rebuild the matrix

	void set(T *a_ptr);                                        	// rebuild the matrix - expects pointer to array of 4 floats

	void setRotateX(float a_rot);

	void setRotateY(float a_rot);

	void setRotateZ(float a_rot);                                 // Rotate Matrix3 on the z axis circle

	void setScale(T a_scaleX, T a_scaleY, T a_scaleZ);                 // Scale matrix by given values

	Vector3<T> getTranslation();

	T getRotation(char a_axis);
#pragma endregion
	//Casts matrix to pointer of type T
	explicit operator T* ();                  //Return start of matrix memory address
	Vector3<T> & operator [] (unsigned int index); //Return axis at specified index
};

