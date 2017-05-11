#include "_3DTestingGroundsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <Vector2.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

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
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	//cameraViewMatrix.convertFromOpenGL(glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0)));
	//cameraViewMatrix = Matrix4::createLookAt(Vector4(10), Vector4(0), Vector4(0, 1, 0, 0));
	// Set initial mouse state
	aie::Input* input = aie::Input::getInstance();

	originalMouseState = Vector2<int>((int)getWindowWidth() / 2, (int)getWindowHeight() / 2);

	// Give the camera a perspective lens (frustum to cuboid)
	//cameraProjectionMatrix = Matrix4::createPerspective(glm::pi<float>() * 0.25f, 16.f / 9.f, 0.1f, 1000.f);
	cameraProjectionMatrix.convertFromOpenGL(glm::perspectiveFov(degToRad(45.f), (float)getWindowWidth(), (float)getWindowHeight(), 1.f, 1000.f));

	return true;
}

void _3DTestingGroundsApp::shutdown() {

	Gizmos::destroy();
}

void _3DTestingGroundsApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}
	// add default transform lines for world axis
	Gizmos::addTransform(mat4(1));

	// Update with mouse input
	MouseInput(deltaTime);

	// Hide the mouse cursor
	glfwSetInputMode(getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Center cursor so we base camera rotations off of projected mouse movement instead of actual movement that could leave the window and cause extreme rotations
	glfwSetCursorPos(getWindowPtr(), originalMouseState.x, originalMouseState.y);

	// Update camera after getting new mouse input
	UpdateViewMatrix(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _3DTestingGroundsApp::MouseInput(float deltaTime)
{
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
}

void _3DTestingGroundsApp::UpdateViewMatrix(float deltaTime)
{
	//cameraPitch -= cameraRotSpeed * deltaTime;
	//cameraYaw -= cameraRotSpeed * deltaTime;
	// Pitch and yaw camera
	cameraRotationMatrix = Matrix4::createRotationX(cameraPitch) * Matrix4::createRotationY(cameraYaw);
	// Transform camera's position relative to its ROTATION
	cameraTransformedPosition = cameraRotationMatrix * cameraReference;
	//// Add the player's POSITION to the camera's position
	//cameraTransformedPosition += playerPosition;
	// Transform camera up normal by camera rotation
	cameraUp = cameraRotationMatrix * Vector4(0, 1, 0, 0);
	// Construct the camera view matrix
	cameraViewMatrix = Matrix4::createLookAt(cameraTransformedPosition, playerPosition, cameraUp);
	//cameraProjectionMatrix.convertFromOpenGL(glm::perspectiveFov(degToRad(45.f), (float)getWindowWidth(), (float)getWindowHeight(), 1.f, 1000.f));
}

void _3DTestingGroundsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// Draw gizmos transformed to the camera
	Gizmos::draw(cameraProjectionMatrix.convertToOpenGL() * cameraViewMatrix.convertToOpenGL());
	//Gizmos::draw(cameraProjectionMatrix.convertToOpenGL() * m_viewMatrix);
}