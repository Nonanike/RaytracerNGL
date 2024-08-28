/// Modified from
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef RTWEEKEND_H_
#define RTWEEKEND_H_

#include <cmath>
#include <cstdlib>
#include <memory>
#include <ngl/Vec3.h>
#include <limits>

#include "interval.h"
#include "Ray.h"
#include "RGBA.h"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double randomDouble()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max)
{
    return min + (max-min) * randomDouble();
}

#endif