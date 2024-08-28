/// Modified from
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <cmath>
#include <ngl/Vec3.h>

#include "rtweekend.h"
#include "camera.h"
#include "RGBA.h"

class hitRecord;

class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, RGBA& attenuation, Ray& scattered) = 0;

    inline ngl::Vec3 unitVector(ngl::Vec3 v)
    {
        return v / v.length();
    }

    static ngl::Vec3 randomVec()
    {
        return ngl::Vec3(randomDouble(), randomDouble(), randomDouble());
    }

    static ngl::Vec3 randomVec(double min, double max)
    {
        return ngl::Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }

    inline ngl::Vec3 randomInUnitTriangle()
    {
        while (true)
            {
                auto p = randomVec(-1,1);
                if (p.lengthSquared() < 1)
                    return p;
            }
    }

    inline ngl::Vec3 randomUnitVector()
    {
        return unitVector(randomInUnitTriangle());
    }

    inline ngl::Vec3 randomOnTriangle(const ngl::Vec3& normal)
    {
        ngl::Vec3 onUnitTriangle = randomUnitVector();
        if (onUnitTriangle.dot(normal) > 0.0)
            return onUnitTriangle;
        else
            return -onUnitTriangle;
    }

    ngl::Vec3 reflect(const ngl::Vec3& v, const ngl::Vec3& n)
    {
        return v - 2*v.dot(n)*n;
    }

    inline ngl::Vec3 refract(const ngl::Vec3& uv, const ngl::Vec3& n, double etai_over_etat)
    {
           auto cosTheta = fmin(-uv.dot(n), 1.0);
           ngl::Vec3 r_out_perp = etai_over_etat * (uv + cosTheta*n);
           ngl::Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.lengthSquared())) * n;
           return r_out_perp + r_out_parallel;
    }

    inline ngl::Vec3 randomInUnitDisk()
    {
           while(true)
               {
               auto p = ngl::Vec3(randomDouble(-1,1), randomDouble(-1,1), 0);
               if (p.lengthSquared() < 1)
                   return p;
               }
    }
};

class Lambertian : public Material
{
public:
    Lambertian(const RGBA& a) : albedo(a) {}

     bool nearZero(const ngl::Vec3 & v, double s = 1e-8)
    {
        return (fabs(v.m_x) < s) &&
               (fabs(v.m_y) < s) &&
               (fabs(v.m_z) < s);
    }

    bool scatter(const Ray& r_in, const HitRecord& rec, RGBA& attenuation, Ray& scattered)
    {
        auto scatterDir = rec.normal + randomUnitVector();

        if (nearZero(scatterDir))
            scatterDir = rec.normal;

        scattered = Ray(rec.p, scatterDir);
        attenuation = albedo;
        return true;
    }
private:
    RGBA albedo;
};

class Metal : public Material
{
public:
    Metal(const RGBA& a) : albedo(a) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, RGBA& attenuation, Ray& scattered)
    {
        ngl::Vec3 reflected = reflect(unitVector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p,reflected);
        attenuation = albedo;
        return true;
    }
private:
    RGBA albedo;
};

class Dielectric : public Material
{
public:
    Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, RGBA& attenuation, Ray& scattered)
    {
        attenuation = RGBA(255,255,255,255);
        double refractionRatio = rec.frontFace ? (1.0/ir) : ir;

        ngl::Vec3 unitDirection = unitVector(r_in.direction());
        double cosTheta = fmin(-unitDirection.dot(rec.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        ngl::Vec3 direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
            direction = reflect(unitDirection, rec.normal);
        else
            direction = refract(unitDirection, rec.normal, refractionRatio);

        scattered = Ray(rec.p, direction);
        return true;
    }
    private:
    double ir;

    static double reflectance(double cosine, double ref_idx)
    {
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};
#endif