#pragma once
#include <Node.h>
#include <Gizmos.h>

using aie::Gizmos;

class NODE_LIBRARY_API GizmoNode :
	public Node
{
public:
	/**
	*	@brief A type of object from the singleton Gizmos that is drawn as a batch by CameraNode.
	*
	*/
	GizmoNode() = default;

	virtual ~GizmoNode() = default;

protected:
	Vector4<float>		m_origin;			// Object anchor point
	Vector4<float>		m_color;			// RGBA color values (0-1)
};

