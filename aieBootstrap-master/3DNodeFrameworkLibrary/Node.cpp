#include "Node.h"
#include <glm/gtx/euler_angles.hpp>
#include <iostream>

Node::Node()
{
	std::cout << "hi" << std::endl;
}

Node::~Node()
{

}



#pragma region Virtual functions

void Node::Update(float dt)
{

}

void Node::Render()
{

}
#pragma endregion

#pragma region Family functions

void Node::AttachParent(Node* a_parent)
{
	// Child accepts change in relationship
	m_parent = a_parent;
	// Parent accepts change in relationship
	a_parent->m_children.push_back(this);
}

void Node::Adopt(Node* a_child)
{
	// Child accepts change in relationship
	a_child->AttachParent(this);
	// Parent accepts change in relationship
	m_children.push_back(a_child);
}
void Node::Orphan()
{
	// Parent accepts change in relationship
	auto iter = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);		// Get iterator position of this node so we can remove it from the parent's vector
	m_parent->m_children.erase(iter);
	// Child accepts orphaning
	m_parent = nullptr;
}
#pragma endregion

#pragma region Coordinate Functions

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

void Node::SetTranslate(eCoordType a_coordType, const Vector4<float>& a_trans)
{
	if (a_coordType == LOCAL || m_parent == nullptr) {
		// We want to replace only the translation part of the Matrix.
		m_localTransform.setTranslate(a_trans.x, a_trans.y, a_trans.z);
		return;
	}

	// De-couple with parent by negating the parent transformation
	Vector4<float> worldTranslate = m_parent->GetTransform(WORLD).getTranslation();
	m_localTransform.setTranslate(a_trans.x - worldTranslate.x, a_trans.y - worldTranslate.y, a_trans.z - worldTranslate.z);
}

void Node::Translate(eCoordType a_coordType, const Vector4<float>& a_pos)
{
	if (a_coordType == LOCAL || m_parent == nullptr) {
		// *= operator so we add on the translation instead of setting it
		m_localTransform *= Matrix4<float>::createTranslation(a_pos.x, a_pos.y, a_pos.z);
		return;
	}

	// De-couple with parent by negating the parent transformation
	Vector4<float> worldTranslate = m_parent->GetTransform(WORLD).getTranslation();
	m_localTransform *= Matrix4<float>::createTranslation(a_pos.x - worldTranslate.x, a_pos.y - worldTranslate.y, a_pos.z - worldTranslate.z);
}

void Node::SetRotate(eCoordType a_coordType, const Vector4<float>& a_rot)
{
	if (a_coordType == LOCAL || m_parent == nullptr) {
		// We want to replace only the rotation parts
		m_localTransform.setRotateX(a_rot.x), m_localTransform.setRotateY(a_rot.y), m_localTransform.setRotateZ(a_rot.z);
		return;
	}

	// De-couple with parent by negating the parent transformation
	Vector4<float> worldRotate = m_parent->GetTransform(WORLD).getRotation();
	m_localTransform.setRotateX(a_rot.x - worldRotate.x), m_localTransform.setRotateY(a_rot.y - worldRotate.y), m_localTransform.setRotateZ(a_rot.z - worldRotate.z);
}

void Node::Rotate(eCoordType a_coordType, const Vector4<float>& a_rot)
{
	if (a_coordType == LOCAL || m_parent == nullptr) {
		// *= operator so we add on the translation instead of setting it
		m_localTransform *= 
			Matrix4<float>::createRotationX(a_rot.x) * 
			Matrix4<float>::createRotationY(a_rot.y) * 
			Matrix4<float>::createRotationZ(a_rot.z);
		return;
	}

	// De-couple with parent by negating the parent transformation
	Vector4<float> worldRotate = m_parent->GetTransform(WORLD).getRotation();
	m_localTransform *= 
		Matrix4<float>::createRotationX(a_rot.x - worldRotate.x) * 
		Matrix4<float>::createRotationY(a_rot.y - worldRotate.y) * 
		Matrix4<float>::createRotationZ(a_rot.z - worldRotate.z);
}

void Node::SetScale(eCoordType a_coordType, const Vector4<float>& a_scale)
{
	if (a_coordType == LOCAL || m_parent == nullptr) {
		m_localTransform = Matrix4<float>::createScale(a_scale.x, a_scale.y, a_scale.z);
		return;
	}

	// De-couple with parent by negating the parent transformation
	Vector4<float> worldScale = m_parent->GetTransform(WORLD).getScale();
	m_localTransform.setScale(a_scale.x - worldScale.x, a_scale.y - worldScale.y, a_scale.z - worldScale.z);
}

void Node::Scale(eCoordType a_coordType, Vector3<float> a_scale)
{
	if (a_coordType == LOCAL || m_parent == nullptr) {
		// *= operator so we add on to the scale instead of setting it
		m_localTransform *= Matrix4<float>::createScale(a_scale.x, a_scale.y, a_scale.z);
		return;
	}

	// De-couple with parent by negating the parent transformation
	Vector4<float> worldScale = m_parent->GetTransform(WORLD).getScale();
	m_localTransform *= Matrix4<float>::createScale(a_scale.x - worldScale.x, a_scale.y - worldScale.y, a_scale.z - worldScale.z);
}
#pragma endregion