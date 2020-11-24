Yifan Yang 40038814 

-------------------------------------------------------------------------------------------------------------------------------------
Environment setting:  Simply add

------------------------------------------------------------------------------------------------------------------------------

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

X: Render the scene with grass texture on the ground mesh, tire texture on the wheels and shiny metal finish

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