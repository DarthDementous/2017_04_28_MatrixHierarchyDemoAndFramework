#include "CameraNode.h"
#include <3DNodeFramework_Utility.h>
#include <Input.h>

void CameraNode::UpdateInput(aie::Input * a_input, const Vector2<int> &a_originalMouseState, float a_dt)
{
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
}

void CameraNode::UpdateView(const Vector4<float> &a_target)
{
	// Update rotation
	Rotate(LOCAL, Vector4<float>(m_cameraPitch, m_cameraYaw, 0, 0));

	// Translate by offset
	Translate(LOCAL, m_reference);

	// Determine camera Up normal by transforming
	Vector4<float> cameraUp = m_localTransform * UP_NORMAL;

	// Construct the camera view matrix
	m_viewMatrix = Matrix4<float>::createLookAt(m_localTransform.getTranslation(), a_target, cameraUp);
}

Matrix4<float> CameraNode::GetObjectTransform()
{
	// NOTE: Order is important when transforming matrices, PROJECTION then VIEW.
	return m_projectionMatrix * m_viewMatrix;
}
