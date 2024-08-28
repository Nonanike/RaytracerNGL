/// The following section was originally written as part of our ASE lab by Jon Macey and modified by me

#include <ngl/Vec3.h>
#include <OpenImageIO/imageio.h>

#include "Image.h"
#include "interval.h"

Image::Image(int _w, int _h) : m_width{_w}, m_height{_h}
{
    m_pixels=std::make_unique<RGBA []>(m_width*m_height);
}

Image::Image(int _w, int _h,unsigned char _r,unsigned char _g, unsigned char _b,unsigned char _a) : Image(_w,_h)
{
    m_pixels=std::make_unique<RGBA []>(m_width*m_height);
    for(int i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i].set(_r,_g,_b,_a);
    }
}

int Image::width() const noexcept
{
    return m_width;
}

int Image::height() const noexcept
{
    return m_height;
}

RGBA * Image::pixels() noexcept
{
return m_pixels.get();
}

RGBA Image::getPixel(int _x, int _y) const noexcept
{
return m_pixels[(m_width*_y) + _x];
}

void Image::setPixel(int _x, int _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
m_pixels[(m_width*_y) + _x].set(_r,_g,_b,_a);
}

/// This function was written and added by me
void Image::setSize(int image_width)
{
    m_width = image_width;
    m_height = (9*m_width)/16;
    m_pixels=std::make_unique<RGBA []>(m_width*m_height);
}
/// End of function

///Those functions were modified from :-
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

inline double linearToGamma(double linearComponent)
{
        return sqrt(linearComponent);
}

void Image::writeColor(std::ostream &out, const RGBA &pixelColor, int samplesPerPixel)
{
    auto r = pixelColor.r;
    auto g = pixelColor.g;
    auto b = pixelColor.b;
    auto a = pixelColor.a;

    auto scale = 1.0 / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    static const Interval intensity(0.000, 0.999);
    std::cout << static_cast<unsigned>(intensity.clamp(r)) << ' '
        << static_cast<unsigned>(intensity.clamp(g)) << ' '
        << static_cast<unsigned>(intensity.clamp(b)) << ' '
        << static_cast<unsigned>(intensity.clamp(a)) << '\n';
}

/// End of Citation

bool Image::save(std::string_view fname) const
{
    using namespace OIIO;
    bool success=false;
    auto out = ImageOutput::create(fname.data());
    if(!out)
    {
        return false;
    }
    ImageSpec spec(m_width,m_height,4,TypeDesc::UINT8);
    success = out->open(fname.data(),spec);
    success = out->write_image(TypeDesc::UINT8,m_pixels.get());
    success = out->close();

    return success;
}
