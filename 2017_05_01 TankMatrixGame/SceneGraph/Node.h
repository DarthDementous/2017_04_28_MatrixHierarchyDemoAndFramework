#pragma once

#include "Matrix3.h"
#include "Vector2.h"

namespace aie
{
	class Renderer2D;
}

class Node
{
public:
	Node();
	virtual ~Node();

	virtual void Update(float dt);
	virtual void Render(aie::Renderer2D *renderer);

	void SetParent(Node *parent);

	Matrix3<float>& GetTransform();
	Matrix3<float> CalculateGlobalTransform() const;

	void Translate(const Vector2<float> &pos);
	void Rotate(float radians);

	Vector2<float> GetLocalPosition();
	float GetLocalRotation();
	void setLocalMatrix(float p_radians) { m_local.setRotateZ(p_radians); }

	// WARNING:
	// Expensive -- does a lot of things
	Vector2<float> GetGlobalPosition();
	float GetGlobalRotation();
protected:
	Matrix3<float> m_local; // defaults to identity 
	Node *m_parent = nullptr;
private:
};