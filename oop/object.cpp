#include "object.h"

#include <glm/gtx/projection.hpp>

bool Sphere::intersect(const Ray &r, IntersectData &id) {
	const glm::vec4 &d = r.direction;
	const glm::vec4 &o = r.origin;
    f32 B = 2.0f * (d.x * (o.x - m_center.x) + d.y * (o.y - m_center.y)
            + d.z * (o.z - m_center.z));
	
    f32 C = pow(o.x - m_center.x, 2) + pow(o.y - m_center.y, 2)
            + pow(o.z - m_center.z, 2) - pow(m_radius, 2);

	// Calculate the value under the square root in the quadratic formula
	f32 squareRootCheck = pow(B, 2) - (4 * C);
    if (squareRootCheck < 0.0f) {
		return false;
	}
	// Calculate the quadratic formula
	f32 wAdd = (-B + sqrt(squareRootCheck)) / 2;
	f32 wSub = (-B - sqrt(squareRootCheck)) / 2;

	// determine the least square root
	f32 leastPos;

    if ((wAdd < 0.0f) && (wSub < 0.0f)) {
		return false;
	} 
    else if (wSub < 0.0f) {
		leastPos = wAdd;
	}
    else if (wAdd < 0.0f) {
		leastPos = wSub;
	}
	else {
		leastPos = wAdd <= wSub ? wAdd : wSub;
	}

	// Calculate intersection and normal
	id.intersection = (o + (d * leastPos));
	id.intersection.w = 1.0;
    id.normal = glm::normalize(id.intersection - m_center);
	id.ray = r;
	return true;
}

void Sphere::transform(const glm::mat4 &transformation) {
    m_center = transformation * m_center;
}

bool Polygon::intersect(const Ray &r, IntersectData &id) {
    for (u64 i = 0; i < m_vertecies.size(); i += 3) {
        // The vertices of the triangle
        glm::vec3 p0 = glm::vec3(m_vertecies[m_connections[i]]);
        glm::vec3 p1 = glm::vec3(m_vertecies[m_connections[i + 1]]);
        glm::vec3 p2 = glm::vec3(m_vertecies[m_connections[i + 2]]);

        glm::vec3 e1 = p1 - p0;
        glm::vec3 e2 = p2 - p0;
        glm::vec3 T = glm::vec3(r.origin) - p0;
        glm::vec3 P = glm::cross(glm::vec3(r.direction), e2);
        glm::vec3 Q = glm::cross(T, e1);

        if (glm::dot(P, e1) > 0.0f) {
            continue;
        }
        glm::vec3 tuv = (1 / (glm::dot(P, e1))) *
            glm::vec3(glm::dot(Q, e2), glm::dot(P, T),
                    glm::dot(Q, glm::vec3(r.direction)));
        f32 t = tuv.x;
        f32 u = tuv.y;
        f32 v = tuv.z;
        if (t < 0.0f) {
            continue;
        }
        else if ((u < 0.0f) || (v < 0.0f) || (u + v > 1.0f)) {
            continue;
        }
	
        id.u_coord = u;
        id.v_coord = v;

        id.intersection = r.origin + t * r.direction;
        id.normal = glm::vec4(glm::cross(e1, e2), 0.0);
        id.normal.w = 0.0;
        id.triangle_points[0] = glm::vec4(p0, 1.0);
        id.triangle_points[1] = glm::vec4(p1, 1.0);
        id.triangle_points[2] = glm::vec4(p2, 1.0);
        if (id.normal.y < 0.0f)
            id.normal = -id.normal;
        id.normal = glm::normalize(id.normal);
        id.ray = r;

        return true;
    }

    return false;
}

void Polygon::transform(const glm::mat4 &transformation) {
    for (auto &point : m_vertecies) {
        point = transformation * point;
    }
}




