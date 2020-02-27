#ifndef BB_H_INCLUDED
#define BB_H_INCLUDED
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"


typedef struct
{
  int start;
  int end;
  int width;
  int height;
  int delay;
  SDL_Texture* customTex;

} AnimState;
typedef struct _s
{

  SDL_Texture* hoverImage;
  SDL_Texture* clickImage;
  SDL_Texture* image;
  SDL_Rect pos;
  int height;
  int width;
  int totalAnims;
  AnimState animations[100];
  int currentState;
  int currentSprite;
  int flipped;
  int animated;
  int clickEvent;
  int type;
  int visible;
  int order;
  int autoSize;
  float scale;
} Sprite;

typedef struct
{
  char name[100];
  char over[100];
  char clicked[100];
} imageData;


Sprite* MakeSprite(imageData data, int type, Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer);
int deleteSprite(Sprite* Sprites[], int *nSprites, int index);
void deleteAll(Sprite *Sprites[], int *nSprites, int *nButtons);
void deleteFrom(Sprite *Sprites[], int *nSprites, int *nButtons, int index);
SDL_Texture* getTexture(char name[] , SDL_Renderer * renderer);
#endif // BB_H_INCLUDED
