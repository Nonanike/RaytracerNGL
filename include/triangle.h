#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <ngl/Vec3.h>

#include <utility>
#include "Material.h"

#include "hittable.h"
#include "Ray.h"

class Triangle : public Hittable
{
public:
    Triangle() = default;
    Triangle(const ngl::Vec3 vertex0,const ngl::Vec3 vertex1,const ngl::Vec3 vertex2, shared_ptr<Material> _material) : v0(vertex0), v1(vertex1), v2(vertex2), mat(_material) {};

///The following sesction is from :-
/// Scratchpixel (2024). Ray-Tracing: Rendering a Triangle: Möller-Trumbore algorithm
/// Avaiable from: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection.html
/// It was modified by me

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec)
    {
        float epsilon = 0.000001;

        ngl::Vec3 edge1 = v1 - v0;
        ngl::Vec3 edge2 = v2 - v0;
        ngl::Vec3 cross_ray_edge2 = r.direction().cross(edge2);
        float det = edge1.dot(cross_ray_edge2);

        if (det < epsilon)
            return false;

        if (fabs(det) < epsilon)
            return false;

        float invDet = 1 / det;

        ngl::Vec3 tvec = r.origin() - v0;

        float u = tvec.dot(cross_ray_edge2) * invDet;
        if ( u < 0 || u > 1 )
            return false;

        ngl::Vec3 qvec = tvec.cross(edge1);
        float v = r.direction().dot(qvec) * invDet;
        if ( v < 0 || u + v > 1)
            return false;

        float tt = edge2.dot(qvec) * invDet;

/// End of function

/// This block of code was modified from :-
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

        rec.t = tt,
        rec.p = r.at(rec.t);
        rec.normal = (edge1.cross(edge2));
        rec.normal.normalize();
        rec.setFaceNormal(r, rec.normal);
        rec.mat = mat;

        return true;
    }
///End of modified block of code
private:
    ngl::Vec3 v0;
    ngl::Vec3 v1;
    ngl::Vec3 v2;
    shared_ptr<Material> mat;
};

#endif