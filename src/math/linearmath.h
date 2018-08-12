#pragma once
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <stdio.h>
#include <math.h>
#include <smmintrin.h>

#define S_INLINE static inline

#define SHUFFLE_PARAM(x, y, z, w) \
((x) | ((y) << 2) | ((z) << 4) | ((w) << 6))

typedef struct {
	vec4 value[4];
}  mat44;

typedef __declspec(align(8)) union
{
	struct {
		float x;
		float y;
	};

	float value[2];
}  vec2;

typedef union
{
	struct
	{
		float x;
		float y;
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


	float value[4];

	__m128 ssevalue;

}  vec4;

S_INLINE vec2 vec2_(float x, float y) {
	vec2 c = { x, y };
	return c;
}

S_INLINE vec3 vec3_(float x, float y, float z) {
	vec3 c = { x, y , z};
	return c;
}

S_INLINE vec4 vec4_(float x, float y, float z, float w) {
	vec4 c;
	c.ssevalue = _mm_set_ps(x, y, z, w);
	return c;
}

S_INLINE vec2 vec2_add(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

S_INLINE vec3 vec3_add(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

S_INLINE vec4 vec4_add(vec4 a, vec4 b)
{	
	vec4 c;
	
	c.ssevalue = _mm_add_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE vec2 vec2_sub(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

S_INLINE vec3 vec3_sub(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

S_INLINE vec4 vec4_sub(vec4 a, vec4 b)
{
	vec4 c;
	c.ssevalue = _mm_sub_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE vec2 vec2_mul(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	return c;
}

S_INLINE vec3 vec3_mul(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}

S_INLINE vec4 vec4_mul(vec4 a, vec4 b)
{
	vec4 c;
	c.ssevalue = _mm_mul_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE vec2 vec2_div(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x / b.x;
	c.y = a.y / b.y;
	return c;
}

S_INLINE vec3 vec3_div(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
	return c;
}

S_INLINE vec4 vec4_div(vec4 a, vec4 b)
{
	vec4 c;
	c.ssevalue = _mm_div_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE float vec2_dot(vec2 a, vec2 b) 
{
	return a.x * b.x + a.y * b.y;
}

S_INLINE float vec3_dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

S_INLINE float vec4_dot(vec4 a, vec4 b)
{
	float result;
	//multiply, sum and store in result
	__m128 tmp = _mm_mul_ps(a.ssevalue, b.ssevalue);
	tmp = _mm_hadd_ps(tmp, tmp);
	tmp = _mm_hadd_ps(tmp, tmp);
	_mm_store_ss(&result, tmp);
	return result;
}

S_INLINE float vec2_length_squared(vec2 a)
{
	return vec2_dot(a, a);
}

S_INLINE float vec3_length_squared(vec3 a)
{
	return vec3_dot(a, a);
}

S_INLINE float vec4_length_squared(vec4 a)
{
	return vec4_dot(a, a);
}

S_INLINE float vec2_length(vec2 a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

S_INLINE float vec3_length(vec3 a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

S_INLINE float vec4_length(vec4 a)
{
	return sqrtf(vec4_length_squared(a));
}
//return z coordinate of 3d vector perpendicular to 2d vectors a and b 
S_INLINE float vec2_cross(vec2 a, vec2 b) 
{
	return a.x*b.y - a.y*b.x;
}

S_INLINE vec3 vec3_cross(vec3 a, vec3 b)
{
	vec3 c;
	c.x = a.y*b.z - a.z*b.y;
	c.y = a.x*b.z - a.z*b.x;
	c.z = a.x*b.y - a.y*b.x;
	return c;
}

S_INLINE vec2 vec2_scale(vec2 a, float scalar)
{
	vec2 c;
	c.x = a.x * scalar;
	c.y = a.y * scalar;
	return c;
}

S_INLINE vec3 vec3_scale(vec3 a, float scalar)
{
	vec3 c;
	c.x = a.x * scalar;
	c.y = a.y * scalar;
	c.z = a.z * scalar;
	return c;
}

S_INLINE vec4 vec4_scale(vec4 a, float scalar)
{
	vec4 c;
	__m128 multiplier = _mm_set1_ps(scalar);

	c.ssevalue = _mm_mul_ps(a.ssevalue, multiplier);
	return c;
}

S_INLINE vec2 vec2_decreace(vec2 a, float scalar)
{
	vec2 c;
	c.x = a.x / scalar;
	c.y = a.y / scalar;
	return c;
}

S_INLINE vec3 vec3_decreace(vec3 a, float scalar)
{
	vec3 c;
	c.x = a.x / scalar;
	c.y = a.y / scalar;
	c.z = a.z / scalar;
	return c;
}

S_INLINE vec4 vec4_decreace(vec4 a, float scalar)
{
	vec4 c;
	__m128 multiplier = _mm_set1_ps(scalar);

	c.ssevalue = _mm_div_ps(a.ssevalue, multiplier);
	return c;
}

S_INLINE vec2 vec2_normalize(vec2 a)
{
	return vec2_decreace(a, vec2_length(a));
}

S_INLINE vec3 vec3_normalize(vec3 a)
{
	return vec3_decreace(a, vec3_length(a));
}

S_INLINE vec4 vec4_normalize(vec4 a)
{
	return vec4_decreace(a, vec4_length(a));
}

S_INLINE mat44 mat44_identity(float diagonal) 
{
	mat44 c;
	c.value[0].ssevalue = _mm_set(diagonal, 0, 0, 0);
	c.value[1].ssevalue = _mm_set(0, diagonal, 0, 0);
	c.value[2].ssevalue = _mm_set(0, 0, diagonal, 0);
	c.value[3].ssevalue = _mm_set(0, 0, 0, diagonal);
	return c;
}

S_INLINE mat44 mat44_transpose(mat44 a)
{
	_MM_TRANSPOSE4_PS(a.value[0], a.value[1], a.value[2], a.value[3]);
	return a;
}

S_INLINE mat44 mat44_scale_uniform(float scalar) 
{
	mat44 c;
	c.value[0].ssevalue = _mm_set(scalar, 0, 0, 0);
	c.value[1].ssevalue = _mm_set(0, scalar, 0, 0);
	c.value[2].ssevalue = _mm_set(0, 0, scalar, 0);
	c.value[3].ssevalue = _mm_set(0, 0, 0, 1);
	return c;
}

S_INLINE mat44 mat44_translate(vec3 a)
{
	mat44 c = mat44_identity(1.0f);
	c.value[3].xyz = a;
	return c;
}

S_INLINE mat44 mat44_rotate_by_x(float radians) 
{
	mat44 c = mat44_identity(1.0f);
	c.value[1].value[1] = cosf(radians);
	c.value[2].value[2] = cosf(radians);
	c.value[1].value[2] = -sinf(radians);
	c.value[2].value[1] = sinf(radians);
	return c;
}

S_INLINE mat44 mat44_rotate_by_y(float radians) 
{
	mat44 c = mat44_identity(1.0f);
	c.value[0].value[0] = cosf(radians);
	c.value[2].value[2] = cosf(radians);
	c.value[0].value[2] = sinf(radians);
	c.value[2].value[0] = -sinf(radians);
	return c;
}

S_INLINE mat44 mat44_rotate_by_x(float radians) 
{
	mat44 c = mat44_identity(1.0f);
	c.value[0].value[0] = cosf(radians);
	c.value[1].value[1] = cosf(radians);
	c.value[0].value[1] = -sinf(radians);
	c.value[1].value[0] = sinf(radians);
	return c;
}

S_INLINE mat44 mat44_add(mat44 a, mat44 b)
{
	mat44 c;
	c.value[0].ssevalue = _mm_add_ps(a.value[0].ssevalue, b.value[0].ssevalue);
	c.value[1].ssevalue = _mm_add_ps(a.value[1].ssevalue, b.value[1].ssevalue);
	c.value[2].ssevalue = _mm_add_ps(a.value[2].ssevalue, b.value[2].ssevalue);
	c.value[3].ssevalue = _mm_add_ps(a.value[3].ssevalue, b.value[3].ssevalue);
}

S_INLINE mat44 mat44_multiply(mat44 a, mat44 b)
{
	mat44 c;
	c.value[0].ssevalue = sse_vec_mat44_multiply(a.value[0].ssevalue, b);
	c.value[1].ssevalue = sse_vec_mat44_multiply(a.value[1].ssevalue, b);
	c.value[2].ssevalue = sse_vec_mat44_multiply(a.value[2].ssevalue, b);
	c.value[3].ssevalue = sse_vec_mat44_multiply(a.value[3].ssevalue, b);
	return c;
}

S_INLINE __m128 sse_vec_mat44_multiply(__m128 a, mat44 b) 
{
	__m128 c = _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(0, 0, 0, 0)), b.value[0]);
	c = _mm_add_ps(c, _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(1, 1, 1, 1)), b.value[1]));
	c = _mm_add_ps(c, _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(2, 2, 2, 2)), b.value[2]));
	c = _mm_add_ps(c, _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(3, 3, 3, 3)), b.value[3]));
	return c;
}
