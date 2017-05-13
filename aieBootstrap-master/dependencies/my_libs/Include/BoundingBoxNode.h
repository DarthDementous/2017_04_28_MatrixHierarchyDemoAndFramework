#pragma once
#include <GizmoNode.h>
#include <3DNodeFramework_Utility.h>

class BoundingBoxNode :
	public GizmoNode
{
public:
	/**
	*	@brief	Oriented Bounding Box comprised of planes (2d bounding boxes) made from min and max points
	*	@param	a_max is the top left point of the 3D box
	*	@param	a_min is the bottom right point of the 3D box
	*	@param	a_color is the RGBA value to draw object with
	*	@param	a_origin is the anchor point of the object (to be used as centre parameter for gizmo)
	*/
	BoundingBoxNode(Vector4<float> a_max, Vector4<float> a_min, Vector4<float> a_color, Vector4<float> a_origin) : m_max(a_max), m_min(a_min) {
		CalculateExtents();
		m_color = a_color;
		m_origin = a_origin;
	}
	
	/**
	*	@brief	Oriented Bounding Box comprised of planes (2d bounding boxes) made from extents (width, height, depth)
	*	@param	a_extents is the dimensions of the OBB
	*/
	BoundingBoxNode(Vector4<float> a_extents, Vector4<float> a_color, Vector4<float> a_origin) : m_extents(a_extents) {
		CalculateMinMax();
		m_color = a_color;
		m_origin = a_origin;
	}

	~BoundingBoxNode();

	void Update();
private:
	/**
	*	@brief	Using the min and max, calculate the width, height and depth
	*/
	void CalculateExtents();

	/**
	*	@brief	Using the extents, calculate the min and max
	*/
	void CalculateMinMax();

	/**
	*	@brief	Calculate and return list of corner points for more advanced collision detection
	*	@DEBUG	Render vertex points
	*/
	std::vector<Vector4<float>> CalculateVertices();

	/**
	*	@brief	Next stage of collision checking, split box into planes and return list of face normals
	*	@DEBUG	Render 2d bounding box outlines
	*/
	std::vector<Vector4<float>> CalculateFacePlanes();

	/**
	*	@brief	Basic collision check with another box.
	*	@param	a_bb is the OBB or AABB that we are checking for possible collision with
	*	@return	ENUM: DISJOINT, CONTAINS, INTERSECTS
	*/
	eContainmentType Collision(BoundingBoxNode a_bb);

	/**
	*	@brief Basic collision check with a point
	*	@param	a_pt is the point we are checking for possible collision with
	*	@return ENUM: DISJOINT, CONTAINS, INTERSECTS
	*/
	eContainmentType Collision(Vector4<float> a_pt);

	/**
	*	@brief	More detailed collision detection, checks each face plane for intersection
	*	@param	a_bb is the OBB or AABB that we are checking more detailed collision with
	*	@return	Direction normal of face we are colliding with
	*	
	*	WARNING: Expensive calculations
	*/
	Vector4<float> AdvancedIntersect(BoundingBoxNode a_bb);

protected:
	Vector4<float>						m_max;			/*Top right point*/
	Vector4<float>						m_min;			/*Bottom left point*/
	Vector4<float>						m_extents;		/*Width, height, depth*/

				
};

