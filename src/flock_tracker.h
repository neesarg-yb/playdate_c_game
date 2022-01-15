#pragma once
#include "angle.h"
#include "vector.h"

typedef struct FlockTracker
{
	Vec2* flockCenter;
	float ringRadius;
	Angle targetAngle;

	Vec2  targetPos;	// Re-caclulated by UpdateFlockTracker()

} FlockTracker;

FlockTracker MakeFlockTracker( Vec2* flockCenter, float startingRingRadius, float initialAngleDegrees );

void UpdateFlockTracker( FlockTracker* ft );
void RenderFlockTracker( FlockTracker* ft );
