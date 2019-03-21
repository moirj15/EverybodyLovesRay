#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/component_wise.hpp>

#include "common.h"
#include "math.h"

class Window {
    SDL_Window *sdl_window;
    SDL_Texture *sdl_texture;
    SDL_Renderer *sdl_renderer;

    s32 width;
    s32 height;

public:
    Window() = default;

    Window(s32 w, s32 h) : sdl_window(NULL), sdl_texture(NULL), 
        sdl_renderer(NULL), width(w), height(h) {

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

    ~Window() {
        SDL_DestroyRenderer(sdl_renderer);
        SDL_DestroyTexture(sdl_texture);
        SDL_DestroyWindow(sdl_window);
    }

    void update(u32 *screen_buffer) {
        SDL_UpdateTexture(sdl_texture, NULL, screen_buffer, width * sizeof(s32));
        SDL_RenderClear(sdl_renderer);
        SDL_RenderCopy(sdl_renderer, sdl_texture, NULL, NULL);
        SDL_RenderPresent(sdl_renderer);
    }
};

struct Ray {
    vec4 origin;
    vec4 direction;

    Ray() = default;
    Ray(const vec4 &o, const vec4 &d) : origin(o), direction(d) {}
};

struct Sphere {
    vec4 center;
    f32 radius;

    Sphere() = default;
    Sphere(const vec4 &c, f32 r) : center(c), radius(r) {}
};

struct Triangle {
    vec4 v0;
    vec4 v1;
    vec4 v2;

    Triangle() = default;
    Triangle(const vec4 &p0, const vec4 &p1, const vec4 &p2) :
        v0(p0), v1(p1), v2(p2) {}
};

struct Camera {
    vec3 position;
    vec3 lookat;
    vec3 up;

    mat4 camera_matrix;

    s32 width;
    s32 height;

    f32 lens_distance;

    Camera() = default;

    Camera(const vec3 &p, const vec3 &l, const vec3 &u, 
        s32 w, s32 h, f32 ld) :
        position(p), lookat(l), up(u), camera_matrix(camera_mat(p, l, u)),
        width(w), height(h), lens_distance(ld) {}

};

bool intersect_sphere(Sphere sphere, Ray ray, vec4 *intersect, vec4 *normal, 
        f32 *distance) {
    f32 B = 2.0f * comp_add(ray.direction * (ray.origin - sphere.center));
    f32 C = comp_add(pow(ray.origin - sphere.center, 2.0f)) 
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
    f32 wAdd = (-B + val_under_root) / 2.0f;
    f32 wSub = (-B - val_under_root) / 2.0f;
    if (wAdd <= 0.0f) {
        *intersect = ray.origin + (ray.direction * wSub);
        *normal = *intersect - sphere.center;
        *distance = wSub;
        return true;
    }

    if (wSub <= 0.0f) {
        *intersect = ray.origin + (ray.direction * wAdd);
        *normal = *intersect - sphere.center;
        *distance = wAdd;

        return true;
    }

    if (wAdd < wSub) {
        *intersect = ray.origin + (ray.direction * wSub);
        *normal = *intersect - sphere.center;
        *distance = wSub;
        return true;
    }

    // wSub > wAdd
    *intersect = ray.origin + (ray.direction * wAdd);
    *normal = *intersect - sphere.center;
    *distance = wAdd;

    return true;

}

bool intersect_triangle(Triangle triangle, Ray ray, vec4 *intersect,
        vec4 *normal, f32 *distance) {
    vec3 e1 = Vec3(triangle.v1 - triangle.v2);
    vec3 e2 = Vec3(triangle.v2 - triangle.v0);
    vec3 T = Vec3(ray.origin - triangle.v0);
    vec3 P(cross(Vec3(ray.direction), Vec3(triangle.v2)));
    vec3 Q(cross(T, Vec3(triangle.v1)));

    if (dot(P, e1) == 0.0f) {
        return false;
    }

    vec3 tuv = (1.0f / (dot(P, e1))) * Vec3(dot(Q, e2),
            dot(P, T), dot(Q, Vec3(ray.direction)));

    if (tuv.x < 0.0f || (tuv.y < 0.0f) || (tuv.z < 0.0f) || 
            (tuv.y + tuv.z > 1.0f)) {
        return false;
    }

    *intersect = ray.origin + tuv.x * ray.direction;
    *normal = Vec4(cross(e1, e2), 0.0f);
    *distance = tuv.x;
    return true;
}

void cast_rays(u32 *screen_buffer, Camera *camera, Sphere sphere) {
    mat4 inv_cam = inverse(camera->camera_matrix);
    constexpr f32 film_height = 9.0f;
    constexpr f32 film_width = 16.0f;
    for (s32 y = 0; y < camera->height; y++) {
        f32 y_origin = (film_height / 2.0f) - 
            ((f32)y * (film_height / (f32)camera->height));
        for (s32 x = 0; x < camera->width; x++) {
            f32 x_origin = (-film_width / 2.0f) + 
                ((f32)x * (film_width / (f32)camera->width));
            auto direction = inv_cam * Vec4(x_origin, y_origin, 
                                             -camera->lens_distance, 0.0f);
            auto origin = inv_cam * Vec4(camera->position, 1.0f);
            Ray ray (origin, normalize(direction));
            vec4 intersect = Vec4(0.0f);
            vec4 normal = Vec4(0.0f);
            f32 distance = 0.0f;
            if (intersect_sphere(sphere, ray, &intersect, &normal, &distance)) {
                screen_buffer[(y * camera->width) + x] = 0x00ff0000;
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
    const s32 width = 1080;
    const s32 height = 720;
    u32 screen_buffer[width * height] = {};
    Window window(width, height);

    Sphere sphere(Vec4(0.0f, 0.0f, -1.1f, 1.0f), 1.0f);
    Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f),
                Vec3(0.0f, 1.0f, 0.0f), width, height, 1.0f);

    cast_rays(screen_buffer, &camera, sphere);
    window.update(screen_buffer);

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
    }

	
	return EXIT_SUCCESS;
}
