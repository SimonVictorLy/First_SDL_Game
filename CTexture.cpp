#include "def.h"

CTexture::CTexture(){
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

CTexture::~CTexture(){
  CTexture::free();
}

bool CTexture::loadFile(std::string path, SDL_Renderer* gRenderer){
  CTexture::free();

  SDL_Texture* newTexture = NULL;
  // Load Image 
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL){
    printf("SDL_image Error %s: %s\n", path.c_str(), IMG_GetError());
    return 0;
  }
  
  // Color Key Image
  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

  // Create texture from surface 
  newTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
  if (newTexture == NULL){
    printf("SDL_Texture Error %s: %s\n", path.c_str(), SDL_GetError());
  }
  else{
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
  }


  SDL_FreeSurface(loadedSurface);
  mTexture = newTexture;
  return mTexture!=NULL;
}

#if defined(_SDL_TFF_H) || defined(SDL_TTF_H)
bool CTexture::loadText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer){

  CTexture::free();
  
  // Render Text Surface
  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor); 
  if(textSurface == NULL){
    printf("Surface Text Error: %s\n", SDL_GetError());
    return 0;
  }
  
  // Render Texture from Surface
  mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  if(mTexture == NULL){
    printf("Texture Text Error: %s\n", SDL_GetError());
  }
  else{
    mWidth = textSurface->w;
    mHeight = textSurface->h;
  }
  
  // Text Surface must be freed
  SDL_FreeSurface(textSurface);
  return mTexture!=NULL;
}
#endif

void CTexture::free(){
  if(mTexture !=NULL){
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void CTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
  SDL_SetTextureColorMod(mTexture,red,green,blue);
}

void CTexture::setBlendMode(SDL_BlendMode blending){
  SDL_SetTextureBlendMode(mTexture,blending);
}
void CTexture::setAlpha(Uint8 alpha){
  SDL_SetTextureAlphaMod(mTexture,alpha);
}
void CTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
  
  SDL_Rect renderQuad = {x,y,mWidth,mHeight};
  
  if(clip!=NULL){
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(gRenderer,mTexture,clip,&renderQuad, angle, center,flip);
}

int CTexture::getWidth() {return mWidth;}
int CTexture::getHeight() {return mHeight;}
