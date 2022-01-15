#include "flock_tracker.h"
#include "game_common.h"

Vec2 CalculateTargetPos( Vec2 center, float radius, float initialAngleDegrees )
{
	float theta = initialAngleDegrees;

	// For a circle,
	// x = r * cos(a) + c.x;
	// y = r * sin(a) + c.y;
	Vec2 targetPos;

	targetPos.x = center.x + ( radius * CosDegrees( theta - 90 ) );
	targetPos.y = center.y + ( radius * SinDegrees( theta - 90 ) );

	return MakeVec2( targetPos.x, targetPos.y );
}

FlockTracker MakeFlockTracker( Vec2* flockCenter, float startingRingRadius, float initialAngle )
{
	FlockTracker ft;
	ft.flockCenter = flockCenter;
	ft.ringRadius = startingRingRadius;
	ft.targetAngle = MakeAngleFromDeg( initialAngle );

	ft.targetPos = CalculateTargetPos( *ft.flockCenter, ft.ringRadius, DegreesFromAngle( ft.targetAngle ) );

	return ft;
}

void UpdateFlockTracker( FlockTracker* ft )
{
	if( !g_pd->system->isCrankDocked() )
	{
		Angle crankAngle = MakeAngleFromDeg( g_pd->system->getCrankAngle() );
		ft->targetAngle = crankAngle;
	}

	ft->targetPos = CalculateTargetPos( *ft->flockCenter, ft->ringRadius, DegreesFromAngle( ft->targetAngle ) );
}

void RenderFlockTracker( FlockTracker* ft )
{
	float rectCenterX = ft->flockCenter->x;
	float rectCenterY = ft->flockCenter->y;
	float radius = ft->ringRadius;
	float diameter = radius * 2.f;
	float platformAngle = DegreesFromAngle( ft->targetAngle );

	// The ring
	g_pd->graphics->drawEllipse( rectCenterX - radius, rectCenterY - radius, diameter, diameter, 2, platformAngle - 5, platformAngle + 5, kColorBlack );
}
