#include "vector.h"
#include <math.h>

Vec2 MakeVec2(float const x, float const y)
{
    Vec2 a = { x, y };
    return a;
}

IntVec2 MakeIntVec2(int const x, int const y)
{
    IntVec2 a = { x, y };
    return a;
}

float LengthVec2(Vec2 const a)
{
    float const vecLength = sqrtf( (a.x * a.x) + (a.y * a.y) );
    return vecLength;
}

Vec2 NormalizeVec2(Vec2 const a)
{
    Vec2 normalized = { 1.f, 0.f };

    float const length = LengthVec2(a);
    if(length != 0)
        normalized = DivVec2(a, length);
    
    return normalized;
}

Vec2 AddVec2(Vec2 const a, Vec2 const b)
{
    Vec2 sum = 
    {
        a.x + b.x,
        a.y + b.y
    };

    return sum;
}

Vec2 SubVec2(Vec2 const a, Vec2 const b)
{
    Vec2 sub =
    {
        a.x - b.x,
        a.y - b.y
    };

    return sub;
}

Vec2 ScaleVec2(Vec2 const a, float const scale)
{
    Vec2 scaledVec2 =
    {
        a.x * scale,
        a.y * scale
    };

    return scaledVec2;
}

Vec2 DivVec2(Vec2 const a, float const divider)
{
    Vec2 divAns =
    {
        a.x / divider,
        a.y / divider
    };

    return divAns;
}

Vec2 ModCompVec2(Vec2 const a, float const modifier)
{
    Vec2 modifiedVec = 
    {
        a.x + modifier,
        a.y + modifier
    };

    return modifiedVec;
}

Vec2 MoveTowardsVec2( Vec2 currentPos, Vec2 targetPos, float fraction )
{
	Vec2 towardsTarget = SubVec2( targetPos, currentPos );
	currentPos = AddVec2( currentPos, ScaleVec2( towardsTarget, fraction ) );
	return currentPos;
}

Vec2 Vec2FromIntVec2(IntVec2 from)
{
    Vec2 vecToRet =
    {
		from.x,
		from.y
    };

    return vecToRet;
}

float LengthIntVec2(IntVec2 const a)
{
    float const len = sqrtf( (a.x * a.x) + (a.y * a.y) );
    return len;
}

IntVec2 AddIntVec2(IntVec2 const a, IntVec2 b)
{
    IntVec2 sum = 
    {
        a.x + b.x,
        a.y + b.y
    };

    return sum;
}

IntVec2 SubIntVec2(IntVec2 const a, IntVec2 const b)
{
    IntVec2 sub =
    {
        a.x - b.x,
        a.y - b.y
    };

    return sub;
}

IntVec2 ModCompIntVec2(IntVec2 const a, int const modifier)
{
    IntVec2 modifiedIntVec =
    {
        a.x + modifier,
        a.y + modifier
    };

    return modifiedIntVec;
}

IntVec2 IntVec2FromVec2(Vec2 const from)
{
    IntVec2 intVecToRet =  
    { 
        (int)from.x, 
        (int)from.y 
    };
    return intVecToRet;
}