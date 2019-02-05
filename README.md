# RecursionVisualized
This project, creating using the SDL libraries, is meant to teach first-year students the concept of recursion.
This is a GUI program that draws the animated stack frames for each recursive function call, and it uses the ACTUAL runtime stack with the recursive function. Instead of using print statements to show it’s current recursion state, the recursive function uses the C/C++ SDL Libraries to draw graphics onto the screen, displaying all the stack frames as they get pushed and popped onto the runtime stack. This is intended as a teaching tool.

To use this project, please download the .tar file to a Linux computer and then run the Makefile.

To 'make' the program you must have the SDL2 libraries installed.
The following command automates the installation process for you:
Note: You may have to uncomment lines 28-31 for it to work.
<br>
<b>
* make --makefile=Makefile_recursion_visualized install_SDL2
</b>

This command actually triggers a makefile rule which runs the following commands:
<br>
<b>
* sudo apt-get install libsdl2-2.0
* sudo apt-get install libsdl2-dev
</b>

Then to start the program just do:
<b>
* make --makefile=Makefile_recursion_visualized run
</b>

![Alt text](/Screenshots/recursion_visualized.png?raw=true "Cover")

This diagram explains how the recursion stack is drawn by the program.

![Alt text](/Screenshots/recursion_notes.jpg?raw=true)
