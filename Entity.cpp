#include "def.h"

Entity::Entity(int X, int Y, CTexture *initTexture, CTexture *aniTexture){
  mPosX = X;
  mPosY = Y;
  mVelX = 0;
  mVelY = 0;
  idleTexture = initTexture;
  if (aniTexture == NULL) moveTexture = initTexture;
  else moveTexture = aniTexture;
}

Entity::Entity(CTexture *initTexture){
  mPosX = 0;
  mPosY = 0;
  mVelX = 0;
  mVelY = 0;
  idleTexture = initTexture;
  moveTexture = initTexture;
}

void Entity::handleEvent(SDL_Event& e){
  if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
    switch(e.key.keysym.sym){
      case SDLK_UP: mVelY -= E_VEL; break;
      case SDLK_DOWN: mVelY += E_VEL; break;
      case SDLK_LEFT: mVelX -= E_VEL;  break;
      case SDLK_RIGHT: mVelX += E_VEL;  break;
    }
  }
  else if(e.type == SDL_KEYUP && e.key.repeat == 0){
    switch(e.key.keysym.sym){
      case SDLK_UP: mVelY += E_VEL; break;
      case SDLK_DOWN: mVelY -= E_VEL; break;
      case SDLK_LEFT: mVelX += E_VEL;  break;
      case SDLK_RIGHT: mVelX -= E_VEL;  break;
    }
  }
}

void Entity::move(){
  mPosX += mVelX;
  if((mPosX < 0) || (mPosX + E_WIDTH > SCREEN_WIDTH)) mPosX -=mVelX;
  mPosY += mVelY;
  if((mPosY < 0) || (mPosY + E_WIDTH > SCREEN_HEIGHT)) mPosY -=mVelY;
}

void Entity::render(SDL_Renderer* gRenderer, SDL_Rect *clip){
  if(mVelX == 0 && mVelY ==0){
    idleTexture->render(mPosX,mPosY,gRenderer);
  }
  else{
    if (mVelX<0) moveTexture->render(mPosX,mPosY,gRenderer,clip,SDL_FLIP_NONE);
    else moveTexture->render(mPosX,mPosY,gRenderer,clip,0.0,NULL,SDL_FLIP_HORIZONTAL);
  }
}
