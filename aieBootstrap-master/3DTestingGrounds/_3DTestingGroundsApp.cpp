#include "_3DTestingGroundsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>
#include <CameraNode.h>
#include <BoundingBoxNode.h>
#include <PhysicsHelper.h>
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;
using aie::Input;

_3DTestingGroundsApp::_3DTestingGroundsApp() {

}

_3DTestingGroundsApp::~_3DTestingGroundsApp() {

}

bool _3DTestingGroundsApp::startup() {
	//setBackgroundColour(0.25f, 0.25f, 0.25f);
	setBackgroundColour(1.0f, 0.41f, 0.71f);


	Gizmos::create(1000, 1000, 1000, 1000);

	// create simple camera transforms
	//m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	//cameraViewMatrix.convertFromOpenGL(glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0)));
	//cameraViewMatrix = Matrix4::createLookAt(Vector4(10), Vector4(0), Vector4(0, 1, 0, 0));
	// Set initial mouse state
	aie::Input* input = aie::Input::getInstance();
	
	///Camera
	// Create unique pointer and then put information into it
	cameraProjectionMatrix = std::unique_ptr<Matrix4<float>>(new Matrix4<float>);
	cameraProjectionMatrix->convertFromOpenGL(glm::perspectiveFov(degToRad(45.f), (float)getWindowWidth(), (float)getWindowHeight(), 1.f, 10000.f));

	// Give the camera a perspective lens (frustum to cuboid)
	m_camera = std::unique_ptr<CameraNode>(new CameraNode(cameraRotSpeed, cameraProjectionMatrix.get(), cameraReference));

	///Player
	m_player = std::unique_ptr<BoundingBoxNode>(new BoundingBoxNode(PLAYER_EXTENTS, PLAYER_COLOR, Vector4<float>(0, 0, 0, 0)));
	// Parent it to the camera so it inherits its transformations

#if 0
	///'Buildings'
	for (auto i = 0; i < 10; i++) {
		// Create building and translate it before moving it into the building vector
		std::unique_ptr<BoundingBoxNode> m_bb = std::unique_ptr<BoundingBoxNode>(new BoundingBoxNode(BUILDING_EXTENTS, BUILDING_COLOR, Vector4<float>(0, 0, 0, 0)));
		m_bb->Translate(WORLD, Vector4<float>(100 * i, BUILDING_EXTENTS.y / 2, 0, 0));

		buildings.push_back(std::move(m_bb));

	}

#endif
	///Mouse
	originalMouseState = Vector2<int>((int)getWindowWidth() / 2, (int)getWindowHeight() / 2);
	return true;
}

void _3DTestingGroundsApp::shutdown() {
	Gizmos::destroy();
}

void _3DTestingGroundsApp::update(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();

	Gizmos::clear();
	
	// Hide the mouse cursor
	glfwSetInputMode(getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Center cursor so we base camera rotations off of projected mouse movement instead of actual movement that could leave the window and cause extreme rotations
	glfwSetCursorPos(getWindowPtr(), originalMouseState.x, originalMouseState.y);
#if 1
	// If player has been pushed 'underneath' by velocity then we reset their y coord
	Vector4<float> playerPosition = m_player->GetPosition(WORLD);

	if (playerPosition.y < 0) {
		m_player->SetTranslate(WORLD, Vector4<float>(playerPosition.x, 0, playerPosition.z, 0));
	}


	// Only check keyboard input if there is any to save on calculations
	if (input->getPressedKeys().empty()) {
		KeyboardInput(deltaTime);
	}

	ApplyFriction(deltaTime);

	ApplyGravity(deltaTime);

#ifdef _DEBUG
	//std::cout << "CURRENT VELOCITY: " << playerVelocity.x << " " << playerVelocity.y << " " << playerVelocity.z << std::endl;
	std::cout << "CURRENT SPEED: " << playerVelocity.magnitude() << std::endl;
#endif

	// Update player position with velocity
	m_player->Translate(WORLD, playerVelocity);

	// Calculate collisions after velocity has been applied
	Collision();
#endif
	// Update camera
	m_camera->Update(getWindowPtr(), deltaTime, input, originalMouseState, m_player->GetPosition(WORLD));

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-100 + i * 10, 0, 100),
						vec3(-100 + i * 10, 0, -100),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(100, 0, -100 + i * 10),
						vec3(-100, 0, -100 + i * 10),
						i == 10 ? white : black);
	}
	// add default transform lines for world axis
	Gizmos::addTransform(mat4(1), 25.f);


	///Player
	// Gizmos requires a pointer to the transformation matri
	playerPosition = m_player->GetPosition(WORLD);
	glm::vec4 transformMatrixPtr;
	glm::vec3 center = glm::vec3(playerPosition.x, playerPosition.y, playerPosition.z);
	glm::vec3 extents = glm::vec3(PLAYER_EXTENTS.x, PLAYER_EXTENTS.y, PLAYER_EXTENTS.z);
	glm::vec4 color = glm::vec4(PLAYER_COLOR.x, PLAYER_COLOR.y, PLAYER_COLOR.z, PLAYER_COLOR.w);

	Gizmos::addAABB(center, extents, color, &transformMatrixPtr.convertToOpenGL());
