#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <vector>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/component_wise.hpp>

#include "common.h"

struct Window {
    SDL_Window *sdl_window;
    SDL_Texture *sdl_texture;
    SDL_Renderer *sdl_renderer;

    s32 width;
    s32 height;

    /**
     * Constructor
     *
     * @param w: The width.
     * @param h: The height.
     */
    Window(s32 w, s32 h) : sdl_window(nullptr), sdl_texture(nullptr),
        sdl_renderer(nullptr), width(w), height(h) {

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "ERR: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        
		sdl_window = SDL_CreateWindow("ray", SDL_WINDOWPOS_UNDEFINED,
		                        SDL_WINDOWPOS_UNDEFINED, width, height,
		                        SDL_WINDOW_SHOWN);

	    if (!sdl_window) {
            fprintf(stderr, "ERR: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
	    }

	    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);

	    if (!sdl_renderer) {
            fprintf(stderr, "ERR: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
	    }

	    sdl_texture = SDL_CreateTexture(sdl_renderer,
		                            SDL_PIXELFORMAT_ARGB8888,
		                            SDL_TEXTUREACCESS_STATIC, w, h);

	    if (!sdl_texture) {
            fprintf(stderr, "ERR: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
	    }
    }

    /**
     * Destructor
     */
    ~Window() {
        SDL_DestroyRenderer(sdl_renderer);
        SDL_DestroyTexture(sdl_texture);
        SDL_DestroyWindow(sdl_window);
    }

    /**
     * Update the window by drawing the given screen buffer to it
     *
     * @param screen_buffer: The screen buffer that will be drawn.
     */
    void update(u32 *screen_buffer) {
        SDL_UpdateTexture(sdl_texture, nullptr, screen_buffer, width * (s32)sizeof(s32));
        SDL_RenderClear(sdl_renderer);
        SDL_RenderCopy(sdl_renderer, sdl_texture, nullptr, nullptr);
        SDL_RenderPresent(sdl_renderer);
    }
};

struct Ray {
    glm::vec4 origin;
    glm::vec4 direction;

    Ray() = default;
    Ray(const glm::vec4 &o, const glm::vec4 &d) : origin(o), direction(d) {}
};

struct Material {
    const f32 ambientCoefficient;
    const f32 diffuseCoefficient;
    const f32 specularCoefficient;
    const f32 specularExponent;
    const glm::vec3 diffuseMaterial;
    const glm::vec3 specularMaterial;

    Material() = default;
    Material(f32 ac, f32 dc, f32 sc, f32 se, glm::vec3 dm, glm::vec3 sm) :
        ambientCoefficient(ac), diffuseCoefficient(dc), specularCoefficient(sc),
        specularExponent(se), diffuseMaterial(dm), specularMaterial(sm) {}
};

struct Sphere {
    glm::vec4 center;
    f32 radius;
    // TODO: make this a handle
//    Material material;

    Sphere() = default;
    Sphere(const glm::vec4 &c, f32 r) :
        center(c), radius(r){}
};

struct Triangle {
    glm::vec4 v0;
    glm::vec4 v1;
    glm::vec4 v2;
    // TODO: make this a handle
//    Material material;

    Triangle() = default;
    Triangle(const glm::vec4 &p0, const glm::vec4 &p1, const glm::vec4 &p2) :
        v0(p0), v1(p1), v2(p2) {}
};

struct Camera {
    glm::vec3 position;
    glm::vec3 lookat;
    glm::vec3 up;

    glm::mat4 camera_matrix;

    s32 width;
    s32 height;

    f32 lens_distance;

    const f32 film_height = 9.0f;
    const f32 film_width = 16.0f;

    Camera() = default;

    Camera(const glm::vec3 &p, const glm::vec3 &l, const glm::vec3 &u, 
        s32 w, s32 h, f32 ld) :
        position(p), lookat(l), up(u), camera_matrix(glm::lookAt(p, l, u)),
        width(w), height(h), lens_distance(ld) {}

};

struct Light {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 ambientColor;

    Light(const glm::vec3 &p, const glm::vec3 &c, const glm::vec3 &a) :
        position(p), color(c), ambientColor(a) {}
};


struct Scene {
    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
    std::vector<Light> lights;
};

inline u32 vec3ToU32(const glm::vec3 &vec) {
    u32 tmp =  ((u32)(vec.r * 255) << 16) | ((u32)(vec.g * 255) << 8) | ((u32)(vec.b * 255));
    return tmp;
}

/**
 * Performs an intersection test between a sphere and a ray.
 * @param sphere - The sphere we're testing.
 * @param ray - The ray we're testing.
 * @param intersect - The intersection point if it exists.
 * @param normal - The normal at the intersection point if it exists.
 * @param distance - The length of the ray.
 * @return - True if an intersection was found, false otherwise.
 */
bool intersect_test(const Sphere &sphere, const Ray &ray, 
        glm::vec4 *intersect, glm::vec4 *normal, f32 *distance) {
    f32 B = 2.0f * glm::compAdd(ray.direction * (ray.origin - sphere.center));
    f32 C = glm::compAdd(glm::pow(ray.origin - sphere.center, glm::vec4(2.0f))) 
        - powf(sphere.radius, 2.0f);

    f32 val_under_root = powf(B, 2.0f) - (4.0f * C);
    if (val_under_root < 0.0f) {
        return false;
    }

    if (val_under_root == 0.0f) {
        f32 w = (-B + val_under_root) / 2.0f;
        *intersect = ray.origin + (ray.direction * w);
        *normal = *intersect - sphere.center;
        *distance = w;
        return true;
    }
    f32 wAdd = (-B + sqrt(val_under_root)) / 2.0f;
    f32 wSub = (-B - sqrt(val_under_root)) / 2.0f;
    if (wAdd <= 0.0f) {
        *intersect = ray.origin + (ray.direction * wSub);
        *normal = *intersect - sphere.center;
        *distance = wSub;
        return true;
    }
    else if (wSub <= 0.0f) {
        *intersect = ray.origin + (ray.direction * wAdd);
        *normal = *intersect - sphere.center;
        *distance = wAdd;

        return true;
    }
    else if (wAdd < wSub) {
        *intersect = ray.origin + (ray.direction * wAdd);
        *normal = *intersect - sphere.center;
        *distance = wAdd;
        return true;
    }
    // wSub < wAdd
    else {
        *intersect = ray.origin + (ray.direction * wSub);
        *normal = *intersect - sphere.center;
        *distance = wSub;

        return true;
    }
}

/**
 * Performs an intersection test between a triangle and a ray.
 * @param triangle - The triangle we're testing.
 * @param ray - The ray we're testing.
 * @param intersect - The intersection point if it exists.
 * @param normal - The normal at the intersection point if it exists.
 * @param distance - The length of the ray.
 * @return - True if an intersection was found, false otherwise.
 */
bool intersect_test(Triangle triangle, Ray ray, glm::vec4 *intersect,
        glm::vec4 *normal, f32 *distance) {
    glm::vec3 e1 = glm::vec3(triangle.v1 - triangle.v0);
    glm::vec3 e2 = glm::vec3(triangle.v2 - triangle.v0);
    glm::vec3 T = glm::vec3(ray.origin - triangle.v0);
    glm::vec3 P(glm::cross(glm::vec3(ray.direction), e2));
    glm::vec3 Q(glm::cross(T, e1));

    if (glm::dot(P, e1) == 0.0f) {
        return false;
    }

    glm::vec3 tuv = (1.0f / (glm::dot(P, e1))) * glm::vec3(glm::dot(Q, e2),
            glm::dot(P, T), glm::dot(Q, glm::vec3(ray.direction)));

    
    if ((tuv.x < 0.0f) || (tuv.y < 0.0f) || (tuv.z < 0.0f) || 
            (tuv.y + tuv.z > 1.0f)) {
        return false;
    }

    *intersect = ray.origin + tuv.x * ray.direction;
    *normal = glm::vec4(cross(e1, e2), 0.0f);
    *distance = tuv.x;
    return true;
}


/**
 * Perform intersection tests on a vector objects (Spheres or Triangles) and
 * finds the intersection with the shortest ray length.
 * @param objects - The objects we'll be testing.
 * @param ray - The ray we're testing.
 * @param intersect - The intersection point if it exists.
 * @param normal - The normal, if the intersection occurs.
 * @param distance - The length of the ray.
 * @return - True if an intersection occured, false otherwise.
 */
template <typename T>
bool intersectObjects(const std::vector<T> &objects, const Ray &ray,
        glm::vec4 *intersect, glm::vec4 *normal, f32 *distance) {
    f32 nearest = INFINITY;
    f32 curr_distance = INFINITY;
    for (const auto &object : objects) {
        if (intersect_test(object, ray, intersect, normal, &curr_distance)) {
            if (curr_distance < nearest) {
                nearest = curr_distance;
            }
        }
    }
    if (curr_distance == INFINITY) {
        return false;
    }
    *distance = nearest;
    return true;
}

inline glm::vec3 calculatePhongLighting(const Light &light, const Material &material,
                                        const glm::vec4 &normal, const glm::vec4 &surfToLight,
                                        const glm::vec4 &reflectionVec, const glm::vec4 &viewVec) {
    glm::vec3 diffuse = light.color * material.diffuseCoefficient * material.diffuseMaterial *
                fmaxf(0.0, glm::dot(normal, surfToLight));
    glm::vec3 specular  = light.color * material.specularCoefficient *
            material.specularMaterial
            * powf(fmaxf(glm::dot(reflectionVec, viewVec), 0.0), material.specularExponent);
    return light.ambientColor + diffuse + specular;
}

u32 castReflectionRay(Camera *camera, const Scene &scene, const Material &material,
                      const glm::vec4 &normal, const glm::vec4 &intersection) {
    glm::vec3 color{};
    for (const auto &light : scene.lights) {
        auto surfToLight = glm::normalize(glm::vec4(light.position, 1.0) - intersection);
        auto viewVec = glm::normalize(glm::vec4(camera->position, 1.0) - intersection);
        auto reflectionvec = glm::normalize(glm::reflect(-surfToLight, normal));
        glm::vec4 junkIntersect{}, junkNormal{};
        f32 distance = 0.0;
        if (intersectObjects(scene.spheres, Ray(intersection, glm::vec4(light.position, 1.0) - intersection), &junkIntersect,
                             &junkNormal, &distance) ||
                intersectObjects(scene.triangles, Ray(intersection + glm::vec4(0.0f, 0.0f, 0.0001f, 1.0f), glm::vec4(light.position, 1.0) - intersection), &junkIntersect,
                                    &junkNormal, &distance)) {
            color += light.ambientColor;
        } else { // not in shadow
            color += calculatePhongLighting(light, material, normal, surfToLight, reflectionvec,
                                            viewVec);
        }
    }
    return vec3ToU32(glm::clamp(color, glm::vec3(0.0f), glm::vec3(1.0f)));
}


/**
 *
 * @param screen_buffer
 * @param camera
 * @param spheres
 * @param triangles
 */
void castRays(u32 *screen_buffer, Camera *camera, const Scene &scene) {
    glm::mat4 inv_cam = inverse(camera->camera_matrix);
    Material triangleMaterial{1.0, 1.0, 1.0, 1.0, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    Material sphereMaterial{0.5, 0.3, 0.9, 1.0, {0.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

    for (s32 y = 0; y < camera->height; y++) {
        f32 y_origin = (camera->film_height / 2.0f) - 
            ((f32)y * (camera->film_height / (f32)camera->height));
        for (s32 x = 0; x < camera->width; x++) {
            f32 x_origin = (-camera->film_width / 2.0f) + 
                ((f32)x * (camera->film_width / (f32)camera->width));

            auto direction = inv_cam * glm::vec4(x_origin, y_origin, 
                                             -camera->lens_distance, 0.0f);
            auto origin = inv_cam * glm::vec4(camera->position, 1.0f);
            Ray ray(glm::normalize(origin), glm::normalize(direction));

            glm::vec4 sphere_intersect(0.0f);
            glm::vec4 sphere_normal(0.0f);

            glm::vec4 tri_intersect(0.0f);
            glm::vec4 tri_normal(0.0f);

            f32 sphere_distance = 0.0f;
            f32 tri_distance = 0.0f;

            bool hit_sphere = intersectObjects(scene.spheres, ray, &sphere_intersect,
                    &sphere_normal, &sphere_distance);

            bool hit_triangle = intersectObjects(scene.triangles, ray, &tri_intersect,
                    &tri_normal, &tri_distance);
            
            if (hit_sphere && hit_triangle) {
                if (sphere_distance < tri_distance) {
                    screen_buffer[(y * camera->width) + x] = // TODO: need to get the material from something
                            castReflectionRay(camera, scene, sphereMaterial, sphere_normal, sphere_intersect);
                }
                else {
                    screen_buffer[(y * camera->width) + x] = //0x00ffffff;
                            castReflectionRay(camera, scene, triangleMaterial, tri_normal, tri_intersect);
                }
            }
            else if (hit_sphere) {
                screen_buffer[(y * camera->width) + x] = //0x00ff0000;
                        castReflectionRay(camera, scene, sphereMaterial, sphere_normal, sphere_intersect);
            }
            else if (hit_triangle) {
                screen_buffer[(y * camera->width) + x] = //0x00ffffff;
                        castReflectionRay(camera, scene, triangleMaterial, tri_normal, tri_intersect);
            }
            else {
                screen_buffer[(y * camera->width) + x] = 0x00000000;
            }
        }
    }
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

    constexpr s32 width = 1080;
    constexpr s32 height = 720;
    u32 *screenBuffer = new u32[width * height]();
    Window window(width, height);

    //Sphere sphere(glm::vec4(0.0f, 0.0f, -2.1f, 1.0f), 1.0f);
    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                glm::vec3(0.0f, 1.0f, 0.0f), width, height, 1.0f);

    Triangle tri(
            glm::vec4(-1.0f, 0.0f, -1.5f, 1.0f),
            glm::vec4(1.0f, 0.0f, -1.5f, 1.0f),
            glm::vec4(0.0f, 1.0f, -1.5f, 1.0f));

    Light light({0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.0f, 0.0f});

//    castRays(screenBuffer, &camera, {{sphere}, {tri}, {light}});
    castRays(screenBuffer, &camera, {{}, {tri}, {light}});
    window.update(screenBuffer);
    printf("done\n");

    bool running = true;
    while (running) {
        printf("done\n %f\n", light.position.z);
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        memset(screenBuffer, 0, sizeof(u32) * width * height);
        light.position.z += 10.0;
        castRays(screenBuffer, &camera, {{}, {tri}, {light}});
        window.update(screenBuffer);
    }
	
    delete[](screenBuffer);
	return EXIT_SUCCESS;
}
