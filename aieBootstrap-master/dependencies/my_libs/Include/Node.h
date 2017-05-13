#pragma once

/**
*  @file    Node.h
*  @author  Sebastian Toy (DarthDementous)
*  @date	12/05/2017
*  @version 1.0
*
*  @brief AIE Math's Demonstration, 3D Matrix Hierarchy framework that allows coupling, de-coupling and local to world coordinates conversions.
*
*  @section DESCRIPTION
*
*  This is a static library that consists of a structure that allows the use of a Matrix Hierarchy in a system.
*  The base class Node provides virtual functions to be overridden by more specialized nodes such as the GizmoNode.
*  The library is designed to work with the Bootstrap and OpenGL architecture.
*  
*  Encapsulation has been upheld in order to ensure each Node is responsible for its own functions, as well as rendering its children
*  which are stored in a vector of Node pointers. 
*  
*  The CameraNode class is designed to simplify and abstract the calculations necessary to create an interactable 3D view so that it is portable
*  enough to be used in any future 3D Bootstrap project. In addition, it serves as the 'grandparent' to all the Nodes because moving the camera
*  means moving everything to create the illusion of moving around the scene.
*
*/

#include <Matrix4.h>
#include <Vector4.h>
#include <Vector3.h>
#include <vector>
#include <3DNodeFramework_Utility.h>
#include <NodeFramework_DLL.h>

/**
*	@brief	Base-class that provides basic functionality for a Matrix Hierarchy system.
*/
class NODE_LIBRARY_API Node
{
public:
	Node();
	virtual ~Node();

#pragma region Virtual functions
	void Update(float a_dt);
	virtual void Render();
#pragma endregion

#pragma region Family functions

	/**
	*	@brief	Couple a single parent to this
	*/
	void AttachParent(Node *a_parent);

	/**
	*	@brief	Couple child node to this.
	*/
	void Adopt(Node *a_child);

	/**
	*	@brief	De-couple the parent node from this.
	*/
	void Orphan();
#pragma endregion

#pragma region Coordinate Functions
	/**
	*	@brief	Get LOCAL or WORLD transformation of this based on the parent.
				WARNING: Expensive calculations and recursion.
	*/
	Matrix4<float> GetTransform(eCoordType a_coordType) const;
	
	/**
	*	@brief	Get LOCAL or WORLD position of this.
	*/
	Vector4<float> GetPosition(eCoordType a_coordType) const;

	/**
	*	@brief	Get LOCAL or WORLD rotation of this.
	*/
	Vector4<float> GetRotation(eCoordType a_coordType);
	
	/**
	*	@brief	Get LOCAL or WORLD scale of this.
	*/
	Vector4<float> GetScale(eCoordType a_coordType) const;

	/**
	*	@brief	Set translation with specified Vector with LOCAL or WORLD consideration.
	*/
	void SetTranslate(eCoordType a_coordType, const Vector4<float> &a_trans);

	/**
	*	@brief	Add translation to this with LOCAL or WORLD consideration.
	*/
	void Translate(eCoordType a_coordType, const Vector4<float> &a_pos);

	/**
	*	@brief	Set rotation with specified Vector with LOCAL or WORLD consideration.
	*/
	void SetRotate(eCoordType a_coordType, const Vector4<float> &a_rot);

	/**
	*	@brief	Add rotation to this with LOCAL or WORLD consideration.
	*/
	void Rotate(eCoordType a_coordType, const Vector4<float> &a_rot);

	/**
	*	@brief	Set scale with specified Vector with LOCAL or WORLD consideration.
	*/
	void SetScale(eCoordType a_coordType, const Vector4<float> &a_scale);
	
	/**
	*	@brief	Add scale to this with LOCAL or WORLD consideration.
	*/
	void Scale(eCoordType a_coordType, Vector3<float> a_scale);

	/**
	*	@brief	Update local transform matrix of this.
	*/
	void SetLocalMatrix(Matrix4<float> &a_localTransform) { m_localTransform = a_localTransform; }
#pragma endregion
protected:
	Matrix4<float>			m_localTransform;	/*Local transformation matrix*/
	std::vector<Node*>		m_children;
	Node*					m_parent = nullptr;
};