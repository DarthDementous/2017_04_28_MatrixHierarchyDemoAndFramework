#pragma once

#include "Application.h"
#include <Vector4.h>
#include <Vector2.h>
#include <Matrix4.h>
#include <glm/mat4x4.hpp>
#include <cmath>
#include <vector>
#include <memory>

#define PLAYER_SPEED			50.f
#define PLAYER_JUMP				500.f
#define PLAYER_EXTENTS			Vector4<float>(20.f, 20.f, 20.f, 0.f)
#define PLAYER_COLOR			Vector4<float>(0.f, 0.f, 1.f, 1.f)

#define BUILDING_EXTENTS		Vector4<float>(20.f, 100.f, 20.f, 0.f)
#define BUILDING_COLOR			Vector4<float>(1.f, 1.f, 1.f, 1.f)

#define	EPSILON 0.0001f			// What is considered absolute zero to avoid unecessary miniscule calculations
#define	DEFAULT_MASS			10.f		// Global mass
#define	DEFAULT_FORCE			10.f		// Base physical force multiplier
#define DEFAULT_FRICTION		9.8f			// Global friction
#define DEFAULT_GRAVITY			9.8f		// Global gravity
#define DEFAULT_GRAVITY_NORMAL  Vector4<float>(0, -1, 0, 0)
#define	DEFAULT_RESTITUTION		.99f		// Global bounce on unit variables (1.0 = bounce forever with collisions)
#define DEFAULT_GROUND_NORMAL	Vector4<float>(0, 1, 0, 0)

// Forward declare to avoid circular inclusions
class CameraNode;
class BoundingBoxNode;

class _3DTestingGroundsApp : public aie::Application {
public:

	_3DTestingGroundsApp();
	virtual ~_3DTestingGroundsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	void KeyboardInput(float deltaTime);
	void UpdateViewMatrix(float deltaTime);
	void MouseInput(float deltaTime);
	void ApplyGravity(float deltaTime);
	void ApplyFriction(float deltaTime);
	void Collision();
	virtual void draw();

protected:
	///Input
	Vector2<int>									originalMouseState;									/*Place to reset mouse cursor DEFAULT: center of the screen*/
	///Player
	std::shared_ptr<BoundingBoxNode>				m_player;											/*Interactive object*/
	bool											jumped;												/*Has the player jumped?*/
	Vector4<float>									playerVelocity;										/*Where to move the player next frame*/
	///Camera
	std::shared_ptr<CameraNode>						m_camera;											/*Viewport that transforms how things are drawn*/
	float											cameraRotSpeed = 0.3f;								/*How fast to rotate the camera view*/
	Vector4<float>									cameraReference = Vector4<float>(0, 300, 600, 0);    /*Offset position of the camera*/           
	std::unique_ptr<Matrix4<float>>					cameraProjectionMatrix;								/*Lens of the camera*/
	///Miscellaneous objects
	std::vector<std::shared_ptr<BoundingBoxNode>>	buildings;											/*List of bounding boxes that are acting as buildings*/
};