#pragma once
#include "locomotion.h"
#include "game_common.h"

void UpdateLocomotion( float deltaSeconds, Locomotion* locMo )
{
	// How do you move to targetPosition?
	// 
	// 1. Get vector to destination
	// 2. Normalize it, to get target direction
	// 3. Get target velocity
	// 4. Get average of current & target velocity and set it to current velocity

	Vec2 const toDestination = SubVec2( locMo->destination, locMo->position );
	Vec2 const targetDir = NormalizeVec2( toDestination );
	Vec2 const targetVel = ScaleVec2( targetDir, locMo->maxSpeed );
	locMo->velocity = ScaleVec2( AddVec2( locMo->velocity, targetVel ), 0.5f );

	// Update the position accordingly
	float const distToTravel = LengthVec2( toDestination );
	float const currentSpeed = LengthVec2( locMo->velocity );
	if( distToTravel > currentSpeed * deltaSeconds )
	{
		locMo->position = AddVec2( locMo->position, ScaleVec2( locMo->velocity, deltaSeconds ) );
	}
	else
	{
		// Just teleport to this last minor distance
		locMo->position = locMo->destination;
		locMo->velocity = MakeVec2( 0.f, 0.f );
	}
}
