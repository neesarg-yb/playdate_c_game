#pragma once
#define _USE_MATH_DEFINES

#include "angle.h"
#include <math.h>
#include "game_common.h"

Angle MakeAngleFromDeg(float const angleDeg)
{
    return MakeAngleFromRad( RadiansFromDegree(angleDeg) );
}

Angle MakeAngleFromRad(float const angleRad)
{
    Angle a;
    a.r = cosf(angleRad);
    a.i = sinf(angleRad);

    return a;
}

float DegreesFromAngle(Angle const angle)
{
    return DegreesFromRadians( RadiansFromAngle(angle) );
}

float RadiansFromAngle(Angle const angle)
{
    return atan2f(angle.i, angle.r);
}

Angle AddAngles(Angle const a, Angle const b)
{
    // Complex num multiplication adds two angles
    float const multReal = ((a.r * b.r) - (a.i * b.i));
    float const multImg  = ((a.r * b.i) + (a.i * b.r));

    Angle sum;
    sum.r = multReal;
    sum.i = multImg;

    return sum;
}

Angle AddDegreesToAngle(Angle const in, float const deltaDeg)
{
    Angle const deltaAngle = MakeAngleFromDeg(deltaDeg);
    return AddAngles(in, deltaAngle);
}

Angle DeltaAngle(Angle const a/*from*/, Angle const b/*to*/)
{
    float numeratorR  = ((a.r * b.r) + (a.i * b.i));
    float numeratorI  = ((a.i * b.r) - (a.r * b.i));
    float denominator = ((b.r * b.r) + (b.i * b.i));

    if(denominator == 0.f)
        g_pd->system->error("Error in class Angle: Divide by ZERO!");

    Angle sub;
    sub.r = numeratorR/denominator;
    sub.i = numeratorI/denominator;

    return sub;
}

bool IsGreaterThanAngle(Angle const lhs, Angle const rhs)
{
    Angle const delta = DeltaAngle(lhs, rhs);
    float const deltaDeg = DegreesFromAngle(delta);

    return deltaDeg > 0.f;
}

bool IsLessThanAngle(Angle const lhs, Angle const rhs)
{
    Angle const delta = DeltaAngle(lhs, rhs);
    float const deltaDeg = DegreesFromAngle(delta);

    return deltaDeg < 0.f;
}

bool IsGreaterEqualThanAngle(Angle const lhs, Angle const rhs)
{
    Angle const delta = DeltaAngle(lhs, rhs);
    float const deltaDeg = DegreesFromAngle(delta);

    return deltaDeg >= 0.f;
}

bool IsLessEqualThanAngle(Angle const lhs, Angle const rhs)
{
    Angle const delta = DeltaAngle(lhs, rhs);
    float const deltaDeg = DegreesFromAngle(delta);

    return deltaDeg <= 0.f;
}

float CosDegrees(float const aDeg)
{
    return cosf( RadiansFromDegree(aDeg) );
}

float SinDegrees(float const aDeg)
{
    return sinf( RadiansFromDegree(aDeg) );
}

float RadiansFromDegree(float const angle)
{
    return ( float ) (angle * M_PI / 180.f);
}

float DegreesFromRadians(float const angle)
{
    return ( float ) (angle * 180.f / M_PI);
}
