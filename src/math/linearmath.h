#pragma once
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <stdio.h>
#include <math.h>
#include <smmintrin.h>

#define S_INLINE static inline

#define SHUFFLE_PARAM(x, y, z, w) \
((x) | ((y) << 2) | ((z) << 4) | ((w) << 6))


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

typedef vec4 quat;

typedef struct {
	vec4 value[4];
}  mat44;

S_INLINE vec2 vec2Create(float x, float y) {
	vec2 c = { x, y };
	return c;
}

S_INLINE vec3 vec3Create(float x, float y, float z) {
	vec3 c = { x, y , z};
	return c;
}

S_INLINE vec4 vec4CreateSse(float x, float y, float z, float w) {
	vec4 c;
	c.ssevalue = _mm_set_ps(w, z, y, x);
	return c;
}

S_INLINE vec4 vec4Create(float x, float y, float z, float w) {
	vec4 c = { x, y, z, w };
	return c;
}

S_INLINE vec2 vec2Neg(vec2 a)
{
	a.x = -a.x;
	a.y = -a.y;
	return a;
}

S_INLINE vec3 vec3Neg(vec3 a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	return a;
}

S_INLINE vec4 vec4Neg(vec4 a)
{
	a.ssevalue = _mm_mul_ps(a.ssevalue, _mm_set1_ps(-1));
	return a;
}

