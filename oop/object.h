#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "utils.h"
#include "ray.h"
#include "intersectData.h"
#include "illumination.h"
#include <array>


// Object abstract class
class Object  {
    IlluminationModel 	*m_illuminationModel;
public:

    Object (IlluminationModel *i) :
        m_illuminationModel(i) {}

	/**
	 * Virtual destructor.
	 */
    virtual ~Object(void) { if (m_illuminationModel) { delete(m_illuminationModel); } }

	/**
	 * Checks for the intersection of an object with the given ray, if there is
	 * an intersection then the params intersection and normal will have their
	 * contents modified.
	 *
	 * @param r: The ray that will be checked for intersection.
	 * @param intersection: The reference to the vector that will hold the 
	 * intersection point if there is an intersection.
	 * @param normal: The reference to the vector that will hold the surface
	 * normal if there is an intersection.
	 * @return: True if the object was intersected, false otherwise.
	 */
	virtual bool intersect(const Ray &r, IntersectData &id) = 0;

    virtual void transform(const glm::mat4 &transformation) = 0;
	
};

class Sphere : public Object {
    glm::vec4 m_center;
    f32 m_radius;
public:

    Sphere(glm::vec4 c, f32 r, IlluminationModel *i) :
        Object(i),
        m_center(c),
        m_radius(r) {}

	/**
	 * Checks for the intersection of an object with the given ray, if there is
	 * an intersection then the params intersection and normal will have their
	 * contents modified.
	 *
	 * @param r: The ray that will be checked for intersection.
	 * @param intersection: The reference to the vector that will hold the 
	 * intersection point if there is an intersection.
	 * @param normal: The reference to the vector that will hold the surface
	 * normal if there is an intersection.
	 * @return: True if the object was intersected, false otherwise.
	 */
	bool intersect(const Ray &r, IntersectData &id);

    virtual void transform(const glm::mat4 &transformation);
};

class Polygon : public Object {
    // triangles will be stored as groups of 3 vec3s
    std::vector<glm::vec4> m_vertecies;
    std::vector<u32> m_connections;
public:

	/**
	 * Constructor.
	 *
	 * @param v: The list of verticies, triangles will be in groups of 3.
	 * @param n: The normal for the triangle face.
	 */
    Polygon(IlluminationModel *illuminationModel, const std::vector<glm::vec4> &vertecies,
            const std::vector<u32> &connections) :
        Object(illuminationModel),
        m_vertecies(vertecies),
        m_connections(connections) {}


	/**
	 * Checks for the intersection of an object with the given ray, if there is
	 * an intersection then the params intersection and normal will have their
	 * contents modified.
	 *
	 * @param r: The ray that will be checked for intersection.
	 * @param intersection: The reference to the vector that will hold the 
	 * intersection point if there is an intersection.
	 * @param normal: The reference to the vector that will hold the surface
	 * normal if there is an intersection.
	 * @return: True if the object was intersected, false otherwise.
	 */
	bool intersect(const Ray &r, IntersectData &id);

    virtual void transform(const glm::mat4 &transformation);
};
#endif
