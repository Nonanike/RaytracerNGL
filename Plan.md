# Plan

### Initial plan

Pseudo-code

for (each pixel in the image)
{
    //step 1
    build a camera;
    //step 2
    build a lighting;
    //step 3
    trace the vector from the origin point (camera) to the current pixel (left upper one);
    //step 4
    cast the primary ray into the scene;
    if (primary ray intersects an object)
        {
            cast secondary ray into the ligth source;
            if (secondary ray hit the ligth source)
                {
                    set the current pixel's colour to the object's colour at the intersecting point;
                }
        }
    else
        {
            set the current pixel's colour to grey;
        }
}