#if 0
	///Buildings
	for (auto building : buildings) {
		glm::vec3 center = glm::vec3(building->GetPosition(WORLD).x, building->GetPosition(WORLD).y, building->GetPosition(WORLD).z);je
		glm::vec3 extents = glm::vec3(BUILDING_EXTENTS.x, BUILDING_EXTENTS.y, BUILDING_EXTENTS.z);
		glm::vec4 color = glm::vec4(BUILDING_COLOR.x, BUILDING_COLOR.y, BUILDING_COLOR.z, BUILDING_COLOR.w);

		Gizmos::addAABB(center, extents, color); //&transformMatrixPtr.convertToOpenGL());
	}


#endif
	// quit if we press escape
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}


void _3DTestingGroundsApp::ApplyFriction(float deltaTime) {
	//Friction only applies on the ground
	if (m_player->GetPosition(WORLD).y == 0)
	{
		playerVelocity = PhysicsHelper::AddFriction(DEFAULT_FRICTION, playerVelocity, deltaTime);
	}
}

void _3DTestingGroundsApp::Collision()
{
	// Update player bounding box with transformations before checking it against other bounding boxes
	m_player->Update();

	for (auto building : buildings) {
		/// Base level collision check
		if (building->Collision(m_player.get()) == INTERSECTS) {
			/// Advanced collision application, return normal we're intersecting with
			playerVelocity = PhysicsHelper::ReflectVelocity(DEFAULT_RESTITUTION, building->AdvancedIntersect(m_player.get()), playerVelocity);
		}
	}
}

void _3DTestingGroundsApp::KeyboardInput(float deltaTime)
{
#if 1
	aie::Input* input = aie::Input::getInstance();

	Vector4<float> playerDirection;														/*Which direction to apply force to the player*/
	Vector4<float> playerPosition = m_player->GetPosition(WORLD);						/*Player position in worldspace. NOTE: Must be updated after every transformation!*/
	Matrix4<float> playerTransform = m_player->GetTransform(LOCAL);						/*Player transform matrix*/
	float push = PLAYER_SPEED;															/*Amount of speed behind the force applied*/

	//Movement speed reduced if in the air
	if (playerPosition.y > 0)
	{
		push /= 10;
	}

#pragma region Movement key input

	//Forwards
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		//Use transformation matrix to find out which way the player is facing
		playerDirection = playerTransform.Forward();

		if (input->isKeyDown(aie::INPUT_KEY_A))
		{
			//Add on left direction for diagonal movement
			playerDirection += playerTransform.Left();
		}
		if (input->isKeyDown(aie::INPUT_KEY_D))
		{
			playerDirection += playerTransform.Right();
		}
	}

	//Back
	else if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		playerDirection = playerTransform.Backward();

		if (input->isKeyDown(aie::INPUT_KEY_A))
		{
			playerDirection += playerTransform.Left();
		}
		if (input->isKeyDown(aie::INPUT_KEY_D))
		{
			playerDirection += playerTransform.Right();
		}
	}

	//Left
	else if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		playerDirection = playerTransform.Left();
	}

	//Right
	else if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		playerDirection = playerTransform.Right();
	}

	//Push the player in the specified direction
	playerVelocity = PhysicsHelper::AddForce(DEFAULT_MASS, push, playerDirection, DEFAULT_FORCE, playerVelocity, deltaTime);
#pragma endregion

#pragma region Jumping key input
	//Player can only jump from the ground
	if (input->isKeyDown(aie::INPUT_KEY_SPACE) && playerPosition.y == 0)
	{
		playerVelocity = PhysicsHelper::AddForce(DEFAULT_MASS, PLAYER_JUMP, DEFAULT_GROUND_NORMAL, DEFAULT_FORCE, playerVelocity, deltaTime);
	}
