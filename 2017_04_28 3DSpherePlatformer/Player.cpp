#include "Player.h"

Player::~Player()
{
}

eJumpStates Player::getJumpState()
{
	if (position.y == defaultHeight) {
		return STATE_GROUNDED;
	} 
	else if (position.y > defaultHeight) {
		return STATE_INAIR;
	}
	// Only remaining possibility is that player is through the ground
	return STATE_INGROUND;
}
