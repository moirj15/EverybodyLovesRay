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
        f32 d[4];
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
        f32 d[3];
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
        f32 d[2];
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

inline f32 len(const vec4 &v) {
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

inline f32 len(const vec3 &v) {
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

inline f32 len(const vec2 &v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

inline f32 comp_add(const vec4 &v) {
    return v.x + v.y + v.z + v.w;
}

inline vec4 pow(const vec4 v, const f32 p) {
    return { powf(v.x, p), powf(v.y, p), powf(v.z, p), powf(v.w, p) }; 
}

inline vec3 cross(const vec3 &a, const vec3 &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

inline f32 dot(const vec3 &a, const vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec4 normalize(const vec4 &v) {
    f32 l = len(v);
    return {v.x / l, v.y / l, v.z / l, v.w / l};
}

inline vec3 normalize(const vec3 &v) {
    f32 l = len(v);
    return {v.x / l, v.y / l, v.z / l};
}

inline vec2 normalize(const vec2 &v) {
    f32 l = len(v);
    return {v.x / l, v.y / l};
}

mat4 camera_mat(const vec3 &pos, const vec3 &lookat, const vec3 &up) {
    mat4 ret = identity();
    vec3 n = normalize(pos - lookat);
    vec3 u = normalize(cross(up, n));
    vec3 v = normalize(cross(n, u));
    for (s32 i = 0; i < 3; i++) {
        ret[0][i] = u.d[i];
        ret[1][i] = v.d[i];
        ret[2][i] = n.d[i];
    }
    ret[0][3] = -1.0f * (dot(u, pos));
    ret[1][3] = -1.0f * (dot(v, pos));
    ret[2][3] = -1.0f * (dot(n, pos));
    return ret;
}


// Taken from 
// https://semath.info/src/inverse-cofactor-ex4.html
mat4 inverse(const mat4 &m) {
    f32 det0 = m[0][0] 
        * (m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1]
        + m[1][3] * m[2][1] * m[3][2] - m[1][3] * m[2][2] * m[3][1]
        - m[1][2] * m[2][1] * m[3][3] - m[1][1] * m[2][3] * m[3][2]);

    f32 det1 = m[1][0] 
        * (m[0][1] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][1]
        + m[0][3] * m[2][1] * m[3][2] - m[0][3] * m[2][2] * m[3][1]
        - m[0][2] * m[2][1] * m[3][3] - m[0][1] * m[2][3] * m[3][2]);

    f32 det2 = m[2][0] 
        * (m[0][1] * m[1][2] * m[3][3] + m[0][2] * m[1][3] * m[3][1]
        + m[0][3] * m[1][1] * m[3][2] - m[0][3] * m[1][2] * m[3][1]
        - m[0][2] * m[1][1] * m[3][3] - m[0][1] * m[1][3] * m[3][2]);

    f32 det3 = m[3][0] 
        * (m[0][1] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[2][1]
        + m[0][3] * m[1][1] * m[2][2] - m[0][3] * m[1][2] * m[2][1]
        - m[0][2] * m[1][1] * m[2][3] - m[0][1] * m[1][3] * m[2][2]);

    f32 determinate = det0 - det1 + det2 + det3;
    if (determinate == 0.0) {
        return 0.0 * m;
    }

    mat4 adjugate;
    adjugate[0][0] = m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1]
        + m[1][3] * m[2][1] * m[3][2] - m[1][3] * m[2][2] * m[3][1]
        - m[1][2] * m[2][1] * m[3][3] - m[1][1] * m[2][3] * m[3][2];

    adjugate[0][1] = -m[0][1] * m[2][2] * m[3][3] - m[0][2] * m[2][3] * m[3][1]
        - m[0][3] * m[2][1] * m[3][2] + m[0][3] * m[2][2] * m[3][1]
        + m[0][2] * m[2][1] * m[3][3] + m[0][1] * m[2][3] * m[3][2];

    adjugate[0][2] = m[0][1] * m[1][2] * m[3][3] + m[1][2] * m[1][3] * m[3][1]
        + m[0][3] * m[1][1] * m[3][2] - m[0][3] * m[1][2] * m[3][1]
        - m[0][2] * m[1][1] * m[3][3] - m[0][1] * m[1][3] * m[3][2];

    adjugate[0][3] = -m[0][1] * m[1][2] * m[2][3] - m[0][2] * m[1][3] * m[2][1]
        - m[0][3] * m[1][1] * m[2][2] + m[0][3] * m[1][2] * m[2][1]
        + m[0][2] * m[1][1] * m[2][3] + m[0][1] * m[1][3] * m[2][2];


    adjugate[1][0] = -m[1][0] * m[2][2] * m[3][3] - m[1][2] * m[2][3] * m[3][1]
        - m[1][3] * m[2][0] * m[3][2] + m[1][3] * m[2][2] * m[3][0]
        + m[1][2] * m[2][0] * m[3][3] + m[1][0] * m[2][3] * m[3][2];

    adjugate[1][1] = m[0][0] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][0]
        + m[0][3] * m[2][0] * m[3][2] - m[0][3] * m[2][2] * m[3][0]
        - m[0][2] * m[2][0] * m[3][3] - m[0][0] * m[2][3] * m[3][2];

    adjugate[1][2] = -m[0][0] * m[0][2] * m[3][3] - m[0][2] * m[1][3] * m[3][0]
        - m[0][3] * m[1][0] * m[3][2] + m[0][3] * m[1][2] * m[3][0]
        + m[0][2] * m[1][0] * m[3][3] + m[0][0] * m[1][3] * m[3][2];

    adjugate[1][3] = m[0][0] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[3][1]
        + m[0][3] * m[1][0] * m[2][2] - m[0][3] * m[1][2] * m[2][0]
        - m[0][2] * m[1][0] * m[2][3] - m[0][0] * m[1][3] * m[2][2];


    adjugate[2][0] = m[1][0] * m[2][1] * m[1][1] + m[2][3] * m[2][3] * m[3][0]
        + m[1][3] * m[2][0] * m[3][1] - m[1][3] * m[2][1] * m[3][0]
        - m[1][1] * m[2][0] * m[3][3] - m[1][0] * m[2][3] * m[3][1];

    adjugate[2][1] = -m[0][0] * m[2][1] * m[3][3] - m[0][1] * m[2][3] * m[3][0]
        - m[0][3] * m[2][0] * m[3][1] + m[0][3] * m[2][1] * m[3][0]
        + m[0][1] * m[2][0] * m[3][3] + m[0][0] * m[2][3] * m[3][1];

    adjugate[2][2] = m[0][0] * m[1][1] * m[3][3] + m[0][1] * m[1][3] * m[3][1]
        + m[0][3] * m[1][0] * m[3][1] - m[0][3] * m[1][1] * m[3][0]
        - m[0][1] * m[1][0] * m[3][3] - m[0][0] * m[1][3] * m[3][1];

    adjugate[2][3] = -m[0][0] * m[1][1] * m[2][3] - m[0][1] * m[1][3] * m[2][0]
        - m[0][3] * m[1][0] * m[2][1] + m[0][3] * m[1][1] * m[2][0]
        + m[0][1] * m[1][0] * m[2][3] + m[0][0] * m[1][3] * m[2][1];
    

    adjugate[3][0] = -m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0]
        - m[1][2] * m[2][0] * m[3][1] + m[1][2] * m[2][1] * m[3][0]
        + m[1][1] * m[2][0] * m[3][2] + m[1][0] * m[2][2] * m[3][1];

    adjugate[3][1] = m[0][0] * m[2][1] * m[3][2] + m[0][1] * m[2][2] * m[3][0]
        + m[0][2] * m[2][0] * m[3][1] - m[0][2] * m[2][1] * m[3][0]
        - m[0][1] * m[2][0] * m[3][2] - m[0][0] * m[2][2] * m[3][1];

    adjugate[3][2] = -m[0][0] * m[1][1] * m[3][2] - m[0][1] * m[1][2] * m[3][0]
        - m[0][2] * m[1][0] * m[3][1] + m[0][2] * m[1][1] * m[3][0]
        + m[0][1] * m[1][0] * m[3][2] + m[0][0] * m[1][2] * m[3][1];

    adjugate[3][3] = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0]
        + m[0][2] * m[1][0] * m[2][1] - m[0][2] * m[1][1] * m[2][0]
        - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];

    return (1.0f / determinate) * adjugate;
}



#endif
