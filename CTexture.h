
// if this inclusion was not already defined
#ifndef _CTexture_H
#define _CTexture_H

class CTexture{
  public:
    CTexture(); // Constructor
    ~CTexture(); // Destructor

    bool loadFile(std::string path,SDL_Renderer* gRenderer);
    #if defined(_SDL_TFF_H) || defined(SDL_TTF_H)
    bool loadText(std::string textureText, SDL_Color textColor,SDL_Renderer* gRenderer);
    #endif

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();
  
  private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif
