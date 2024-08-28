#include <gtest/gtest.h>
#include "Image.h"

TEST(Image,constructDefault)
{
    Image img;
    EXPECT_EQ(img.width(), NULL);
    EXPECT_EQ(img.height(),NULL);
    EXPECT_EQ(img.pixels(),nullptr);
}

TEST (Image, constructUser)
{
    Image img(16,255,128,12,255);
    EXPECT_EQ(img.width(), 16);
    EXPECT_EQ(img.height(), 9);
    EXPECT_EQ(img.pixels(),nullptr);
}

TEST(Image,getRGBA)
{
//    constexpr int imagesize=10;
    Image img(16,255,128,12,255);
    for(int y=0; y<9; ++y)
    {
        for(int x=0; x<16; ++x)
        {
            auto pixel=img.getPixel(x,y);
            EXPECT_EQ(pixel.r,0);
            EXPECT_EQ(pixel.g,0);
            EXPECT_EQ(pixel.b,0);
            EXPECT_EQ(pixel.a,255);
        }
    }
}

TEST(Image,constructColour)
{
    constexpr int imagesize=10;
    Image img(10,255,128,12,200);
    EXPECT_EQ(img.pixels(), nullptr);
    for(int y=0; y<imagesize; ++y)
    {
        for(int x=0; x<imagesize; ++x)
        {
            auto pixel= img.getPixel(x, y);
            EXPECT_EQ(pixel.r,255);
            EXPECT_EQ(pixel.g,128);
            EXPECT_EQ(pixel.b,12);
            EXPECT_EQ(pixel.a,200);
        }
    }
}

TEST(Image,setPixel)
{
    Image img(16,255,128,12,255);
    img.setPixel(0,0,255,0,0,255);
    auto pixel=img.getPixel(0,0);
    EXPECT_EQ(pixel.r,255);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,255);
    // green test
    img.setPixel(1,0,0,255,0);
    pixel=img.getPixel(1,0);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,255);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,255);
    // green test
    img.setPixel(2,0,0,0,255,128);
    pixel=img.getPixel(2,0);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,255);
    EXPECT_EQ(pixel.a,128);
}

TEST(Image, setSize)
{
    Image img(16,255,128,12,255);
    img.setSize(16);
    EXPECT_EQ(img.width(), NULL);
    EXPECT_EQ(img.height(), (9 * img.width()) / 16);
    EXPECT_EQ(img.pixels(),nullptr);
}

TEST(Image, linearToGamma)
{
    double linearComponent = 0.5;
    double gammaCorrect = linearComponent * linearComponent;
    EXPECT_EQ(gammaCorrect, 0.25);
}

TEST(Image, writeColor)
{
    std::ostringstream out;
    RGBA pixelColor(120, 100, 230, 255);
    int samplesPerPixel = 5;
    constexpr int imagesize=10;
    Image img(16,255,128,12,255);
    img.writeColor(out, pixelColor, samplesPerPixel);
    EXPECT_EQ(pixelColor.r, 576);
    EXPECT_EQ(pixelColor.g, 400);
    EXPECT_EQ(pixelColor.b, 2116);
    EXPECT_EQ(pixelColor.a, 255);

}

TEST(Image,savePNG)
{
    {
        Image img(512,512,255,0,0,255);
        EXPECT_TRUE(img.save("red.png"));
        }
        {
        Image img(512,512,0,255,0,255);
        EXPECT_TRUE(img.save("green.png"));
        }
        {
        Image img(512,512,0,0,255,255);
        EXPECT_TRUE(img.save("blue.png"));
        }
        {
        Image img(512,512,255,0.0,255);
        EXPECT_TRUE(img.save("alpha.png"));
    }
}