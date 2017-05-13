#include "CameraNode.h"
#include <3DNodeFramework_Utility.h>
#include <Input.h>
#include <Gizmos.h>


using aie::Gizmos;

void CameraNode::UpdateInput(aie::Input * a_input, const Vector2<int> &a_originalMouseState, float a_dt)
{
#if 1
	Vector2<int> currentState;

	// Apply current mouse position to Vector2 by casting memory address to int pointer
	a_input->getMouseXY(&currentState.x, &currentState.y);

	// If the mouse has moved from the centre
	if (currentState != a_originalMouseState) {
		float xDifference = currentState.x - a_originalMouseState.x;
		float yDifference = a_originalMouseState.y - currentState.y;	// In Bootstrap Y axis goes from bottom to top
		float rotSpeed = m_sensitivity * a_dt;							// Calculate normalized rotation speed with the time between frames

		// Modify the camera rotation values by the change in movement (Bootstrap = counter-clockwise rotation)
		m_cameraYaw -= xDifference * rotSpeed;
		m_cameraPitch -= yDifference * rotSpeed;
		
		// Limit pitch to avoid gimbal lock
		float tempAngle = radToDeg(m_cameraPitch);   // Convert to degrees for readability
		if (tempAngle > 89.f) {
			tempAngle = 89.f;
		}
		else if (tempAngle < -89.0f) {
			tempAngle = -89.f;
		}
		m_cameraPitch = degToRad(tempAngle);         // Convert back to radians so its compatable with regular calculations
	}
#else
	m_cameraYaw -= m_sensitivity * a_dt;
#endif
}

void CameraNode::UpdateView(const Vector4<float> &a_target)
{
	// Update rotation
	SetRotate(LOCAL, Vector4<float>(m_cameraPitch, m_cameraYaw, 0, 0));

	// Translate by offset
	SetTranslate(LOCAL, m_reference);

	// Determine new position of camera by transforming current translation with its Matrix
	Vector4<float> cameraTransformedPosition = m_localTransform * m_localTransform.getTranslation();

	// Add target position onto camera position
	cameraTransformedPosition += a_target;

	// Determine camera Up normal by transforming
	Vector4<float> cameraUp = m_localTransform * UP_NORMAL;

	// Construct the camera view matrix
	m_viewMatrix = Matrix4<float>::createLookAt(cameraTransformedPosition, a_target, cameraUp);
}

Matrix4<float> CameraNode::GetObjectTransform()
{
	// NOTE: Order is important when transforming matrices, PROJECTION then VIEW.
	return m_projectionMatrix * m_viewMatrix;
}

void CameraNode::Update(GLFWwindow* a_window, float a_dt, aie::Input* a_input, Vector2<int> a_originalMouseState, Vector4<float> a_target)
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// Update with mouse input
	UpdateInput(a_input, a_originalMouseState, a_dt);

	// Hide the mouse cursor
	glfwSetInputMode(a_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Center cursor so we base camera rotations off of projected mouse movement instead of actual movement that could leave the window and cause extreme rotations
	glfwSetCursorPos(a_window, a_originalMouseState.x, a_originalMouseState.y);

	// Update camera view after getting new mouse input and orient to specified target
	UpdateView(a_target);
}

void CameraNode::Render() {
	/* Since Gizmos are a singleton class there's only one instance that's drawn as a batch.
	With this draw function we simulate a Matrix Hierarchy, that is the Gizmos are 'children' of the grandparent class - CameraNode.
	*/
	
	Gizmos::draw(GetObjectTransform().convertToOpenGL());			// Draw all Gizmos so they are transformed by the camera's viewport
}