/// Modified from :-
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef RAY_H_
#define RAY_H_

#include <ngl/Vec3.h>

class Ray {
public:
    Ray() {}
    Ray(const ngl::Vec3& origin, const ngl::Vec3& direction)
        : orig(origin), dir(direction) {}

    ngl::Vec3 origin() const { return orig; }
    ngl::Vec3 direction() const { return dir; }

    ngl::Vec3 at(double t) const
    {
        return orig + t*dir;
    }
private:
    ngl::Vec3 orig;
    ngl::Vec3 dir;

};
#endif