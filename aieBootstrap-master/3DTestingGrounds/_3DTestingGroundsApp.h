#pragma once

#include "Application.h"
#include <Vector4.h>
#include <Vector2.h>
#include <Matrix4.h>
#include <glm/mat4x4.hpp>
#include <cmath>
#include <CameraNode.h>

class _3DTestingGroundsApp : public aie::Application {
public:

	_3DTestingGroundsApp();
	virtual ~_3DTestingGroundsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	void MouseInput(float deltaTime);
	void UpdateViewMatrix(float deltaTime);                     // Update camera based off the player's movement in the frame
	virtual void draw();

protected:
	///Input
	Vector2<int>     originalMouseState;
	///Player
	Vector4<float>		playerPosition = Vector4<float>(0);
	Vector4<float>		playerVelocity;
	Vector4<float>		playerRestitutionVelocity;
	///Camera
	CameraNode*			m_camera = nullptr;
	Vector4<float>		cameraUp;
	Vector4<float>		cameraTransformedPosition;        // Coords of camera object (position and rotation)
	Vector4<float>		cameraReference = Vector4<float>(0, 20, -20, 0);                  // Offset position of the camera

	const float cameraRotSpeed = 0.3f;
	const float cameraMoveSpeed = 30.0f;
	float cameraYaw = 0.f;					  // Turning to face left or right
	float cameraPitch = 0.f;             // Angling down or up
	
	Matrix4<float>	cameraProjectionMatrix, cameraViewMatrix, cameraRotationMatrix;  // Stores camera projection, positioning and rotation

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};