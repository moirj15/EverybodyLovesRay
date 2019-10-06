#include <cstdio>
#include <cstdlib>
#include "utils.h"
#include "bmpIO.h"
#include "object.h"
#include "camera.h"
#include "illumination.h"
#include <chrono>
#include <iostream>

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
    auto start = std::chrono::high_resolution_clock::now();

    Scene scene;

    scene.lights.push_back(Light(glm::vec4(0.97, 3.00, 9.5, 1.0),
								glm::vec4(1.0, 1.0, 1.0, 1.0),
								glm::vec4(1.0, 1.0, 1.0, 1.0)));

    glm::vec4 ambientMat(1.0, 1.0, 1.0, 1.0);
    glm::vec4 diffuseMat(1.0, 1.0, 1.0, 1.0);
    glm::vec4 specularMat(1.0, 1.0, 1.0, 1.0);

    Phong sphereIllum1(0.0, 0.5, 0.5, 70.0, 0.0, 0.0, ambientMat, diffuseMat,
            specularMat);
    Phong sphereIllum2(0.0, 0.5, 0.5, 70.0, 0.5, 0.0, ambientMat, diffuseMat,
            specularMat);

	glm::vec4 color1(1.0, 0.0, 0.0, 0.0);
	glm::vec4 color2(1.0, 1.0, 0.0, 0.0);

    CheckerBoard floorIllum(0.5, 0.5, 0.5, 70.0, 0.0, 0.0, color1, color2);

    scene.objects.push_back(new Sphere(glm::vec4(1.49, -1.31, 5.70, 1.0), 1.00, &sphereIllum1));

    std::vector<glm::vec4> triangles;

    triangles.push_back(glm::vec4(15.8, -1.90, 7.69, 0.0));
    triangles.push_back(glm::vec4(-4.6, -1.90, 8.69, 0.0));
    triangles.push_back(glm::vec4(-4.6, -1.90, -18.69, 0.0));

    triangles.push_back(glm::vec4(15.8, -1.90, 7.69, 0.0));
    triangles.push_back(glm::vec4(2.8,  -1.90, -19.00, 0.0));
    triangles.push_back(glm::vec4(-4.6, -1.90, -18.69, 0.0));

    std::vector<u32> connections({0, 1, 2, 3, 4, 5});
	
    scene.objects.push_back(new Polygon(&floorIllum, triangles, connections));

    scene.objects.push_back(new Sphere(glm::vec4(2.93, -2.00, 4.21, 1.0), 0.8f, &sphereIllum2));

    Camera camera(glm::vec3(1.67, -1.28, 7.37), glm::vec3(0.0, 0.0, -1.0),
                glm::vec3(0.0, 1.0, 0.0), glm::vec2(16.0f, 9.0f));

    for (auto *object : scene.objects) {
        object->transform(camera.matrix());
    }

    ScreenBuffer *screenBuffer = new ScreenBuffer(1920, 1080);

    camera.render(scene, screenBuffer);

    writeBMP("test.bmp", screenBuffer);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
    return EXIT_SUCCESS;
}
