Yifan Yang 40038814 yifanyang0826@gmail.com 


CopyRight:The recourses in Assets folder don't belong to me. The third party environment modules in third party folder don't belong to me. The std_image.h in Labs folder is from https://github.com/nothings/stb/blob/master/stb_image.h
-------------------------------------------------------------------------------------------------------------------------------------
Environment setting:
The core part of this project is Labs  
Simply use Visual Studio add labs.sln in folder Labs, run main.cpp,other environment are intergrated in folder thirdParty
------------------------------------------------------------------------------------------------------------------------------
Features Implemented:

Input_and_Interaction

Geometry,Viewing,Projections and Transformtions

Shadows_with_Projections

Two Pass Shadow Algorithm

Spilines

Rasterization

Programmable Shaders

Ray Tracing

Texture Mapping

Particle Effect

-------------------------------------------------------------------------------------------------------------------------------

World View:red axis is x axis,blue axis is z axis

positive x means forward,positive z means rightward

-------------------------------------------------------------------------------------------------------------------------------
Basic Operation

W S A D: forward ,backward ,leftward, rightward

U: make the car bigger

J: make the car smaller

P: point mode with size 6

L: line mode

T: triangle mode

X: turn on texture and shiny car body

B: Turn on the light of car, run two pass shadow algorithm with world light source

V: Shadowing

C: First person perspective

Space Bar: re-position the car at xz plane

Home: set every matrix to initial

right mouse button pressed: pan

middle mouse button pressed: tilt (angle limited)

left moust button pressed; zoom	(scale is limited, min is vec3(0.1,0.1,0.1)

UP DOWN LEFT RIGHT: rotate the world (implemented by rotate camera)

1  2    3   4 :translate the camera  (0:15 to 0:20 on moodle assignment1 submission)

-------------------------------------------------------------------------------------------------------------------------------
the camera is initially at xy plane ,look at center, so you should use left arrow/right arrow/up arrow/down arrow to see the x axis hidden by y axis

Double buffer: glfw is default double buffer, and swap front/back buffer by glfwSwapBuffers(window); 