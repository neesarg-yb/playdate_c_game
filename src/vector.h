#pragma once

// Vec2
typedef struct Vec2
{
    float x;
    float y;
} Vec2;

Vec2 MakeVec2(float const x, float const y);

// IntVec2
typedef struct IntVec2
{
    int x;
    int y;
} IntVec2;

IntVec2 MakeIntVec2(int const x, int const y);

// Vec2 funcs
float LengthVec2(Vec2 const a);
Vec2  NormalizeVec2(Vec2 const a);

Vec2  AddVec2(Vec2 const a, Vec2 const b);
Vec2  SubVec2(Vec2 const a, Vec2 const b);
Vec2  ScaleVec2(Vec2 const a, float const scale);
Vec2  DivVec2(Vec2 const a, float const divider);
Vec2  ModCompVec2(Vec2 const a, float const modifier);

Vec2  Vec2FromIntVec2(IntVec2 const from);

// IntVec2 funcs
float LengthIntVec2(IntVec2 const a);

IntVec2 AddIntVec2(IntVec2 const a, IntVec2 const b);
IntVec2 SubIntVec2(IntVec2 const a, IntVec2 const b);
IntVec2 ModCompIntVec2(IntVec2 const a, int const modifier);

IntVec2 IntVec2FromVec2(Vec2 const from);
