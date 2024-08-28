/// Modified from :-
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdlib>
#include <iostream>
#include <ngl/Vec3.h>

#include "hittable.h"
#include "hittable_list.h"
#include "Image.h"
#include "interval.h"
#include "Ray.h"
#include "RGBA.h"
#include "rtweekend.h"
#include "triangle.h"

class Camera
{
public:

    int samplesPerPixel = 10;
    int maxDepth;

    double vfov = 90;
    ngl::Vec3 lookFrom = ngl::Vec3(0,0,-1);
    ngl::Vec3 lookAt = ngl::Vec3(0,0,0);
    ngl::Vec3 vup = ngl::Vec3(0,1,0);

    void initilize()
    {
        m_image.setSize(1280);
        
        origin = lookFrom;

        double focal_length = (lookFrom - lookAt).length();
        double theta = degreesToRadians(vfov);
        double h = tan(theta/2);
        double viewport_height = 2.0 * h * focal_length;
        double viewport_width = (16*viewport_height)/9;
        
        w = unitVector(lookFrom - lookAt);
        u = unitVector(vup.cross(w));
        v = w.cross(u);

        viewport_u = viewport_width * u;
        viewport_v = viewport_height * -v;

        pixel_delta_u = viewport_u / m_image.width();
        pixel_delta_v = viewport_v / m_image.height();


        auto viewport_upper_left = origin -(focal_length * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    }

    RGBA rayColor(const Ray& r, int depth, Hittable& world)
    {
        HitRecord rec;

        if (depth <= 0)
            return RGBA(0,0,0,255);

        if (world.hit(r, 0.001, infinity, rec))
            {
                Ray scattered;
                RGBA attenuation;
                if(rec.mat->scatter(r,rec,attenuation,scattered))
                    return attenuation * rayColor(scattered, depth-1, world);
                return RGBA(0,0,0,255);
            }

        ngl::Vec3 unitDirection = unitVector(r.direction());
        double t1 = 0.5*(unitDirection.m_y + 1.0);
        std::cout<<"t = " << t1 << "\n";
        return RGBA(255,255,255,255)*(1.0-t1) + RGBA(128,220,255,255)*t1;

    }

    void render(Hittable& world)
    {
        m_image.setSize(1280);

        std::cout << "P3\n" << m_image.width() << " " << m_image.height() << "\n255\n";

        for (int j = 0; j < m_image.height(); ++j)
        {
            std::cerr << "\rScanlines remaining: " << (m_image.height() - j) << " " << std::flush;
            for (int i = 0; i < m_image.width(); ++i)
            {
                auto pixel_center = pixel00_loc + ( i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - origin;
                Ray r(origin, ray_direction);

                RGBA pixelColor = rayColor(r, maxDepth, world);

                m_image.setPixel(i,j, pixelColor.r,pixelColor.g,pixelColor.b,pixelColor.a);
                m_image.writeColor(std::cout, pixelColor, samplesPerPixel);
            }
        }
        std::cerr << "\nDone.\n";

        m_image.save("test_2.png");

    }
private:
    ngl::Vec3 viewport_u;
    ngl::Vec3 viewport_v;
    ngl::Vec3 pixel00_loc;
    ngl::Vec3 pixel_delta_u;
    ngl::Vec3 pixel_delta_v;
    ngl::Vec3 u, v, w;

    ngl::Vec3 origin = ngl::Vec3( 0,0,0);

    ngl::Vec3 pixelSampleSquare() const
    {
        auto px = -0.5 + randomDouble();
        auto py = -0.5 + randomDouble();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

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

    Image m_image;
};

#endif