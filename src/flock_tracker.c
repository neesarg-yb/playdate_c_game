#include "flock_tracker.h"
#include "game_common.h"

Vec2 CalculateTargetPos( Vec2 center, float radius, float crankAngleDeg )
{
	float theta = crankAngleDeg - 90;	// Crank's 0 degrees is at -90 degrees as per following calculation

	// For a circle of radius r & center c
	// Playdate coordinate system - origin in top left corner
	//
	// c _____________x     
	//  | .                 -----------------
	//  |   . r             | Thus, a point | 
	//  |     .             |   rotates     |
	//  |       .           |  clockwise    |
	//  |        * t        -----------------
	//  y                
	//
	// t(x) = r * cos(a) + c.x;
	// t(y) = r * sin(a) + c.y;
	//
	Vec2 targetPos;

	targetPos.x = center.x + ( radius * CosDegrees( theta ) );
	targetPos.y = center.y + ( radius * SinDegrees( theta ) );

	return MakeVec2( targetPos.x, targetPos.y );
}

FlockTracker MakeFlockTracker( Vec2* flockCenter, float startingRingRadius, float initialCrankAngleDeg )
{
	FlockTracker ft;
	ft.flockCenter = flockCenter;
	ft.ringRadius = startingRingRadius;
	ft.crankAngle = MakeAngleFromDeg( initialCrankAngleDeg );

	return ft;
}

void UpdateFlockTracker( float deltaSeconds, FlockTracker* ft )
{
	PDButtons downButtons;
	g_pd->system->getButtonState( &downButtons, NULL, NULL );

	// Center Position
	float const movementSpeed = 50.0;
	if( downButtons & kButtonDown )
		ft->flockCenter->y += movementSpeed * deltaSeconds;
	if( downButtons & kButtonUp )
		ft->flockCenter->y -= movementSpeed * deltaSeconds;
	if( downButtons & kButtonRight )
		ft->flockCenter->x += movementSpeed * deltaSeconds;
	if( downButtons & kButtonLeft )
		ft->flockCenter->x -= movementSpeed * deltaSeconds;

	// Ring size
	float const ringSizeSpeed = 40.f;
	if( downButtons & kButtonA )
		ft->ringRadius += ringSizeSpeed * deltaSeconds;
	if( downButtons & kButtonB )
		ft->ringRadius -= ringSizeSpeed * deltaSeconds;

	// Crank
	if( !g_pd->system->isCrankDocked() )
	{
		Angle crankAngle = MakeAngleFromDeg( g_pd->system->getCrankAngle() );
		ft->crankAngle = crankAngle;
	}

	ft->targetPos = CalculateTargetPos( *ft->flockCenter, ft->ringRadius, DegreesFromAngle( ft->crankAngle ) );
}

void RenderFlockTracker( FlockTracker* ft )
{
	float rectCenterX = ft->flockCenter->x;
	float rectCenterY = ft->flockCenter->y;
	float radius = ft->ringRadius;
	float diameter = radius * 2.f;
	float platformAngle = DegreesFromAngle( ft->crankAngle );

	// The ring
	g_pd->graphics->drawEllipse( rectCenterX - radius, rectCenterY - radius, diameter, diameter, 3, platformAngle - 5, platformAngle + 5, kColorBlack );
}
