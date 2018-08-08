#pragma once
#include <xmmintrin.h>
#include <stdio.h>

#define S_INLINE static inline

typedef __declspec(align(16)) union
{
	struct {
		float x;
		float y;
	};

	float value[2];
}  vec2;

typedef __declspec(align(16)) union
{
	struct
	{
		union
		{
			vec2 xy;
			struct
			{
				float x;
				float y;
			};
		};
		float z;
	};

	float value[3];
}  vec3;

typedef __declspec(align(16)) union
{	
	struct 
	{
		union 
		{
			vec3 xyz;
			struct 
			{
				float x;
				float y;
				float z;
			};
		};
		float w;
	};



	__m128 ssevalue;

	float value[4];
}  vec4;




S_INLINE vec4 vec4_add(vec4 a, vec4 b)
{	
	vec4 c;
	
	c.ssevalue = _mm_add_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE vec4 vec4_sub(vec4 a, vec4 b)
{
	vec4 c;
	c.ssevalue = _mm_sub_ps(a.ssevalue, b.ssevalue);
	return c;
}