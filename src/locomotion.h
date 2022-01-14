#pragma once
#include "vector.h"

typedef struct Locomotion
{
	Vec2	position;
	Vec2	velocity;

	float	maxSpeed;
	Vec2	destination;

} Locomotion;

void UpdateLocomotion( Locomotion* locMo, float deltaSeconds );
