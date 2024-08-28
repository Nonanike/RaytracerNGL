/// The following section was originally written as part of our ASE lab by Jon Macey and modified by me

#ifndef RGBA_H_
#define RGBA_H_

#include <algorithm>
#include <math.h>
#include <ngl/Vec3.h>

struct RGBA
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;

    RGBA() = default;
    RGBA(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
    : r{_r}, g{_g}, b{_b}, a{_a} {}

    void set(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
    {
        r=_r;
        g=_g;
        b=_b;
        a=_a;
    }

    void clamp(unsigned char _min, unsigned char _max)
    {
        r=std::clamp(r, _min, _max);
        g=std::clamp(g, _min, _max);
        b=std::clamp(b, _min, _max);
        a=std::clamp(a, _min, _max);
    }

    ///Functions added by me

    RGBA operator*(double _i) const noexcept
    {
        return RGBA(static_cast<unsigned char>(floor(r*_i)),
                    static_cast<unsigned char>(floor(g*_i)),
                    static_cast<unsigned char>(floor(b*_i)),
                    a);
    }

    RGBA operator*(RGBA _rgba) const noexcept
    {
        return RGBA(static_cast<unsigned char>(floor(r*_rgba.r)),
                    static_cast<unsigned char>(floor(g*_rgba.g)),
                    static_cast<unsigned char>(floor(b*_rgba.b)),
                    a);
    }


    RGBA operator+(RGBA _rgba) const
    {
        return RGBA(std::clamp(_rgba.r + r, 0, 255),
                    std::clamp(_rgba.g + g, 0, 255),
                    std::clamp(_rgba.b + b, 0, 255),
                    255);
    }

    RGBA (const ngl::Vec3& _vec)
        : r{static_cast<unsigned char>(_vec.m_x * 255)},
          g{static_cast<unsigned char>(_vec.m_y * 255)},
          b{static_cast<unsigned char>(_vec.m_z * 255)},
          a{255} {}

    RGBA operator+(const ngl::Vec3& _vec) const
    {
        return RGBA(std::clamp(r + static_cast<int>(_vec.m_x * 255), 0, 255),
                    std::clamp(g + static_cast<int>(_vec.m_y * 255), 0, 255),
                    std::clamp(b + static_cast<int>(_vec.m_z * 255), 0, 255),
                    255);
    }

    ///End of the functions added by me
};
#endif