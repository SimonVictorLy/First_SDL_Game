#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string> 

#include "CTexture.h"
#include "Entity.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* args[]);

// Starts SDL and creates window
bool init();

// Load images, sounds and other media
bool loadMedia();

// Frees media and shuts down SDL
void close();


