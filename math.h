#ifndef MATH_H
#define MATH_H

#include <math.h>
//#include <cmath>
#include "common.h"

// struct definition for a 4x4 matrix
struct mat4 {
	f32 m[4][4];

    inline f32 *operator[](s32 x) {
        return m[x];
    }
    inline const f32 *operator[](s32 x) const {
        return m[x];
    }
};

struct mat3 {
	f32 m[3][3];

    inline f32 *operator[](s32 x) {
        return m[x];
    }
    inline const f32 *operator[](s32 x) const {
        return m[x];
    }
};

struct mat2 {
	f32 m[2][2];

    inline f32 *operator[](s32 x) {
        return m[x];
    }
    inline const f32 *operator[](s32 x) const {
        return m[x];
    }
};

// struct definition for a 4 component vector
struct vec4 {
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
};

struct vec3 {
    union {
        struct {
            f32 x;
            f32 y;
            f32 z;
        };
        struct {
            f32 r;
            f32 g;
            f32 b;
        };
    };

};

struct vec2 {
    union {
        struct {
            f32 x;
            f32 y;
        };
        struct {
            f32 u;
            f32 v;
        };
    };

};


#define print_mat4(x) \
	printf("%f %f %f %f\n", x.m[0][0], x.m[0][1], x.m[0][2], x.m[0][3]); \
	printf("%f %f %f %f\n", x.m[1][0], x.m[1][1], x.m[1][2], x.m[1][3]); \
	printf("%f %f %f %f\n", x.m[2][0], x.m[2][1], x.m[2][2], x.m[2][3]); \
	printf("%f %f %f %f\n", x.m[3][0], x.m[3][1], x.m[3][2], x.m[3][3]); 

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

    for (s32 x = 0; x < 4; x++) {
        for (s32 y = 0; y < 4; y++) {
            for (s32 k = 0; k < 4; k++) {
                result[x][y] += a[x][k] * b[y][k];
            }
        }
    }

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

#define print_vec4(v) printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);

inline vec4 Vec4(f32 x, f32 y, f32 z, f32 w) {
    return {x, y, z, w};
}

inline vec4 Vec4(f32 v) {
    return { v, v, v, v };
}
inline vec4 Vec4(vec3 v, f32 w) {
    return { v.x, v.y, v.z, w };
}

inline vec3 Vec3(f32 x, f32 y, f32 z) {
    return { x, y, z };
}

inline vec3 Vec3(vec4 v) {
    return { v.x, v.y, v.z };
}

inline vec4 operator *(const f32 &a, const vec4 &b) {
	vec4 result = {};

	result.x = a * b.x;
	result.y = a * b.y;
	result.z = a * b.z;
	result.w = a * b.w;

	return result;
}

inline vec4 operator *(const vec4 &a, const f32 b) {
    return { a.x * b, a.y * b, a.z * b, a.w * b };
}

inline vec4 operator *(const vec4 &a, const vec4 &b) {
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}

inline vec4 operator *(const mat4 &a, const vec4 &b) {
	vec4 result = {};

	result.x = a.m[0][0] * b.x + a.m[0][1] * b.x
			 + a.m[0][2] * b.x + a.m[0][3] * b.x;
	result.y = a.m[1][0] * b.x + a.m[1][1] * b.x
			 + a.m[1][2] * b.x + a.m[1][3] * b.x;
	result.z = a.m[2][0] * b.x + a.m[2][1] * b.x
			 + a.m[2][2] * b.x + a.m[2][3] * b.x;
	result.w = a.m[3][0] * b.x + a.m[3][1] * b.x
			 + a.m[3][2] * b.x + a.m[3][3] * b.x;

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

inline vec4 operator+(const vec4 &a, const f32 b) {
    return {a.x + b, a.y + b, a.z + b, a.w + b};
}

inline vec4 operator -(const vec4 &a, const vec4 &b) {
	vec4 result = {};

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;

	return result;
}

inline vec4 operator-(const vec4 &a, const f32 b) {
    return {a.x - b, a.y - b, a.z - b, a.w - b};
}

inline vec3 operator *(const f32 &a, const vec3 &b) {
    return { a * b.x, a * b.y, a * b.z };
}

inline vec3 operator *(const vec3 &a, const vec3 &b) {
    return { a.x * b.x, a.y * b.y, a.z * b.z };
}

inline vec3 operator +(const vec3 &a, const vec3 &b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

inline vec3 operator+(const vec3 &a, const f32 b) {
    return {a.x + b, a.y + b, a.z + b};
}

inline vec3 operator -(const vec3 &a, const vec3 &b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

inline vec3 operator-(const vec3 &a, const f32 b) {
    return {a.x - b, a.y - b, a.z - b};
}

mat4 camera_mat(const vec3 &pos, const vec3 &lookat, const vec3 &up) {
    return {};
}

f32 comp_add(const vec4 &v) {
    return v.x + v.y + v.z + v.w;
}

vec4 pow(const vec4 v, const f32 p) {
    return { powf(v.x, p), powf(v.y, p), powf(v.z, p), powf(v.w, p) }; 
}

vec3 cross(const vec3 &a, const vec3 &b) {
    return {};
}

f32 dot(const vec3 &a, const vec3 &b) {
    return {};
}

mat4 inverse(const mat4 &m) {
    return {};
}

vec4 normalize(const vec4 &v) {

}

vec3 normalize(const vec3 &v) {

}

vec2 normalize(const vec2 &v) {

}


#endif
