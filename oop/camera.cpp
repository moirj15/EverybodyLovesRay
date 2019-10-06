#include <cmath>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "bmpIO.h"
#include "object.h"

void Camera::render(const Scene &scene, ScreenBuffer *screenBuffer) {
    for (s32 y = 0; y < screenBuffer->height; y++) {
        f32 filmPlanY = (m_aspectRatio.y / 2) - (y * (m_aspectRatio.y / screenBuffer->height));
        for (s32 x = 0; x < screenBuffer->width; x++) {
            f32 filmPlanX = (-m_aspectRatio.x / 2) + (x * (m_aspectRatio.x / screenBuffer->width));
            glm::vec4 direction(filmPlanX, filmPlanY, -m_f, 0.0);

            Ray r(glm::normalize(glm::vec4(m_pos, 1.0)),  glm::normalize(direction));

			IntersectData data;
            s32 obj = intersection(r, data, -1, scene);

			if (obj == -1) {
                screenBuffer->buffer[screenBuffer->width * y + x] = 0xffff0000;
            } else {
                glm::vec4 color = calculateLight(data, scene.objects[obj]->m_illuminationModel, scene.lights, obj, 1, scene);
                screenBuffer->buffer[screenBuffer->width * y + x] = vec4_to_u32(color);
			}
		}
	}
}

s32 Camera::intersection(Ray ray, IntersectData &data, s32 check_obj, const Scene &scene) {
	IntersectData closest_data;
	f32 closest_distance = INFINITY;
	f32 test_distance;
	s32 obj = -1;
    for (u64 i = 0; i < scene.objects.size(); i++) {

		IntersectData curr_data;

        if (scene.objects[i]->intersect(ray, curr_data)) {
            test_distance = glm::distance(glm::vec4(m_pos, 0.0), curr_data.intersection);
			if ((check_obj > -1) && (i == (u64)check_obj)) {
				continue;
			}
			if (test_distance <= closest_distance) {
				closest_distance = test_distance;
				obj = (s32)i;
				closest_data = curr_data;
			}
		}
	}
	data = closest_data;
	return obj;
}

#define MAX_DEPTH	2

glm::vec4 Camera::calculateLight(IntersectData &id, IlluminationModel *i_model, 
        std::vector<Light> lights, s32 obj, u32 depth, const Scene &scene) {
	glm::vec4 color(0.0);
	for (u64 i = 0; i < lights.size(); i++) {
		Light &light = lights[i];

        color += i_model->illuminate(id, light, m_pos, inShadow(id, light, obj, scene));

		if (depth < MAX_DEPTH) {
			if (i_model->reflection_const > 0.0) {
                glm::vec4 surfToLight = glm::normalize( glm::vec4(m_pos, 0.0)- id.intersection);
				glm::vec4 reflectionVec = glm::normalize(-glm::reflect(surfToLight, id.normal));
				reflectionVec.w = 0.0;
				Ray ray(id.intersection, reflectionVec);
				IntersectData data;
                s32 hit_obj = intersection(ray, data, obj, scene);

				if (hit_obj > -1) {
					color += i_model->reflection_const * calculateLight(data, 
                            scene.objects[hit_obj]->m_illuminationModel, lights, hit_obj, depth + 1, scene);
				}
				else {
					color += i_model->reflection_const * glm::vec4(0.0, 0.0, 1.0, 0.0);
				}
			}
			/*
			if (i_model->refraction_const > 0.0) {
				f32 n =i_model->refraction_const; 
			//	f32 neg_check = 1 - (powf(n, 2) * (1 - powf(glm::dot(id.ray.direction, id.normal), 2))) /
			//		powf()

			}*/
		}
	}


	color = glm::clamp(color, glm::vec4(0.0), glm::vec4(1.0));
	return color;
}

bool Camera::inShadow(IntersectData &id, Light light, s32 obj, const Scene &scene) {
	Ray r;
	r.direction = glm::normalize(light.position - id.intersection); 
	r.direction.w = 1.0;
	r.origin = id.intersection;
	r.origin.w = 0.0;

	IntersectData dummy;
    for (u64 i = 0; i < scene.objects.size(); i++) {
		if (obj == (s32)i) {
			continue;
		}
        if (scene.objects[i]->intersect(r, dummy)) {
			return true;
		}
	}
	return false;
}








