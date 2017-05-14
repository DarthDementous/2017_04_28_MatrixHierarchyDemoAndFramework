#pragma once
#include <GizmoNode.h>

class NODE_LIBRARY_API BoundingSphereNode :
	public GizmoNode
{
public:
	BoundingSphereNode(Vector4<float> a_origin, Vector4<float> a_color);
	~BoundingSphereNode();
protected:
	float			m_radius;
	int				m_rows, m_columns;	// Subdivisions, level of detail for sphere

};

