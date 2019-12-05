#include "def.h"


const int WALKING_ANIMATION_FRAMES = 4;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gSpriteClips[4];

CTexture gBackground;
CTexture gStanding;
CTexture gWalking;

bool init(){

  if(SDL_Init(SDL_INIT_VIDEO)<0){
    printf("Initalization Error %s\n",SDL_GetError());
    return false;
  }

  if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1")){
    printf("Warning: Linear texture filtering not enabled!\n");
  }
  
  gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if(gWindow == NULL){
    printf("Window Error %s\n", SDL_GetError());
    return false;
  }
  gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(gRenderer == NULL){
    printf("Renderer Error %s\n",SDL_GetError());
    return false;
  }
   
  SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0xFF,0xFF);
  
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)){
    printf("SDL_image Error: %s\n",IMG_GetError());
    return false;
  }

  return true;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
  
  success &= gBackground.loadFile("imgs/background.png", gRenderer);
  success &= gStanding.loadFile("imgs/standing.png", gRenderer);
  success &= gWalking.loadFile("imgs/walking.png", gRenderer);

  gSpriteClips[ 0 ].x =   0;
	gSpriteClips[ 0 ].y =   0;
	gSpriteClips[ 0 ].w =  64;
	gSpriteClips[ 0 ].h = 205;

	gSpriteClips[ 1 ].x =  64;
  gSpriteClips[ 1 ].y =   0;
  gSpriteClips[ 1 ].w =  64;
  gSpriteClips[ 1 ].h = 205;
  
  gSpriteClips[ 2 ].x = 128;
  gSpriteClips[ 2 ].y =   0;
  gSpriteClips[ 2 ].w =  64;
  gSpriteClips[ 2 ].h = 205;

  gSpriteClips[ 3 ].x = 196;
  gSpriteClips[ 3 ].y =   0;
  gSpriteClips[ 3 ].w =  64;
  gSpriteClips[ 3 ].h = 205;

  return success;
}


int main(int argc, char* args[]){
  
  if(!init()){
    printf("Failed to Initialize!\n");
    return 0;
  }

  if(!loadMedia()){
    printf("Failed to load media!\n");
    return 0;
  }

  bool quit = false;
  SDL_Event e;
  SDL_Rect clip = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
  
  Entity person(0,0,&gStanding,&gWalking);
  int frame =0;

  while(!quit){
    
    while(SDL_PollEvent(&e)!=0){
      if(e.type == SDL_QUIT){
        quit = true;
        continue;
      }
      else{
        person.handleEvent(e);
      }
    }

    person.move();
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    SDL_RenderClear(gRenderer);
    gBackground.render(0,0,gRenderer,&clip);
    person.move(); 
    person.render(gRenderer,&gSpriteClips[frame/4]);
    SDL_RenderPresent(gRenderer);

    frame = frame/4 >= WALKING_ANIMATION_FRAMES ? 0 : frame+1;
  }

  return 0;
}

