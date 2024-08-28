/// Modified from
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <limits>

class Interval
        {
        public:
            double min, max;

            Interval() : min(std::numeric_limits<double>::infinity()), max(-std::numeric_limits<double>::infinity()) {}

            Interval(double _min, double _max) : min(_min), max(_max) {}

            bool contains(double x) const
            {
                return min <= x && x <= max;
            }

            bool surrounds(double x) const
            {
                return min < x && x <= max;
            }

            double clamp(double x) const
            {
                if (x < min) return min;
                if (x > max) return max;
                return x;
            }
        };

const static Interval empty (std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
const static Interval universe (-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());

#endif