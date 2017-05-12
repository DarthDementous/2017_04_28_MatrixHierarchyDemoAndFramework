#include "Tank.h"
#include <Texture.h>
#include "SpriteNode.h"
#include "Input.h"

Tank::Tank()
{
	m_tankBaseTexture = new aie::Texture("./sceneGraph/textures/tankBlue.png");
	m_turretTexture = new aie::Texture("./sceneGraph/textures/barrelGreen.png");
	
	m_turret = new SpriteNode(m_turretTexture);
	m_turret->Translate(Vector2<float>(0, 0));
	m_turret->SetOrigin(Vector2<float>(0.0f, 0.5f));

	m_base = new SpriteNode(m_tankBaseTexture);
	m_base->Rotate(3.14159f / 4.0f); // 90 degrees

	m_turret->AttachParent(m_base);
	m_base->AttachParent(this);
}

Tank::~Tank()
{
	delete m_base;
	delete m_turret;

	delete m_turretTexture;
	delete m_tankBaseTexture;
}

void Tank::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
}

void Tank::Render(aie::Renderer2D *renderer)
{
	m_base->Render(renderer);
	m_turret->Render(renderer);
}

void Tank::SetTurretRotate(float p_radians)
{
	float bRads = m_base->GetLocalRotation();
	m_turret->setLocalMatrix(p_radians-bRads);
}

void Tank::SetBaseRotate(float p_radians)
{
	m_base->setLocalMatrix(p_radians);
}

void Tank::SetBaseTranslate(Vector2<float> p_move)
{
	m_base->Translate(p_move);
}

float Tank::GetBaseRotate()
{
	return m_base->GetLocalRotation();
}
