#include<stdio.h>
#include "funcs.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include <string.h>


Sprite* Sprites[100];
int nSprites = 0;
int gameRunning = 1;
int cMouseOver = -1;
int mouseDown = 0;
int processedClick = 0;


void checkMouse()
{
  cMouseOver = -1;
  int mx,my;
  SDL_GetMouseState(&mx, &my);
  for(int o=nSprites-1; o>=0; o--)
  {
    if(Sprites[o]->pos.x<=mx && Sprites[o]->pos.y<=my && Sprites[o]->pos.x+Sprites[o]->pos.w>=mx && Sprites[o]->pos.y+Sprites[o]->pos.h>=my)
    {
      cMouseOver = o;
      break;
    }
  }
}

void PlaySound(char name[], int rep)
{
  Mix_Music *music;
  music = Mix_LoadMUS(name);
  Mix_PlayMusic(music, rep);
}


void PlaySoundSingle(char name[], int rep)
{
  Mix_Chunk *music;
  music = Mix_LoadWAV(name);

  Mix_PlayChannel(-1, music, rep);
}

void processClickEvent(int e)
{
  switch(e)
  {
    case 1:
      {

        Sprites[0]->image = IMG_Load("images/background main 2.bmp");
        PlaySound("audio/music.mp3", -1);
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

  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);


  Sprite* bg = MakeSprite("images/background main", 0);
  bg->pos.x = 0;
  bg->pos.y = 0;
  bg->pos.w = 800;
  bg->pos.h = 480;


  addButton("images/new game", 50, 100);
  Sprite* contBtn = addButton("images/continuer", 50, 130);
  contBtn->clickEvent = 1;


  addButton("images/settings", 50, 160);
  addButton("images/CRED", 50, 190);
  addButton("images/quit", 50, 220);


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
        processedClick = 0;
      }
      else
      {
        //printf("another event.\n");
      }

    }

    checkMouse();

    //printf("nsprites = %d\n", nSprites);
    for(int o=0; o<nSprites; o++)
    {
      if(Sprites[o]->visible != 1) continue;
      if(Sprites[o]->type==1)
      {
        if(cMouseOver==o)
        {
          if(mouseDown==1)
          {
            SDL_BlitSurface(Sprites[o]->clickImage, NULL, screen, &Sprites[o]->pos);

            if(processedClick==0)
            {
              processedClick = 1;
              PlaySoundSingle("audio/click.ogg", 0);
              if(Sprites[o]->clickEvent != -1)
                processClickEvent(Sprites[o]->clickEvent);
            }
          }
          else
            SDL_BlitSurface(Sprites[o]->hoverImage, NULL, screen, &Sprites[o]->pos);
        }
        else
        {
          SDL_BlitSurface(Sprites[o]->image, NULL, screen, &Sprites[o]->pos);
        }
      }
      else
      {
        SDL_BlitSurface(Sprites[o]->image, NULL, screen, &Sprites[o]->pos);

      }
    }
//SDL_BlitSurface(SDL_LoadBMP("images/background main.bmp"), NULL, screen, NULL);

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
