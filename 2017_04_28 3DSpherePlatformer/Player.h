#pragma once
#include "Vector3.h"
#include "3DSphere_Utility.h"

//template <class T>   // Enable use of template class returns and use in parameters

class Player
{
public:
	template <class T> Player() : position(Vector3<T>{0, 1500, 0}) {}  // Default starting position
	template <class T> Player(Vector3<T> a_position) : position(a_position) {}
	~Player();
#pragma region Variables
#pragma endregion

#pragma region Methods
	// Model getModel()
	// updateModel (Model a_model)
	eJumpStates getJumpState();
	
	template <class T> Vector3<T> getPosition() { return position; }
	template <class T> Vector3<T> getVelocity() { return velocity; }

	template <class T> void updatePosition(Vector3<T> a_position) { position = a_position };
#pragma endregion

private:
	float defaultHeight = DEFAULT_GROUND_HEIGHT;  // What height we consider the player as being on the 'ground'

	Vector3<float> position;
	Vector3<float> velocity;     //How the player will move once position is updated with this

};