S_INLINE vec2 vec2Add(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

S_INLINE vec3 vec3Add(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

S_INLINE vec4 vec4Add(vec4 a, vec4 b)
{	
	vec4 c;
	
	c.ssevalue = _mm_add_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE vec2 vec2Sub(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

S_INLINE vec3 vec3Sub(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

S_INLINE vec4 vec4Sub(vec4 a, vec4 b)
{
	vec4 c;
	c.ssevalue = _mm_sub_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE vec2 vec2Mul(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	return c;
}

S_INLINE vec3 vec3Mul(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}

S_INLINE vec4 vec4Mul(vec4 a, vec4 b)
{
	vec4 c;
	c.ssevalue = _mm_mul_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE vec2 vec2Div(vec2 a, vec2 b)
{
	vec2 c;

	c.x = a.x / b.x;
	c.y = a.y / b.y;
	return c;
}

S_INLINE vec3 vec3Div(vec3 a, vec3 b)
{
	vec3 c;

	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
	return c;
}

S_INLINE vec4 vec4Div(vec4 a, vec4 b)
{
	vec4 c;
	c.ssevalue = _mm_div_ps(a.ssevalue, b.ssevalue);
	return c;
}

S_INLINE float vec2Dot(vec2 a, vec2 b) 
{
	return a.x * b.x + a.y * b.y;
}

S_INLINE float vec3Dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

S_INLINE float vec4Dot(vec4 a, vec4 b)
{
	float result;
	//multiply, sum and store in result
	__m128 tmp = _mm_mul_ps(a.ssevalue, b.ssevalue);
	tmp = _mm_hadd_ps(tmp, tmp);
	tmp = _mm_hadd_ps(tmp, tmp);
	_mm_store_ss(&result, tmp);
	return result;
}

S_INLINE float vec2LengthSquared(vec2 a)
{
	return vec2Dot(a, a);
}

S_INLINE float vec3LengthSquared(vec3 a)
{
	return vec3Dot(a, a);
}

S_INLINE float vec4LengthSquared(vec4 a)
{
	return vec4Dot(a, a);
}

S_INLINE float vec2Length(vec2 a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

S_INLINE float vec3Length(vec3 a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

S_INLINE float vec4Length(vec4 a)
{
	return sqrtf(vec4LengthSquared(a));
}
//return z coordinate of 3d vector perpendicular to 2d vectors a and b 
S_INLINE float vec2Cross(vec2 a, vec2 b) 
{
	return a.x*b.y - a.y*b.x;
}

S_INLINE vec3 vec3Cross(vec3 a, vec3 b)
{
	vec3 c;
	c.x = a.y*b.z - a.z*b.y;
	c.y = a.z*b.x - a.x*b.z;
	c.z = a.x*b.y - a.y*b.x;
	return c;
}

S_INLINE vec2 vec2Scale(vec2 a, float scalar)
{
	vec2 c;
	c.x = a.x * scalar;
	c.y = a.y * scalar;
	return c;
}

S_INLINE vec3 vec3Scale(vec3 a, float scalar)
{
	vec3 c;
	c.x = a.x * scalar;
	c.y = a.y * scalar;
	c.z = a.z * scalar;
	return c;
}

S_INLINE vec4 vec4Scale(vec4 a, float scalar)
{
	vec4 c;
	__m128 multiplier = _mm_set1_ps(scalar);

	c.ssevalue = _mm_mul_ps(a.ssevalue, multiplier);
	return c;
}

S_INLINE vec2 vec2Decreace(vec2 a, float scalar)
{
	vec2 c;
	c.x = a.x / scalar;
	c.y = a.y / scalar;
	return c;
}

S_INLINE vec3 vec3Decreace(vec3 a, float scalar)
{
	vec3 c;
	c.x = a.x / scalar;
	c.y = a.y / scalar;
	c.z = a.z / scalar;
	return c;
}

S_INLINE vec4 vec4Decreace(vec4 a, float scalar)
{
	vec4 c;
	__m128 multiplier = _mm_set1_ps(scalar);

	c.ssevalue = _mm_div_ps(a.ssevalue, multiplier);
	return c;
}

S_INLINE vec2 vec2Normalize(vec2 a)
{
	return vec2Decreace(a, vec2Length(a));
}

S_INLINE vec3 vec3Normalize(vec3 a)
{
	return vec3Decreace(a, vec3Length(a));
}

S_INLINE vec4 vec4Normalize(vec4 a)
{
	return vec4Decreace(a, vec4Length(a));
}

S_INLINE mat44 mat44Identity(float diagonal) 
{
	mat44 c;
	c.value[0] = vec4Create(diagonal, 0, 0, 0);
	c.value[1] = vec4Create(0, diagonal, 0, 0);
	c.value[2] = vec4Create(0, 0, diagonal, 0);
	c.value[3] = vec4Create(0, 0, 0, diagonal);
	return c;
}

S_INLINE mat44 mat44Transpose(mat44 a)
{
	_MM_TRANSPOSE4_PS(a.value[0].ssevalue, a.value[1].ssevalue, a.value[2].ssevalue, a.value[3].ssevalue);
	return a;
}

S_INLINE mat44 mat44ScaleUniform(float scalar) 
{
	mat44 c;
	c.value[0] = vec4Create(scalar, 0, 0, 0);
	c.value[1] = vec4Create(0, scalar, 0, 0);
	c.value[2] = vec4Create(0, 0, scalar, 0);
	c.value[3] = vec4Create(0, 0, 0, 1);
	return c;
}

S_INLINE mat44 mat44Translate(vec3 a)
{
	mat44 c = mat44Identity(1.0f);
	c.value[3].xyz = a;
	return c;
}

S_INLINE mat44 mat44RotateByX(float radians) 
{
	mat44 c = mat44Identity(1.0f);
	c.value[1].value[1] = cosf(radians);
	c.value[2].value[2] = cosf(radians);
	c.value[1].value[2] = -sinf(radians);
	c.value[2].value[1] = sinf(radians);
	return c;
}

S_INLINE mat44 mat44RotateByY(float radians) 
{
	mat44 c = mat44Identity(1.0f);
	c.value[0].value[0] = cosf(radians);
	c.value[2].value[2] = cosf(radians);
	c.value[0].value[2] = sinf(radians);
	c.value[2].value[0] = -sinf(radians);
	return c;
}

S_INLINE mat44 mat44RotateByZ(float radians) 
{
	mat44 c = mat44Identity(1.0f);
	c.value[0].value[0] = cosf(radians);
	c.value[1].value[1] = cosf(radians);
	c.value[0].value[1] = -sinf(radians);
	c.value[1].value[0] = sinf(radians);
	return c;
}

S_INLINE mat44 mat44Add(mat44 a, mat44 b)
{
	mat44 c;
	c.value[0].ssevalue = _mm_add_ps(a.value[0].ssevalue, b.value[0].ssevalue);
	c.value[1].ssevalue = _mm_add_ps(a.value[1].ssevalue, b.value[1].ssevalue);
	c.value[2].ssevalue = _mm_add_ps(a.value[2].ssevalue, b.value[2].ssevalue);
	c.value[3].ssevalue = _mm_add_ps(a.value[3].ssevalue, b.value[3].ssevalue);
}

S_INLINE __m128 sseVecMat44Multiply(__m128 a, mat44 b)
{
	__m128 c = _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(0, 0, 0, 0)), b.value[0].ssevalue);
	c = _mm_add_ps(c, _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(1, 1, 1, 1)), b.value[1].ssevalue));
	c = _mm_add_ps(c, _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(2, 2, 2, 2)), b.value[2].ssevalue));
	c = _mm_add_ps(c, _mm_mul_ps(_mm_shuffle_ps(a, a, SHUFFLE_PARAM(3, 3, 3, 3)), b.value[3].ssevalue));
	return c;
}

S_INLINE mat44 mat44Multiply(mat44 a, mat44 b)
{
	mat44 c;
	c.value[0].ssevalue = sseVecMat44Multiply(a.value[0].ssevalue, b);
	c.value[1].ssevalue = sseVecMat44Multiply(a.value[1].ssevalue, b);
	c.value[2].ssevalue = sseVecMat44Multiply(a.value[2].ssevalue, b);
	c.value[3].ssevalue = sseVecMat44Multiply(a.value[3].ssevalue, b);
	return c;
}

S_INLINE quat quatFromVec3(vec3 a, float radians) 
{
	quat c;
	float tmp = radians / 2;
	c.xyz = vec3Scale(a, sinf(tmp));
	c.w = cosf(tmp);
}

S_INLINE quat quatFromVec4V2(vec4 a, float radians)
{
	quat c;
	float tmp = radians / 2;
	float sin = sinf(tmp);
	__m128 mul = _mm_set_ps(0, sin, sin, sin);
	__m128 add = _mm_set_ps(cosf(tmp), 0, 0, 0);
	c.ssevalue = _mm_add_ps(_mm_mul_ps(a.ssevalue, mul), add);
	return c;
}

S_INLINE quat quatNormalize(quat a) 
{
	return vec4Normalize(a);
}

S_INLINE quat quatConjugate(quat a)
{
	a.xyz = vec3Neg(a.xyz);
	return a;
}

S_INLINE quat quatConjugateSse(quat a)
{
	__m128 tmp = _mm_set_ps(1, -1, -1, -1);
	a.ssevalue = _mm_mul_ps(a.ssevalue, tmp);
	return a;
}

S_INLINE quat quatMultiply(quat a, quat b) 
{
	quat c;

	__m128 wzyx = _mm_shuffle_ps(a.ssevalue, a.ssevalue, _MM_SHUFFLE(0, 1, 2, 3));
	__m128 baba = _mm_shuffle_ps(b.ssevalue, b.ssevalue, _MM_SHUFFLE(0, 1, 0, 1));
	__m128 dcdc = _mm_shuffle_ps(b.ssevalue, b.ssevalue, _MM_SHUFFLE(2, 3, 2, 3));

	__m128 ZnXWY = _mm_hsub_ps(_mm_mul_ps(a.ssevalue, baba), _mm_mul_ps(wzyx, dcdc));
	__m128 XZYnW = _mm_hadd_ps(_mm_mul_ps(a.ssevalue, dcdc), _mm_mul_ps(wzyx, baba));
	__m128 XZWY = _mm_addsub_ps(_mm_shuffle_ps(XZYnW, ZnXWY, _MM_SHUFFLE(3, 2, 1, 0)),_mm_shuffle_ps(ZnXWY, XZYnW, _MM_SHUFFLE(2, 3, 0, 1)));

	c.ssevalue = _mm_shuffle_ps(XZWY, XZWY, _MM_SHUFFLE(2, 1, 3, 0));

	return c;
}

S_INLINE vec3 quatVec2Rotate(quat a, vec2 b) 
{
	quat tmp;
	tmp.ssevalue = _mm_set_ps(0, 0, b.y, b.x);
	tmp = quatMultiply(a, tmp);
	quat conjugate = quatConjugateSse(a);
	tmp = quatMultiply(tmp, conjugate);
	vec3 c = { tmp.x, tmp.y, tmp.z };
	return c;
}

S_INLINE vec3 quat_vec3_rotate(quat a, vec3 b) 
{
	quat tmp;
	tmp.ssevalue = _mm_set_ps(0, b.z, b.x, b.y);
	tmp = quatMultiply(a, tmp);
	quat conjugate = quatConjugateSse(a);
	tmp = quatMultiply(tmp, conjugate);
	vec3 c = { tmp.x, tmp.y, tmp.z };
	return c;
}


