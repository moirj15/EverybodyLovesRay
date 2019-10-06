#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "utils.h"
#include "illumination.h"

struct Object;

struct Scene {
    std::vector<Light> lights;
    std::vector<Object*> objects;
};

struct ScreenBuffer {
    u32 *buffer;
    s32 width;
    s32 height;

    ScreenBuffer(s32 w, s32 h) :
        buffer(new u32[(size_t)w * (size_t)h]), width(w), height(h) {}
    ~ScreenBuffer() { if (buffer) { delete[](buffer); } }
};

class Camera
{

    glm::vec3 m_pos;
    glm::vec3 m_lookAt;
    glm::vec3 m_up;

    glm::vec2 m_aspectRatio;
    f32	m_f;
    glm::mat4 m_camTransform;



public:

    Camera(const glm::vec3 &pos, const glm::vec3 &lookAt, const glm::vec3 &up,
           const glm::vec2 &aspectRatio) :
        m_pos(pos), m_lookAt(lookAt), m_up(up), m_aspectRatio(aspectRatio), m_f(pos.z),
        m_camTransform(glm::lookAt(m_pos, m_lookAt, m_up)) {}

    ~Camera(void) = default;

    void render(const Scene &scene, ScreenBuffer *screenBuffer);
    s32 intersection(Ray ray, IntersectData &data, s32 check_obj, const Scene &scene);

    inline glm::mat4 matrix() const { return m_camTransform; }

private:
    glm::vec4 calculateLight(IntersectData &id, IlluminationModel *illuminationModel,
            std::vector<Light> lights, s32 obj, u32 depth, const Scene &scene);

    bool inShadow(IntersectData &id, Light light, s32 obj, const Scene &scene);

};


#endif
