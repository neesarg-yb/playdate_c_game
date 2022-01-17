#pragma once
#include "angle.h"
#include "vector.h"

typedef struct FlockTracker
{
	Vec2* flockCenter;
	float ringRadius;
	Angle crankAngle;

	Vec2  targetPos;	// Re-caclulated by UpdateFlockTracker()

} FlockTracker;

FlockTracker MakeFlockTracker( Vec2* flockCenter, float startingRingRadius, float initialCrankAngleDeg );

void UpdateFlockTracker( float deltaSeconds, FlockTracker* ft );
void RenderFlockTracker( FlockTracker* ft );
