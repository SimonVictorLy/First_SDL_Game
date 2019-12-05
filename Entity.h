#ifndef _Entity_H
#define _Entity_H
class Entity{
  public:
    
    static const int E_WIDTH = 20;
    static const int E_HEIGHT = 20;

    static const int E_VEL = 2;
    
    Entity(CTexture *initTexture);
    Entity(int X, int Y, CTexture *initTexture, CTexture *aniTexture = NULL);
    
     
    void handleEvent(SDL_Event &e);
    void move();
    void render(SDL_Renderer* gRenderer, SDL_Rect *clip = NULL);
  
  private:
    int mPosX, mPosY;
    int mVelX, mVelY;  
    CTexture* idleTexture;
    CTexture* moveTexture;
};
#endif
