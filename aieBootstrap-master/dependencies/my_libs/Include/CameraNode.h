#pragma once
#include <Node.h>
#include <Vector2.h>
#include <GLFW/glfw3.h>
#include <Gizmos.h>
#include <MathLib_Utility.h>

namespace aie {
	class Input;
}

using aie::Gizmos;

class NODE_LIBRARY_API CameraNode :
	public Node
{
public:
	CameraNode() = default;
	~CameraNode();

	/**
	*	@brief Interactive camera viewport.
	*	
	*	@param	a_sensitivity is how fast the camera rotates 
	*	@param	a_projectionMatrix is the Matrix that dictates the camera's perspective
	*	@param	a_reference is the off-set camera position (default = 1st person)
	*/
	CameraNode(float a_sensitivity, const Matrix4<float> *a_projectionMatrix, const Vector4<float> &a_reference = Vector4<float>(0, 0, 0, 0)) : 
		m_sensitivity(a_sensitivity), m_projectionMatrix(*a_projectionMatrix), m_reference(a_reference) {
		// initialise gizmo primitive counts
		//Gizmos::create(10000, 10000, 10000, 10000);
	}

	/**
	*	@brief	Change pitch and yaw based on projected mouse movement.
	*	
	*	@param	a_input is the Bootstrap Input instance
	*	@param	a_originalMouseState is the point the mouse was at last (for best results make this centre of screen)
	*	@param	a_dt is the time between frames to normalize calculations
	*/
	void UpdateInput(aie::Input* a_input, const Vector2<int> &a_originalMouseState, float a_dt);

	/**
	*	@brief	Update the view matrix.
	*
	*	@param	a_target is what to orient the camera to (e.g. position of the player)
	*/
	void UpdateView(const Vector4<float> &a_target);

	/**
	*	@brief	Return the transform matrix required to transform 3D objects to the camera.
	*
	*/
	Matrix4<float> GetObjectTransform();
	
	void Update(GLFWwindow* a_window, float a_dt, aie::Input* a_input, const Vector2<int> &a_originalMouseState, const Vector4<float> &a_target);

	void Render() override;
private:
	float										m_cameraYaw = 0.f;//_PIOVER2;			/* Turning left and right on Y axis*/
	float										m_cameraPitch = 0.f;//-_PI / 10.f;		/* Angling up and down on X axis*/
	float										m_sensitivity;						/* How fast the camera rotates*/
	
	Vector4<float>								m_reference;						/* How much the camera position is offset*/

	Matrix4<float>								m_projectionMatrix;					/* What 'lens' the camera has*/
	Matrix4<float>								m_viewMatrix;						/* Where the camera is and what it's facing at*/
};

