#include "SpriteNode.h"
#include <Texture.h>
#include <Renderer2D.h>
#include "GizmoNode.h"

SpriteNode::SpriteNode()
{

}

SpriteNode::SpriteNode(aie::Texture *texture)
{
	m_texture = texture;
	m_size.x = (float)m_texture->getWidth();
	m_size.y = (float)m_texture->getHeight();
}

SpriteNode::~SpriteNode()
{

}

void SpriteNode::Render(aie::Renderer2D *renderer)
{
	Matrix3<float> gTransform = ConvertToWorldTransform();

	Vector3<float> pos = gTransform.getTranslation();
	Vector2<float> scale(gTransform[0].magnitude(), gTransform[1].magnitude());
	float rot = gTransform.getRotation('Z');

	renderer->drawSprite(
		m_texture, 
		pos.x, pos.y, 
		scale.x*m_size.x, scale.y*m_size.y, 
		rot, 
		0,
		m_origin.x, m_origin.y
	);
}

void SpriteNode::SetSize(const Vector2<float>& size)
{
	m_size = size;
}

const Vector2<float>& SpriteNode::GetSize()
{
	return m_size;
}

void SpriteNode::SetOrigin(const Vector2<float>& origin)
{
	m_origin = origin;
}
const Vector2<float>& SpriteNode::GetOrigin()
{
	return m_origin;
}

GizmoNode::GizmoNode()
{
}


GizmoNode::~GizmoNode()
{
}
