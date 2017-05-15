#include <PhysicsHelper.h>
#include <MathLib_Utility.h>

#define	EPSILON 0.0001f			// What is considered absolute zero to avoid unecessary miniscule calculations

PhysicsHelper::~PhysicsHelper() {}

//Decay the player's velocity to simulate friction
Vector4<float> PhysicsHelper::AddFriction(float friction, Vector4<float> velocity, float deltaTime)
{
	Vector4<float> newVelocity;
	float currentSpeed = velocity.magnitude();		 //Current length of the velocity vector

	float newSpeed;
	float drop;										 //Decay factor (inertia)
	float scale;									 //Ratio of change
	
	// If speed is insignificant negate it completely to avoid unecessary calculations
	if (currentSpeed > EPSILON) {
		drop = currentSpeed * friction * deltaTime;  //Normalize drop with physics calculator
		newSpeed = currentSpeed - drop;
		scale = newSpeed / currentSpeed;			 //Rate of how much speed has gone down after drop affects it
		newVelocity = velocity * scale;				 //Scale down velocity accordingly
	}

	// Return modified velocity or negated velocity
	return newVelocity;
}

//Apply force to the player
Vector4<float> PhysicsHelper::AddForce(float mass, float addForce, Vector4<float> direction, float force, Vector4<float> velocity, float deltaTime)
{
	Vector4<float> newVelocity;
	float push;

	//Determine what to add on to the force
	push = (force * (addForce / mass)) * deltaTime; //addForce = How many units to move from the force, like a modifier
		
	newVelocity = velocity + (direction * push);	//Final new velocity taking into account the direction and how much to move forwards (push)

	return newVelocity;
}

//Push player back after a collision
Vector4<float> PhysicsHelper::ReflectVelocity(float reflect, Vector4<float> planeNormal, Vector4<float> velocity)
{
	Vector4<float> newVelocity;
	double clip;										  //Stores dot-product between velocity and planeNormal vector
	clip = -(1.0 + reflect) * dot(velocity, planeNormal); //Finds the cosine of the angle between the two vectors
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

	//Zero out the y axis to avoid small bounces
	if (newVelocity.y < 1)
	{
		newVelocity.y = 0.0f;
	}

	return newVelocity;

}