#include "BoundingSphereNode.h"

BoundingSphereNode::BoundingSphereNode(Vector4<float> a_origin, Vector4<float> a_color)
{
	m_origin = a_origin;
	m_color = a_color;
}

BoundingSphereNode::~BoundingSphereNode()
{
}
