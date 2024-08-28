/// The following section was originally written as part of our ASE lab by Jon Macey modified by me

#ifndef IMAGE_H_
#define IMAGE_H_

#include <memory>
#include <string_view>

#include "RGBA.h"

class Image
{
public :
    Image()=default;
    Image(int _w, int _h);
    Image(int _w, int _h,unsigned char _r,unsigned char _g, unsigned char _b,unsigned char _a=255);
    void setSize(int image_width);
    [[nodiscard]] int width() const noexcept;
    [[nodiscard]] int height() const noexcept;
    [[nodiscard]] RGBA * pixels() noexcept;
    [[nodiscard]] RGBA getPixel(int _x, int _y) const noexcept;
    void setPixel(int _x, int _y, unsigned char _r, unsigned char _g,
                   unsigned char _b, unsigned char _a=255);
    void writeColor(std::ostream &out, const RGBA &pixelColor, int samplesaPerPixel);
    bool save(std::string_view fname) const;
private :
    int m_width=0;
    int m_height=0;
    int m_x;
    int m_y;
    std::unique_ptr<RGBA []> m_pixels;
};

#endif