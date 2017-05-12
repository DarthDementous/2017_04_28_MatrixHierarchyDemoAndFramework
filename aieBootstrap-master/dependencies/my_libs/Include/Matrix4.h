#pragma once
#include "Vector4.h"
#include "DLL.h"
#include <glm/mat4x4.hpp>
template <class T>

///Matrix4 = 2D Matrix with no translation
class LIBRARY_API Matrix4
{
public:
	///Constructors
	Matrix4();

	Matrix4(const Matrix4 &a_rhs);                      //Copy constructor, copy information from Matrix into the other

	Matrix4(T *a_ptr);                          //Construct from list of floats

	Matrix4(T a_m11, T a_m12, T a_m13, T a_m14,
		T a_m21, T a_m22, T a_m23, T a_m24,
		T a_m31, T a_m32, T a_m33, T a_m34,
		T a_m41, T a_m42, T a_m43, T a_m44);
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
	Matrix4 operator * (const Matrix4 &a_rhs) const;

	Vector4<T> operator * (const Vector4<T> &a_rhs) const;           //Because we're not in the Vector4 template class, we need to specify what type it is in all uses.

	Matrix4 operator = (const Matrix4 &a_rhs);
#pragma endregion
	//Operators that rely on base operators
#pragma region Advanced Operators
	Matrix4& operator *=(const Matrix4 &a_rhs);
#pragma endregion

#pragma region Functions
	///Created out of the lhs
	static Matrix4 createLookAt(const Vector4<T> &a_position, const Vector4<T> &a_target, const Vector4<T> &a_worldUp);  // Transform into camera space and orient camera to look at direction (View Transform Matrix)
	
	static Matrix4 createPerspective(T fovY, T aspect, T zNear, T zFar);  // Field of view, ratio, min cull distance, max cull distance

	static Matrix4 createIdentity();                                      //Return default matrix

	static Matrix4 createRotationX(float a_rot);

	static Matrix4 createRotationY(float a_rot);

	static Matrix4 createRotationZ(float a_rot);                         //Return rotated Matrix4

	static Matrix4 createScale(T a_xScale, T a_yScale, T a_zScale);           //Return scaled Matrix4
	
	static Matrix4 createTranslation(T a_transX, T a_transY, T a_transZ);

	///Setters
	void set(T a_m11, T a_m12, T a_m13, T a_m14,
		T a_m21, T a_m22, T a_m23, T a_m24,
		T a_m31, T a_m32, T a_m33, T a_m34,
		T a_m41, T a_m42, T a_m43, T a_m44);   	// rebuild the matrix

	void set(T *a_ptr);                                        	// rebuild the matrix - expects pointer to array of 4 floats

	void setRotateX(float a_rot);

	void setRotateY(float a_rot);

	void setRotateZ(float a_rot);                                 // Rotate Matrix4 on the z axis circle

	void setScale(T a_scaleX, T a_scaleY, T a_scaleZ);                 // Scale matrix by given values

	void setTranslate(T a_transX, T a_transY, T a_transZ);

	Vector4<T> getTranslation() const;

	Vector4<T> getRotation();

	Vector4<T> getScale() const;

	glm::mat4x4 convertToOpenGL();   // Allow math's library structures to be used in Bootstrap functions

	Matrix4& convertFromOpenGL(glm::mat4x4& a_mat);
#pragma endregion
	//Casts matrix to pointer of type T
	explicit operator T* ();                   //Return start of matrix memory address
	Vector4<T> & operator [] (unsigned int index); //Return axis at specified index
};

