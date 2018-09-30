/**
 * @file    recursion_visualized_main.c
 * @author  Konstantin Rebrov
 * @version 07/16/2018
 *
 * Recursion Visualized Project
 *
 * @section DESCRIPTION
 *
 * This project is a program to demonstrate recursion in a graphical way for education purposes.
 * 
 * This file contians the main() function definition.
 *
 * This program displays a SDL window. Inside of it, we can see an animation of the function call stack.
 * This animation displays the real state of the function call stack at any given moment.
 * A rectangle representing the currently running stack frame goes up and down the call stack.
 * The program uses an actual runtime stack to generate the animation.
 */

#include "SDL.h"     // Simple DirectMedia Layer API structures and functions
#include <stdlib.h>  // C standard library - for exit(), EXIT_SUCCESS, EXIT_FAILURE, NULL
#include <stdio.h>   // C standard input/output - for fprintf(), stderr

#include "recursion_visualized_header.h"


/**
 * The main() function is the entry point of the program execution.
 *
 * The preprocessor directive is used if we would want to mix C and C++ code together.
 * extern "C" tells the C++ compiler to not mangle the names of functions.
 *
 * The first part is the initialization code, setting up the program.
 * The second part is the drawing/animation code, where all the action happens.
 * The third part is the conclusion code, ending the program and cleaning up.
 *
 * @param int argc - The number of command-line arguments (including the name of the executable).
 *
 * @param char* argv[] - An array of char*'s which point to the C-strings containing the
 *                       command-line arguments.
 *
 * @return int - EXIT_SUCCESS if the program ran successfully through its completion.
 *               EXIT_FAILURE if the program encountered a runtime error.
 */
#ifdef __cplusplus
  extern "C"
#endif
int main(int argc, char* argv[])
{
    /* This chunk of code is responsible for setting up the infrastructure used by the program. */

    /* Initialize the SDL Video subsystem and check for errors. */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "error - Initialization of SDL subsystems failed: %s\n", SDL_GetError());
	exit(EXIT_FAILURE);
    }

    SDL_Window*   window   = NULL;
    SDL_Renderer* renderer = NULL;

    /* Allocate dynamic memory for the SDL_Window and check for errors. */
    window = SDL_CreateWindow("Recursion Visualized", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              300, 640, 0);
    if (!window) {
        fprintf(stderr, "error - Creating window failed: %s\n", SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
    }

    /* Allocate dynamic memory for the SDL_Renderer and check for errors. */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "error - Creating renderer failed: %s\n", SDL_GetError());
	// Since the SDL_Window was created successfully,
	// we need to destroy it anyway to avoid memory leak.
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_FAILURE);
    }


    /* The following code is responsible for animation and drawing objects on the screen. */

    // Draw the main function, without the stack.
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    // This box is a visual representaion of a stack frame.
    // Define its initial x and y positions, and its dimensions.
    SDL_Rect box = {125, 590, 50, 50};

    // Used for event handling.
    SDL_Event e;

    // Start the recursion process:
    // This recursive function draws the function call stack as each recursive
    // function call happens.
    bunny(renderer, window, &box, &e);

    // Draw the main function, without the stack.
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);


    /* This chunk of code is responsible for safely exiting the program. */

    /* Deallocate dynamic memory for the window and the renderer. */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    /* Quit the SDL subsystems and free up any additional used resources. */
    SDL_Quit();

    return EXIT_SUCCESS;
}

