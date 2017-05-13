#include "PhysicsHelper.h"


protected Vector3 Physics_AddFriction(float friction, Vector3 velocity)
{
	Vector3 newVelocity;
	float currentSpeed; //Current length of the velocity vector
	currentSpeed = (float)Math.Sqrt(
		velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z
	); //Use maths to find length of velocity vector

	float newSpeed;
	float drop; //Decay factor (inertia)
	float scale; //Ratio of change

	if (currentSpeed > 1) {
		drop = currentSpeed * friction * DEFAULT_PHY_DELTA;  //Normalize drop with physics calculator
		newSpeed = currentSpeed - drop;
		scale = newSpeed / currentSpeed; //Rate of how much speed has gone down after drop affects it
		newVelocity = velocity * scale; //Scale down velocity accordingly
	}
	else { newVelocity = Vector3.Zero; } //Don't bother with friction if player speed is very low

	return newVelocity;
}
//Apply force to the player
protected Vector3 Physics_AddForce(float mass, float addForce, Vector3 direction, float force, Vector3 velocity)
{
	Vector3 newVelocity = Vector3.Zero;
	float push;
	//Determine what to add on to the force
	push = (force * (addForce / mass)) * DEFAULT_PHY_DELTA; //addForce = How many units to move from the force, like playerVelocityAdd
															//[COLLISION] The speed the player is sent backwards
	newVelocity = velocity + (direction * push); //Final new velocity taking into account the direction and how much to move forwards (push)

	return newVelocity;
}
//Push player back after a collision
protected Vector3 Physics_ReflectVelocity(float reflect, Vector3 planeNormal, Vector3 velocity)
{
	Vector3 newVelocity = Vector3.Zero;
	double clip; //Stores dot-product between velocity and planeNormal vector
	clip = -(1.0 + reflect) * Vector3.Dot(velocity, planeNormal); //Finds the cosine of the angle between the two vectors
																  //reflect = amount of bounce after collision
																  /// Rev: Clip is how much velocity is being reflected back, based on the plane's normal
																  /// so a value of 1.0, would 'stop' an object going in that direction, and a value greater than 1.0
																  /// would 'bounce' it:
																  ///Ex 1: ( 100 - (1.0 * 100) = 100 - 100 = 0, stopped ).
																  ///Ex 2: (100 - (1.65 * 100 ) = 100 - 165 = -65, bounced away with a new velocity of -65)
																  /// the - infront of (1.0 + reflect) is what does the subtraction for us ahead of time.
																  /// reflect will cause the bounce by adding to the 1.0 clip modifier.
																  /// Reflect of 0.65 = -(1.0 + 0.65) = -(1.65), see Ex 2.
																  /// Don't input negative reflect values...
	newVelocity = velocity + (planeNormal * (float)clip); //Determine the new velocity after going against a clipping plane
														  //Clip only returns float value, * planeNormal turns it into new vector
														  //planeNormal = direction being pushed from

														  //Zero out the y axis to avoid small bounces if velocity is 10% of defaultHeight
	if (newVelocity.Y < 1.1f)
	{
		newVelocity.Y = 0.0f;
	}
	return newVelocity;
}