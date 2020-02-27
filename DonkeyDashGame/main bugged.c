#include<stdio.h>
#include "SDL/SDL.h"
#include <string.h>

typedef struct _s
{

  SDL_Surface* image;
  SDL_Surface* hoverImage;
  SDL_Surface* clickImage;
  SDL_Rect pos;



  int type;
  int visible;
  int order;
} Sprite;


Sprite Sprites[100];
int nSprites = 0;
int gameRunning = 1;
int cMouseOver = -1;
int mouseDown = 0;

Sprite MakeSprite(char name[], int type)
{
  char fname[40] = "";
  strcpy(fname, name);
  strcat(fname, ".bmp");
  //printf("name = %s\n", fname);
  Sprite sprite;
  sprite.image = SDL_LoadBMP(fname);
  sprite.visible = 1;
  sprite.type=type;
  if(type==1)
  {
    char hname[30] = "";
    strcat(hname, name);
    strcat(hname, " hover.bmp");
    sprite.hoverImage = SDL_LoadBMP(hname);
    char cname[30] = "";
    strcat(cname, name);
    strcat(cname, " clicked.bmp");
    sprite.clickImage = SDL_LoadBMP(cname);

    if(sprite.hoverImage==NULL)
    {
      printf("Unable to load hover bitmap: %s\n", SDL_GetError());
    }

    if(sprite.clickImage==NULL)
    {
      printf("Unable to load click bitmap: %s\n", SDL_GetError());
    }

  }
  //image = SDL_LoadBMP("images/background main.bmp");
  if(sprite.image==NULL)
  {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
  }
  Sprites[nSprites++] = sprite;
  return sprite;
}

void checkMouse()
{
  cMouseOver = -1;
  int mx,my;
  SDL_GetMouseState(&mx, &my);
  for(int o=nSprites-1; o>=0; o--)
  {
    if(Sprites[o].pos.x<=mx && Sprites[o].pos.y<=my && Sprites[o].pos.x+Sprites[o].pos.w>=mx && Sprites[o].pos.y+Sprites[o].pos.h>=my)
    {
      cMouseOver = o;
      break;
    }
  }
}

int main()
{
  SDL_Delay(1000);
  SDL_Surface *screen;
  SDL_Surface *image;
  SDL_Rect positionecran;
  char pause;
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
  screen = SDL_SetVideoMode(800, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if(screen==NULL)
  {
    printf("Unable to set video mode : %s\n", SDL_GetError());
    return 1;
  }


  Sprite bg = MakeSprite("images/background main", 0);
  bg.pos.x = 0;
  bg.pos.y = 0;
  bg.pos.w = bg.image->w;
  bg.pos.h = bg.image->h;


  Sprite continueBtn = MakeSprite("images/continuer", 1);
  continueBtn.pos.x = 0;
  continueBtn.pos.y = 0;
  continueBtn.pos.w = 100;
  continueBtn.pos.h = 27;



  SDL_Delay(1000);

  while(gameRunning==1)
  {


    //continueBtn.pos.x++;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        gameRunning = 0;
      }
      else if(event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN)
      {
        mouseDown = 1;
      }
      else if(event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
      {
        mouseDown = 0;
      }
      else
      {
        //printf("another event.\n");
      }

    }

    checkMouse();


    for(int o=0; o<nSprites; o++)
    {
      if(Sprites[o].visible != 1) continue;
      if(Sprites[o].type==9)
      {
        if(cMouseOver==o)
        {
          if(mouseDown==1)
            SDL_BlitSurface(Sprites[o].clickImage, &Sprites[o].pos, screen, &Sprites[o].pos);
          else
            SDL_BlitSurface(Sprites[o].hoverImage, &Sprites[o].pos, screen, &Sprites[o].pos);
        }
      }
      else
      {
        SDL_BlitSurface(Sprites[o].hoverImage, &Sprites[o].pos, screen, &Sprites[o].pos);

      }
    }


    //SDL_BlitSurface(Sprites[o].hoverImage, &Sprites[o].pos, screen, &Sprites[o].pos);


    SDL_Delay(33);

    SDL_Flip(screen);

  }

  SDL_Quit();

  printf("done\n");

  //SDL_FreeSurface(image);
  pause = getchar();

  printf("yeh worked xd : %s\n", SDL_GetError());

  return 0;
}
