/// Modified from
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "Ray.h"
#include "rtweekend.h"

class Material;

class HitRecord
{
public:
    ngl::Vec3 p;
    ngl::Vec3 normal;
    std::shared_ptr<Material> mat;
    double t;
    bool frontFace;

    void setFaceNormal(const Ray& r, ngl::Vec3& outwardNormal)
    {
        frontFace = r.direction().dot(outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) = 0;
};

#endif