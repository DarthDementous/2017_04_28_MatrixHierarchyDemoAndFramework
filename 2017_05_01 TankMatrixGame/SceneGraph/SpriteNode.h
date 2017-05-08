#pragma once

#include "Node.h"

namespace aie
{
	class Texture;
	class Renderer2D;
}

class SpriteNode : public Node
{
public:

	SpriteNode();
	SpriteNode(aie::Texture *texture);
	virtual ~SpriteNode();

	virtual void Render(aie::Renderer2D *renderer);

	void SetSize(const Vector2<float>& size);
	const Vector2<float>& GetSize();

	void SetOrigin(const Vector2<float>& origin);
	const Vector2<float>& GetOrigin();

protected:

	aie::Texture *m_texture = nullptr;
	Vector2<float> m_size;
	Vector2<float> m_origin = Vector2<float>(0.5, 0.5);
private:
};
