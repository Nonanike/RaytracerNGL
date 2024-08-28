cmake_minimum_required(VERSION 3.12)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
# to build see the NGL instructions 
# Windows :- mkdir build; cd build ; cmake -DCMAKE_PREFIX_PATH=~/NGL/ .. ; cmake --build . 
# Linux / Mac mkdir build; cd build; cmake -DCMAKE_PREFIX_PATH~/NGL/ .. ; make
#-------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()


# Name of the project
project(RaytracerNGLBuild)
# This is the name of the Exe change this and it will change everywhere
set(TargetName RaytracerNGL)
# This will include the file NGLConfig.cmake, you need to add the location to this either using
# -DCMAKE_PREFIX_PATH=~/NGL or as a system environment variable. 
find_package(NGL CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
# Instruct CMake to run moc automatically when needed (Qt projects only)
set(CMAKE_AUTOMOC ON)
# find Qt libs
# find Qt libs first we check for Version 6
find_package(Qt6 COMPONENTS OpenGL Widgets QUIET )
if ( Qt6_FOUND )
    message("Found Qt6 Using that")
else()
    message("Found Qt5 Using that")
    find_package(Qt5 COMPONENTS OpenGL Widgets REQUIRED)
endif()

# use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# Set the name of the executable we want to build
add_executable(${TargetName}
                include/Ray.h
                include/Image.h
                include/RGBA.h
                include/camera.h
                include/triangle.h
                include/hittable.h
                include/hittable_list.h
                include/rtweekend.h
                include/interval.h
                include/Material.h

)

# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include)
target_sources(${TargetName} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLScene.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLSceneMouseControls.cpp  
			${PROJECT_SOURCE_DIR}/include/NGLScene.h
            ${PROJECT_SOURCE_DIR}/include/Ray.h
            ${PROJECT_SOURCE_DIR}/include/RGBA.h
            ${PROJECT_SOURCE_DIR}/include/Image.h
            ${PROJECT_SOURCE_DIR}/src/Image.cpp
            ${PROJECT_SOURCE_DIR}/include/triangle.h
            ${PROJECT_SOURCE_DIR}/include/hittable.h
            ${PROJECT_SOURCE_DIR}/include/hittable_list.h
            ${PROJECT_SOURCE_DIR}/include/rtweekend.h
            ${PROJECT_SOURCE_DIR}/include/interval.h
            ${PROJECT_SOURCE_DIR}/include/Material.h

)
target_link_libraries(${TargetName} PRIVATE Qt::Widgets Qt::OpenGL NGL OpenImageIO::OpenImageIO)

### Testing Code
find_package(GTest CONFIG REQUIRED)
find_package(NGL CONFIG REQUIRED)
include(GoogleTest)
add_executable(ImageTests
        include/Image.h
        include/RGBA.h
#        src/Image.cpp
#        include/camera.h
)
set(CMAKE_CXX_STANDARD 17)

include_directories(include $ENV{HOME}/NGL/include)

target_include_directories(ImageTests PRIVATE include)
target_sources(ImageTests PRIVATE
            tests/RGBATests.cpp
            tests/ImageTests.cpp
            src/Image.cpp
            include/Image.h
            include/RGBA.h
)
target_link_libraries(ImageTests PRIVATE GTest::gtest GTest::gtest_main
                      OpenImageIO::OpenImageIO)
gtest_discover_tests(ImageTests)

#target_link_libraries(${TargetName} PRIVATE Qt::Widgets Qt::OpenGL NGL)

add_custom_target(${TargetName}CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${TargetName}>/shaders
)