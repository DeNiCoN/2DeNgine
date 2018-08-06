#pragma once

typedef struct
{
	float x;
	float y;
	float z;
	float w;
} vec4;

inline vec4 vec4_add(vec4 a, vec4 b);