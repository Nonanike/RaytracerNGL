///This file is modified from original file written by Jon Macey
///Available from: https://github.com/NCCA/BlankNGL/blob/main/src/NGLScene.cpp
///Commit nr: ccc88248d1acdef52fff8d229c850d8cc15f938c

#include <QMouseEvent>
#include <QGuiApplication>

#include <cstdlib>
#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/Util.h>
#include <ngl/VAOPrimitives.h>

#include "NGLScene.h"
#include "Image.h"
#include "RGBA.h"
#include "Ray.h"
#include "triangle.h"
#include "Material.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "interval.h"
#include "camera.h"

////modified by me - changed the title
NGLScene::NGLScene()
{
    // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
    setTitle("Raytracer");
}
////end of the edit

NGLScene::~NGLScene()
{
    std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w , int _h)
{
    m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

void NGLScene::initializeGL()
{
    // we must call that first before any other GL commands to load and link the
    // gl commands from the lib, if that is not done program will crash
    ngl::NGLInit::initialize();
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    glEnable(GL_MULTISAMPLE);

/// Modified code from :-
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

    ///Image size - choose the width of the final image and it is gonna return a height based on 16/9 ratio

    m_image.setSize(1280);

    /// World

    HittableList world;

    ///Here you create a material: either lambertian, metal or dielectric

    auto material_left = make_shared<Lambertian>(RGBA(100,100,0,255));
    auto material_far_left = make_shared<Dielectric>(1.5);
    auto material_right = make_shared<Metal>(RGBA(100,100,100,255));
    auto material_far_right = make_shared<Dielectric>(0.75);
    auto material1 = make_shared<Lambertian>(RGBA(150,200,100,255));

    ///Here you add a triangle object to the scene and choose a material that will be applied to it

    world.add(make_shared<Triangle>(ngl::Vec3(-0.9,0,0),ngl::Vec3(-0.5,-0.9,0),ngl::Vec3(0,0,-0.9), material_far_left));
    world.add(make_shared<Triangle>(ngl::Vec3(0.55,-0.2,-0.2),ngl::Vec3(0.55,0.55,0.9),ngl::Vec3(0,-0.2,0.55), material_right));
    world.add(make_shared<Triangle>(ngl::Vec3(0.5,0.5,0.5),ngl::Vec3(0,0.5,0.6),ngl::Vec3(0,0.3,0.6), material_left));
    world.add(make_shared<Triangle>(ngl::Vec3(-0.9,0,0),ngl::Vec3(0,-0.2,0),ngl::Vec3(0,0,-0.9), material_far_right));
    world.add(make_shared<Triangle>(ngl::Vec3(-0.5,0,0), ngl::Vec3(-0.5,-0.5,0),ngl::Vec3(0,0,-0.5),material1));

    ///Here you manipulate camera parameters

    m_camera.samplesPerPixel = 500;
    m_camera.maxDepth = 50;

    m_camera.vfov = 10;
    m_camera.lookFrom = ngl::Vec3(13,2,3);
    m_camera.lookAt = ngl::Vec3(0,0,-1);
    m_camera.vup = ngl::Vec3(0,1,0);

    m_camera.initilize();
    m_camera.render(world);

///End of modified code
}

void NGLScene::paintGL()
{
    // clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,m_win.width,m_win.height);
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
    // this method is called every time the main window receives a key event.
    // we then switch on the key value and set the camera in the GLWindow
    switch (_event->key())
    {
        // escape key to quite
        case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
        case Qt::Key_Space :
            m_win.spinXFace=0;
            m_win.spinYFace=0;
            m_modelPos.set(ngl::Vec3::zero());

            break;
        default : break;
    }
    // finally update the GLWindow and re-draw

    update();
}