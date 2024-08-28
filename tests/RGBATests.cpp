#include <gtest/gtest.h>
#include "RGBA.h"

TEST(RGBA, constructor)
{
    RGBA pixel;
    EXPECT_EQ(pixel.r, 0);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 0);
    EXPECT_EQ(pixel.a, 255);
}

TEST(RGBA, constructorUser)
{
    RGBA pixel(255, 125, 75, 23);
    EXPECT_EQ(pixel.r, 255);
    EXPECT_EQ(pixel.g, 125);
    EXPECT_EQ(pixel.b, 75);
    EXPECT_EQ(pixel.a, 23);
}

TEST(RGBA,set)
{
    RGBA pixel;
    pixel.set(0,255,128,255);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,255);
    EXPECT_EQ(pixel.b,128);
    EXPECT_EQ(pixel.a,255);
}

TEST(RBGA,clamp)
{
    RGBA pixel(255,0,128,220);
    pixel.clamp(50, 220);
    EXPECT_EQ(pixel.r,220);
    EXPECT_EQ(pixel.g,50);
    EXPECT_EQ(pixel.b,128);
    EXPECT_EQ(pixel.a,220);
}

TEST(RGBA, operatorMultiplyDouble)
{
    RGBA pixel(255,0,128,255);
    double i = 2.0;
    RGBA result = pixel * i;
    EXPECT_EQ(pixel.r, 510);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,256);
    EXPECT_EQ(pixel.a,255);
}

TEST(RGBA, operatorMultiplyRGBA)
{
    RGBA pixel(255,0,128,255);
    RGBA _rgba(200,100,0,255);
    RGBA result = pixel * _rgba;
    EXPECT_EQ(pixel.r, 51000);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,255);
}

TEST(RGBA, operatorAddRGBA)
{
    RGBA pixel(255,0,128,255);
    RGBA _rgba(200,100,0,255);
    RGBA result = pixel + _rgba;
    EXPECT_EQ(pixel.r, 455);
    EXPECT_EQ(pixel.g, 100);
    EXPECT_EQ(pixel.b, 128);
    EXPECT_EQ(pixel.a, 475);
}

TEST(RGBA, conversion)
{
    RGBA pixel(255,0,128,255);
    ngl::Vec3 _vec(0.2,0.5, 0.7);
    EXPECT_EQ(pixel.r, 51);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 64);
    EXPECT_EQ(pixel.a, 255);
}

TEST(RGBA, operatorAddVec3)
{
    RGBA pixel(255,0,128,255);
    ngl::Vec3 _vec(10,-2,0);
    RGBA result = pixel + (_vec * 255);
    EXPECT_EQ(pixel.r, 2805);
    EXPECT_EQ(pixel.g, -256);
    EXPECT_EQ(pixel.b, 128);
    EXPECT_EQ(pixel.a,255);
}
