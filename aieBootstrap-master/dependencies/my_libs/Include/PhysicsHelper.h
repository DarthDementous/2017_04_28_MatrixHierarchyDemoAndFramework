#include <Vector4.h>
#include <PhysicsHelper_DLL.h>

class PHYSICS_LIBRARY_API PhysicsHelper
{
public:
	/*
	*	@brief	Pure virtual/abstract class that holds functions used for calculating physics
	*/
	virtual ~PhysicsHelper() = 0;

	/*
	*	@brief	Add friction and decay a given Vector4
	*	@param	friction is how viscous a surface is
	*	@param	velocity is the given velocity that will be transformed by AddFriction
	*	@param	deltaTime is the time between frames used to normalize physics calculations
	*
	*	@return	Velocity with friction decaying it
	*/	
	static Vector4<float> AddFriction(float friction, Vector4<float> velocity, float deltaTime);

	/*
	*	@brief	Add force to a given Vector4
	*	@param	mass is the weight of the object to be taken into account when calculating force
	*	@param	addForce is how many units to move from the given force (modifier)
	*	@param	direction is what direction to apply force to
	*	@param	force is the default base value of the power of the push
	*	@param	velocity is the given velocity that will be transformed by AddForce
	*	@param	deltaTime is the time between frames used to normalize physics calculations
	*
	*	@return Velocity with force applied to it in the specified direction
	*/
	static Vector4<float> AddForce(float mass, float addForce, Vector4<float> direction, float force, Vector4<float> velocity, float deltaTime);

	/*
	*	@brief	Reflect the given velocity in accordance to a given direction to simulate being 'bounced' by something
	*	@param	reflect is the base value of how far to push back
	*	@param	planeNormal is the direction the velocity is being pushed back in after a collision
	*	@param	velocity is the given velocity that will be transformed by ReflectVelocity
	*
	*	@return	Velocity that has been reflected in a specified direction
	*/
	static Vector4<float> ReflectVelocity(float reflect, Vector4<float> planeNormal, Vector4<float> velocity);
};