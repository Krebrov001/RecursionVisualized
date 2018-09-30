/**
 * @file    recursion_visualized_defs.c
 * @author  Konstantin Rebrov
 * @version 07/16/2018
 *
 * Recursion Visualized Project
 *
 * @section DESCRIPTION
 *
 * This project is a program to demonstrate recursion in a graphical way for education purposes.
 * 
 * This file contians the definitions of the functions used in the program.
 */

#include "SDL.h"     // Simple DirectMedia Layer API structures and functions
#include <stdlib.h>  // C standard library - for exit(), EXIT_SUCCESS, EXIT_FAILURE

#include "recursion_visualized_header.h"


void bunny(SDL_Renderer* renderer, SDL_Window* window, SDL_Rect* rectangle, SDL_Event* event)
{
    handleEvents(renderer, window, event);

    drawStack(renderer, rectangle, LIME);

    if (rectangle->y == 90) {
	// reached the max, or base case.
        return;
    } else {
	// going up the stack.
        rectangle->y -= 50;

	bunny(renderer, window, rectangle, event);
    }

    // going down the stack.
    rectangle->y += 50;

    drawStack(renderer, rectangle, PINK);

    handleEvents(renderer, window, event);

    return;
}


void handleEvents(SDL_Renderer* renderer, SDL_Window* window, SDL_Event* event)
{
    while (SDL_PollEvent(event)) {
	// If the user clicks the (X), the SDL_QUIT or SDL_WINDOWEVENT_CLOSE event
	// may be generated. This code reacts to the recieved event by destroying the
	// SDL_Window and SDL_Renderer to avoid memory leaks.
	// Then it quits the SDL subsystems and exits the program with an appropriate
	// return code providing information for the OS.
        if (event->type == SDL_QUIT || event->type == SDL_WINDOWEVENT_CLOSE) {
	    SDL_DestroyWindow(window);
	    SDL_DestroyRenderer(renderer);
	    SDL_Quit();
	    exit(EXIT_SUCCESS);
	}
    }
}


void drawStack(SDL_Renderer* renderer, const SDL_Rect* rectangle, Uint8 color)
{
    // Draws the blue background.
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    // Draws the current "stack frame".
    if (color == LIME) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);
    } else if (color == PINK) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);
    }
    SDL_RenderFillRect(renderer, rectangle);

    // Presents the back buffer onto the front buffer,
    // updating the contents of the renderer.
    SDL_RenderPresent(renderer);

    // Sleep for 1 second.
    SDL_Delay(1000);

    return;
}

