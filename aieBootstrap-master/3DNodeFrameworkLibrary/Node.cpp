#include "Node.h"
#include <Renderer2D.h>
#include <glm/gtx/euler_angles.hpp>

Node::Node()
{

}

Node::~Node()
{

}

void Node::Update(float dt)
{

}

void Node::Render(aie::Renderer2D *renderer)
{
	// DEBUG RENDERING
	// TODO: Put condition in to toggle debug rendering for basic nodes
	Matrix4<float> gTransform = GetTransform(WORLD);
	Vector3<float> pos = Vector3<float>(gTransform.getTranslation().x, gTransform.getTranslation().y, gTransform.getTranslation().z);

	//renderer->drawBox(pos.x, pos.y, 10, 20, rot);
}

void Node::Adopt(Node * a_child)
{
	// Child accepts change in relationship
	a_child->AttachParent(this);
	// Parent accepts change in relationship
	m_children.push_back(a_child);
}

Matrix4<float> Node::GetTransform(eCoordType a_coordType) const
{
	// Local if specified or no parent
	if (m_parent == nullptr || a_coordType == LOCAL) {
		return m_localTransform;
	}
	// Calculate world transform based off parent
	// WARNING: Calculations are more expensive the deeper the node is in the hierarchy
	return m_parent->GetTransform(WORLD) * m_localTransform;
}

Vector4<float> Node::GetPosition(eCoordType a_coordType) const
{
	// Local if specified or no parent
	if (m_parent == nullptr || a_coordType == LOCAL) {
		return m_localTransform.getTranslation();
	}
	// Calculate world transform based off parent
	// WARNING: Calculations are more expensive the deeper the node is in the hierarchy
	return (m_parent->GetTransform(WORLD) * m_localTransform).getTranslation();
}

Vector4<float> Node::GetRotation(eCoordType a_coordType)
{
	// Local if specified or no parent
	if (m_parent == nullptr || a_coordType == LOCAL) {
		return m_localTransform.getRotation();
	}
	// Calculate world transform based off parent
	// WARNING: Calculations are more expensive the deeper the node is in the hierarchy
	return (m_parent->GetTransform(WORLD) * m_localTransform).getRotation();
}

Vector4<float> Node::GetScale(eCoordType a_coordType) const
{
	// Local if specified or no parent
	if (m_parent == nullptr || a_coordType == LOCAL) {
		return m_localTransform.getScale();
	}
	// Calculate world transform based off parent
	// WARNING: Calculations are more expensive the deeper the node is in the hierarchy
	return (m_parent->GetTransform(WORLD) * m_localTransform).getScale();
}

void Node::Translate(eCoordType a_coordType, const Vector4<float>& a_pos)
{
	// *= operator so we add on the translation instead of setting it
	m_localTransform *= Matrix4<float>::createTranslation(a_pos.x, a_pos.y, a_pos.z);
	// TODO:
	// Figure out how to globally translate according to parent
	if (a_coordType == WORLD && m_parent != nullptr) {
		m_localTransform *= m_parent->GetTransform(WORLD);
	}
}

void Node::Rotate(eCoordType a_coordType, const Vector4<float>& a_rot)
{
	// *= operator so we add on the rotations instead of setting it
	m_localTransform *= (Matrix4<float>::createRotationX(a_rot.x) * Matrix4<float>::createRotationY(a_rot.y) * Matrix4<float>::createRotationZ(a_rot.z));
	// TODO:
	// Figure out how to globally rotate according to parent
	if (a_coordType == WORLD && m_parent != nullptr) {
		m_localTransform *= m_parent->GetTransform(WORLD);
	}
}

void Node::Scale(eCoordType a_coordType, Vector3<float> a_scale)
{
	// *= operator so we add on to the scale instead of setting it
	m_localTransform *= Matrix4<float>::createScale(a_scale.x, a_scale.y, a_scale.z);
	// TODO:
	// Figure out how to globally scale according to parent
	if (a_coordType == WORLD && m_parent != nullptr) {
		m_localTransform *= m_parent->GetTransform(WORLD);
	}
}