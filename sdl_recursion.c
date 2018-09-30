#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>

/* These constants define 8-bit rvalues representing the color codes. */
/* There can be 8 total different color codes. */
#define LIME 0x01  // 0000_0001
#define PINK 0x02  // 0000_0010

void drawStack(SDL_Renderer* renderer, SDL_Rect* rectangle, Uint8 color);

void handleEvents(SDL_Renderer* renderer, SDL_Window* window, SDL_Event* event);

/**
 * The runtime stack of this recursive function is drawn to the screen.
 * This function goes up into recursion until rectangle-> y == 90,
 * then it comes back down and all the stack frames are popped off the runtime stack.
 *
 * Every single stack frame of the function is printed twice:
 *   First time on entrance into the recursive function call,
 *   when the stack frame is pushed onto the runtime stack.
 *   Second time just before exit out of the recursive function call,
 *   when the stack frame is just about to be pushed into the stack.
 *
 * When a new stack frame is pushed onto the function call stack, it is drawn in LIME,
 * and when the recursion comes back down, it is being popped of the function call stack,
 * so it is drawn in PINK.
 *
 * The function bunny() handles events recieved by the window by calling handleEvents().
 * Events are handled just before the current stack frame is drawn going up,
 * and just after the stack frame is drawn going down.
 *
 * @param SDL_Renderer* renderer - Pointer to the renderer is needed for drawing shapes onto
 *                                 the screen.
 *          It is also passed to the handleEvents() function to destroy the renderer in case
 *          the program closes unexpectedly.
 *
 * @param SDL_Window* window - Pointer to the window is passed to the handleEvents() function
 *                             to destroy the window in case the program closes unexpectedly.
 *
 * @param SDL_Rect* rectangle - It is a graphical representation of the current stack frame.
 *                       When a new stack frame is pushed onto the stack, y is decremented, going up.
 *                       When the stack frame is popped off the stack, y is incremented, going up.
 *
 * @param SDL_Event* event - This is the master structure which is used for event handling.
 *                           It is passed into handleEvents().
 */
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


/**
 * This function handles events that the window recieves.
 *
 * The program must be responsive to the user.
 * If the user decides to click the (X) to close the window, then the window
 * must close and the program must exit gracefully instead of crashing with an exception.
 * Event handling is also required by the OS.
 * This is necessary to keep the OS from marking the program as unresponsive.
 *
 * This function is called each twice for each recursive call of bunny(),
 * once on entrance into the recursive function call, and once on exit.
 *
 * @param SDL_Renderer* renderer - In case the program is closed unexpectedly, we need to
 *                                 dealoccate the dynamic SDL_Renderer object.
 *
 * @param SDL_Window* window - In case the program is closed unexpectedly, we need to
 *                             dealoccate the dynamic SDL_Window object.
 *
 * @param SDL_Event* event - A pointer to the event handler master structure.
 *        Because sizeof(SDL_Event) == 56, I do not want to create a local variable on the runtime stack.
 */
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
	    exit(EXIT_FAILURE);
	}
    }
}


/**
 * This function updates the scene on the screen.
 *
 * It draws the current stack frame that function bunny() is currently in
 * relatively proportional to other stack frames in the call stack.
 *
 * @param SDL_Renderer* renderer - A pointer to the renderer into which the
 *                                 back buffer is going to be drawn.
 *
 * @param const SDL_Rect* rectangle - A pointer to the rectangle object, which represents
 *                                    the stack frame and its dimensions.
 *
 * @param Uint8 color - Specifies the color to draw the box in.
 *                      LIME if the stack frame is being popped onto the runtime stack.
 *                      PINK if the stack frame if being popped off the runtime stack.
 */
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