#pragma endregion

#endif
}

void _3DTestingGroundsApp::ApplyGravity(float deltaTime) {
	Vector4<float> playerPosition = m_player->GetPosition(WORLD);

	//Player is in the air or has just jumped
	if (playerPosition.y > 0)
	{
		jumped = true;								//Flag the jump so restitution isn't applied immediately
		// Constantly simulate gravity by applying force downwards to the player if they are in the air
		playerVelocity = PhysicsHelper::AddForce(DEFAULT_MASS, DEFAULT_GRAVITY, DEFAULT_GRAVITY_NORMAL, DEFAULT_FORCE, playerVelocity, deltaTime);
	}

	//Player has touched down after a jump
	if (playerPosition.y == 0 && jumped == true)
	{
		//Apply bounce
		playerVelocity = PhysicsHelper::ReflectVelocity(DEFAULT_RESTITUTION, DEFAULT_GROUND_NORMAL, playerVelocity);
		jumped = false;								//Jumping procedure has been completed
	}
}

void _3DTestingGroundsApp::MouseInput(float deltaTime)
{
#if 0
	//// Limit pitch to avoid gimbal lock
	//float tempAngle = radToDeg(cameraPitch);   // Convert to degrees for readability
	//if (tempAngle > 89.f) {
	//	tempAngle = 89.f;
	//}
	//else if (tempAngle < -89.0f) {
	//	tempAngle = -89.f;
	//}
	//cameraPitch = degToRad(tempAngle);         // Convert back to radians so its compatable with regular calculations
	// Get current mouse position
	Input* input = Input::getInstance();
	Vector2<int> currentState;
	// Apply current mouse position to Vector2 by casting memory address to int pointer
	input->getMouseXY(&currentState.x, &currentState.y);
	
	// If the mouse has moved 
	if (currentState != originalMouseState) {
		///Calculate how far mouse has moved from the centre in order to turn projected movement into rotation
		float xDifference = currentState.x - originalMouseState.x;
		// Bootstrap y axis starts from bottom
		float yDifference = originalMouseState.y - currentState.y;
		float rotSpeed = cameraRotSpeed * deltaTime;
		
		///Camera rotation values
		cameraYaw -= xDifference * rotSpeed;
		cameraPitch -= yDifference * rotSpeed;
		// Limit pitch to avoid gimbal lock
		float tempAngle = radToDeg(cameraPitch);   // Convert to degrees for readability
		if (tempAngle > 89.f) {
			tempAngle = 89.f;
		} 
		else if (tempAngle < -89.0f) {
			tempAngle = -89.f;
		}
		cameraPitch = degToRad(tempAngle);         // Convert back to radians so its compatable with regular calculations
	}
#endif
}

void _3DTestingGroundsApp::UpdateViewMatrix(float deltaTime)
{
#if 0
	cameraPitch -= cameraRotSpeed * deltaTime;
	cameraYaw -= cameraRotSpeed * deltaTime;
	 Pitch and yaw camera
	cameraRotationMatrix = Matrix4::createRotationX(cameraPitch) * Matrix4::createRotationY(cameraYaw);
	// Transform camera's position relative to its ROTATION
	cameraTransformedPosition = cameraRotationMatrix * cameraReference;
	//// Add the player's POSITION to the camera's position
	//cameraTransformedPosition += playerPosition;
	// Transform camera up normal by camera rotation
	cameraUp = cameraRotationMatrix * Vector4(0, 1, 0, 0);
	// Construct the camera view matrix
	cameraViewMatrix = Matrix4::createLookAt(cameraTransformedPosition, playerPosition, cameraUp);
	cameraProjectionMatrix.convertFromOpenGL(glm::perspectiveFov(degToRad(45.f), (float)getWindowWidth(), (float)getWindowHeight(), 1.f, 1000.f));
#endif
}

void _3DTestingGroundsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// Draw gizmos transformed to the camera
	//m_camera->Render();

	Gizmos::draw(m_camera->GetObjectTransform().convertToOpenGL());			// Draw all Gizmos so they are transformed by the camera's viewport
	// update perspective in case window resized
	//glm::mat4 m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
	//	getWindowWidth() / (float)getWindowHeight(),
	//	0.1f, 1000.f);
	//// create simple camera transforms

	//glm::mat4 m_viewMatrix = glm::lookAt(glm::vec3(cameraReference.x, cameraReference.y, cameraReference.z), vec3(0), vec3(0, 1, 0));
	//Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}