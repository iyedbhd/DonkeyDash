#include <stdio.h>
#include "funcs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include <string.h>

int deleteSprite(Sprite *Sprites[], int *nSprites, int index)
{
  if (index > (*nSprites - 1))
  {
    return 0;
  }
  else
  {
    (*nSprites)--;
    free(Sprites[index]);
    for (int s = index; s < (*nSprites); s++)
    {
      Sprites[s] = Sprites[s + 1];
    }
    return 1;
  }
}

void deleteFrom(Sprite *Sprites[], int *nSprites, int *nButtons, int index)
{
  for (int s = index; s < (*nSprites); s++)
  {
    if(Sprites[s]->type == 1)(*nButtons)--;
    free(Sprites[s]);
  }
  if(index <(*nSprites)) (*nSprites) = index;
  
}

void deleteAll(Sprite *Sprites[], int *nSprites, int *nButtons)
{
  for (int s = 0; s < (*nSprites); s++)
  {
    free(Sprites[s]);
  }
  (*nSprites) = 0;
  (*nButtons) = 0;
}
SDL_Texture* getTexture(char name[], SDL_Renderer * renderer)
{
  SDL_Texture* toLoad;
    SDL_Surface *sheet = IMG_Load(name);
  toLoad = SDL_CreateTextureFromSurface(renderer, sheet);
  SDL_FreeSurface(sheet);
  return toLoad;
}
Sprite *MakeSprite(imageData data, int type, Sprite *Sprites[], int *nSprites, int *nButtons, SDL_Renderer *renderer)
{
  printf("name = %s\n", data.name);
  Sprite *sprite = malloc(sizeof(Sprite));
  sprite->animated = 0;
  sprite->autoSize = 0;
  sprite->clickEvent = -1;
  SDL_Surface *sheet = IMG_Load(data.name);
  sprite->image = SDL_CreateTextureFromSurface(renderer, sheet);
  SDL_FreeSurface(sheet);

  sprite->visible = 1;
  sprite->type = type;
  sprite->clickEvent = 5;
  /*if(type == 0)
  {*/
  SDL_QueryTexture(sprite->image, NULL, NULL, &(sprite->pos.w), &(sprite->pos.h));
  //}
  if (type == 1)
  {
    (*nButtons)++;
    sheet = IMG_Load(data.over);
    sprite->hoverImage = SDL_CreateTextureFromSurface(renderer, sheet);
    SDL_FreeSurface(sheet);
    char cname[30] = "";
    sheet = IMG_Load(data.clicked);
    sprite->clickImage = SDL_CreateTextureFromSurface(renderer, sheet);
    SDL_FreeSurface(sheet);

    if (sprite->hoverImage == NULL)
    {
      printf("Unable to load hover bitmap: %s %s\n",data.over, SDL_GetError());
    }

    if (sprite->clickImage == NULL)
    {
      printf("Unable to load click bitmap: %s %s\n",data.clicked, SDL_GetError());
    }
  }
  if (sprite->image == NULL)
  {
    printf("Unable to load bitmap: %s %s\n",data.name, SDL_GetError());
  }
  Sprites[(*nSprites)++] = sprite;
  return sprite;
}
