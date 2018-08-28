#ifndef MATH_H
#define MATH_H

#include "common.h"

// struct definition for a 4x4 matrix
typedef struct {
	f32 m[4][4];
} mat4;

/**
 * Allocate a mat4 set to the identity matrix.
 */
inline mat4 identity(void) {
	return {{{1.0f, 0.0f, 0.0f, 0.0f},
			 {0.0f, 1.0f, 0.0f, 0.0f},
			 {0.0f, 0.0f, 1.0f, 0.0f},
			 {0.0f, 0.0f, 0.0f, 1.0f}}};
}


inline mat4 perspective(f32 near, f32 far) {
	
}

inline mat4 operator *(const f32 &a, const mat4 &b) {
	mat4 result = {};

	result.m[0][0] = a * b.m[0][0];
	result.m[0][1] = a * b.m[0][1];
	result.m[0][2] = a * b.m[0][2];
	result.m[0][3] = a * b.m[0][3];

	result.m[1][0] = a * b.m[1][0];
	result.m[1][1] = a * b.m[1][1];
	result.m[1][2] = a * b.m[1][2];
	result.m[1][3] = a * b.m[1][3];

	result.m[2][0] = a * b.m[2][0];
	result.m[2][1] = a * b.m[2][1];
	result.m[2][2] = a * b.m[2][2];
	result.m[2][3] = a * b.m[2][3];
	
	result.m[3][0] = a * b.m[3][0];
	result.m[3][1] = a * b.m[3][1];
	result.m[3][2] = a * b.m[3][2];
	result.m[3][3] = a * b.m[3][3];

	return result;
}

inline mat4 operator *(const mat4 &a, const mat4 &b) {
	mat4 result = {};

	return result;
}

inline mat4 operator +(const mat4 &a, const mat4 &b) {
	mat4 result = {};

	result.m[0][0] = a.m[0][0] + b.m[0][0];
	result.m[0][1] = a.m[0][1] + b.m[0][1];
	result.m[0][2] = a.m[0][2] + b.m[0][2];
	result.m[0][3] = a.m[0][3] + b.m[0][3];

	result.m[1][0] = a.m[1][0] + b.m[1][0];
	result.m[1][1] = a.m[1][1] + b.m[1][1];
	result.m[1][2] = a.m[1][2] + b.m[1][2];
	result.m[1][3] = a.m[1][3] + b.m[1][3];

	result.m[2][0] = a.m[2][0] + b.m[2][0];
	result.m[2][1] = a.m[2][1] + b.m[2][1];
	result.m[2][2] = a.m[2][2] + b.m[2][2];
	result.m[2][3] = a.m[2][3] + b.m[2][3];
	
	result.m[3][0] = a.m[3][0] + b.m[3][0];
	result.m[3][1] = a.m[3][1] + b.m[3][1];
	result.m[3][2] = a.m[3][2] + b.m[3][2];
	result.m[3][3] = a.m[3][3] + b.m[3][3];

	return result;
}

inline mat4 operator -(const mat4 &a, const mat4 &b) {
	mat4 result = {};

	result.m[0][0] = a.m[0][0] - b.m[0][0];
	result.m[0][1] = a.m[0][1] - b.m[0][1];
	result.m[0][2] = a.m[0][2] - b.m[0][2];
	result.m[0][3] = a.m[0][3] - b.m[0][3];

	result.m[1][0] = a.m[1][0] - b.m[1][0];
	result.m[1][1] = a.m[1][1] - b.m[1][1];
	result.m[1][2] = a.m[1][2] - b.m[1][2];
	result.m[1][3] = a.m[1][3] - b.m[1][3];

	result.m[2][0] = a.m[2][0] - b.m[2][0];
	result.m[2][1] = a.m[2][1] - b.m[2][1];
	result.m[2][2] = a.m[2][2] - b.m[2][2];
	result.m[2][3] = a.m[2][3] - b.m[2][3];
	
	result.m[3][0] = a.m[3][0] - b.m[3][0];
	result.m[3][1] = a.m[3][1] - b.m[3][1];
	result.m[3][2] = a.m[3][2] - b.m[3][2];
	result.m[3][3] = a.m[3][3] - b.m[3][3];

	return result;
}
// struct definition for a 4 component vector
typedef struct {
	union {
		struct {
			f32 x;
			f32 y;
			f32 z;
			f32 w;
		};
		struct {
			f32 r;
			f32 g;
			f32 b;
			f32 a;
		};
	};
} vec4;

inline vec4 operator *(const f32 &a, const vec4 &b) {
	vec4 result = {};

	result.x = a * b.x;
	result.y = a * b.y;
	result.z = a * b.z;
	result.w = a * b.w;

	return result;
}

inline vec4 operator *(const mat4 &a, const vec4 &b) {
	vec4 result = {};

	return result;
}

inline vec4 operator +(const vec4 &a, const vec4 &b) {
	vec4 result = {};

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	result.w = a.w * b.w;

	return result;
}

inline vec4 operator -(const vec4 &a, const vec4 &b) {
	vec4 result = {};

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;

	return result;
}
#endif
