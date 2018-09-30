/**
 * @file    recursion_visualized_header.h
 * @author  Konstantin Rebrov
 * @version 07/16/2018
 *
 * Recursion Visualized Project
 *
 * @section DESCRIPTION
 *
 * This project is a program to demonstrate recursion in a graphical way for education purposes.
 * 
 * This file contians the declarations of the constants and functions used in the program.
 * Here also is documentation about what they do.
 */

/* These constants define 8-bit rvalues representing the color codes. */
/* There can be 8 total different color codes. */
#define LIME 0x01  // 0000_0001
#define PINK 0x02  // 0000_0010


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
 *
 * The preprocessor directive is used if we would want to mix C and C++ code together.
 * extern "C" tells the C++ compiler to not mangle the names of functions.
 */
#ifdef __cplusplus
  extern "C"
#endif
void bunny(SDL_Renderer* renderer, SDL_Window* window, SDL_Rect* rectangle, SDL_Event* event);


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
 *
 * The preprocessor directive is used if we would want to mix C and C++ code together.
 * extern "C" tells the C++ compiler to not mangle the names of functions.
 */
#ifdef __cplusplus
  extern "C"
#endif
void handleEvents(SDL_Renderer* renderer, SDL_Window* window, SDL_Event* event);


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
 *
 * The preprocessor directive is used if we would want to mix C and C++ code together.
 * extern "C" tells the C++ compiler to not mangle the names of functions.
 */
#ifdef __cplusplus
  extern "C"
#endif
void drawStack(SDL_Renderer* renderer, const SDL_Rect* rectangle, Uint8 color);

