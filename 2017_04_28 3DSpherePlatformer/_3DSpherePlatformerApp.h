#pragma once

#include <set>

#include "Application.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Player.h"
#include "3DSphere_Utility.h"

class _3DSpherePlatformerApp : public aie::Application {
public:

	_3DSpherePlatformerApp();
	virtual ~_3DSpherePlatformerApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
#pragma region Variables
	
	// Entities
	Player m_player;
	// camera transforms
	Matrix4<float>	m_viewMatrix;
	Matrix4<float>	m_projectionMatrix;
#pragma endregion

};