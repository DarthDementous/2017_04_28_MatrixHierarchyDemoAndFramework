#pragma once
#include "Vector3.h"
// Normalized vector directions
#define UP_NORMAL Vector3<float>     {0, 1, 0}
#define DN_NORMAL Vector3<float>     {0, -1, 0}
#define LT_NORMAL Vector3<float>     {-1, 0, 0}
#define RT_NORMAL Vector3<float>     {1, 0, 0}
#define FD_NORMAL Vector3<float>     {0, 0, 1}
#define BK_NORMAL Vector3<float>     {0, 0, -1}

#define DEFAULT_GROUND_HEIGHT 100.f
#define GROUND_NORMAL UP_NORMAL   //What direction the ground is facing

// Physics
#define DEFAULT_MASS = 200.0f				//Global mass
#define DEFAULT_FORCE = 1000.0f				//Base physical force multiplier
#define DEFAULT_FRICTION = 4.0f				//Global friction
#define DEFAULT_PHY_DELTA = (1.0f / 60.0f)	//Physics calculator oriented to 60fps, time between frames
#define DEFAULT_GRAVITY = 9.8f				//Global gravity
#define DEFAULT_RESTITUTION = 0.65f			//Global bounce on unit variables (1.0 = bounce forever with collisions)

enum eJumpStates { STATE_GROUNDED, STATE_INAIR, STATE_INGROUND }; //States that affect movement and physics
enum eCollisionStates { NONE, WALL, FLOOR, BOUNDARY, POWERUP};    //Types of object collisions 
enum ContainmentType { DISJOINT, CONTAIN, INTERSECTION };          //Types of collisions