#pragma once
#include <stdbool.h>

typedef struct Angle
{
    // Normalized Complex number, which represents an angle
    float r;
    float i;
} Angle;

Angle   MakeAngleFromDeg(float const angleDeg);
Angle   MakeAngleFromRad(float const angleRad);
Angle   AddAngles(Angle const a, Angle const b);
Angle   AddDegreesToAngle(Angle const in, float const deltaDeg);
Angle   DeltaAngle(Angle const from, Angle const to);

bool    IsGreaterThanAngle(Angle const lhs, Angle const rhs);
bool    IsLessThanAngle(Angle const lhs, Angle const rhs);
bool    IsGreaterEqualThanAngle(Angle const lhs, Angle const rhs);
bool    IsLessEqualThanAngle(Angle const lhs, Angle const rhs);

float   CosDegrees(float const aDeg);
float   SinDegrees(float const aDeg);

float   RadiansFromAngle(Angle const angle);
float   DegreesFromAngle(Angle const angle);
float   RadiansFromDegree(float const angle);
float   DegreesFromRadians(float const angle);