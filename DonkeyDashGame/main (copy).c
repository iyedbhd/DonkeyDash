#include<stdio.h>

#include "funcs.h"

#include<SDL2/SDL.h>

#include<SDL2/SDL_image.h>

#include "SDL2/SDL_mixer.h"

#include <string.h>

Sprite * Sprites[100];
int nSprites = 0;
int done = 0;

int gameRunning = 1;
int cMouseOver = -1;
int mouseDown = 0;
int processedClick = 0;
Sprite* donkeyAnimation;
SDL_Texture * backgroundTexture;
Man enemy;
SDL_Renderer * renderer;
int globalTime = 0;
  const int gameHeight = 975;
  const int gameWidth = 1920;

void loadMenu()
{

imageData bgData = {"background.png"};
  Sprite* bg = MakeSprite(bgData, 0, Sprites, &nSprites, renderer);
  bg->pos.x = 0;
  bg->pos.y = 0;
  bg->pos.w = 640;
  bg->pos.h = 480;
  bg->autoSize = 1;
  bg->scale = 0.9;

  
  imageData unicornData = {"LightUnicornSeat.png"};
  
   Sprite* unicornAnim = MakeSprite(unicornData, 0, Sprites, &nSprites, renderer);
   unicornAnim->animated = 1;
   unicornAnim->pos.x = 350;
   unicornAnim->pos.y = 250;
   unicornAnim->pos.w = 99*2;
   unicornAnim->pos.h = 100*2;
   AnimState unicornGlow = {0,69,99,100,3};
   unicornAnim->animations[0] = unicornGlow;
   unicornAnim->totalAnims = 1;
   unicornAnim->currentState = 0;
   unicornAnim->flipped = 0;



  imageData playBtnData = {"play0001.png","play0002.png","play0003.png"};
  
  Sprite* playBtn = MakeSprite(playBtnData, 1, Sprites, &nSprites, renderer);
   playBtn->pos.x = 225;
   playBtn->pos.y = 200;
   playBtn->autoSize = 1;
   playBtn->scale = 1;

   playBtn->clickEvent = 2;

  imageData settingsData = {"settings0001.png","settings0002.png","settings0003.png"};
  
  Sprite* settingsBtn = MakeSprite(settingsData, 1, Sprites, &nSprites, renderer);
   settingsBtn->pos.x = 225;
   settingsBtn->pos.y = 265;
   settingsBtn->autoSize = 1;
   settingsBtn->scale = 1;
   settingsBtn->clickEvent = 4;

  imageData closeData = {"close0001.png","close0002.png","close0003.png"};
  
  Sprite* closeBtn = MakeSprite(closeData, 1, Sprites, &nSprites, renderer);
   closeBtn->pos.x = 285;
   closeBtn->pos.y = 330;
   closeBtn->autoSize = 1;
   closeBtn->clickEvent = 5;
   closeBtn->scale = 1;


  imageData donkeyData = {"donkeyanimation.png"};
  
   donkeyAnimation = MakeSprite(donkeyData, 0, Sprites, &nSprites, renderer);
      donkeyAnimation->animated = 1;
   donkeyAnimation->pos.x = 250;
   donkeyAnimation->pos.y = 45;
   donkeyAnimation->pos.w = 43*3;
   donkeyAnimation->pos.h = 49*3;
   AnimState donkeyIdle = {0,20,121,143,3};
   AnimState donkeyWalk = {21,39,121,143,3};
   donkeyAnimation->animations[0] = donkeyIdle;
   donkeyAnimation->animations[1] = donkeyWalk;
   donkeyAnimation->totalAnims = 2;
   donkeyAnimation->currentState = 0;
   donkeyAnimation->flipped = 0;

   
   
  imageData birdData = {"LilyBird.png"};
  
   Sprite* birdanim = MakeSprite(birdData, 0, Sprites, &nSprites, renderer);
   birdanim->animated = 1;
   birdanim->pos.x = 450;
   birdanim->pos.y = 30;
   birdanim->pos.w = 77*1.5;
   birdanim->pos.h = 63*1.5;
   AnimState birdFlap = {0,14,77,63,3};
   birdanim->animations[0] = birdFlap;
   birdanim->totalAnims = 1;
   birdanim->currentState = 0;
   birdanim->flipped = 0;
}
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
void processClickEvent(int e)
{
  switch(e)
  {
    case 5:
    printf("yoooo");
    done = 1;
    break;
    case 2:
    donkeyAnimation->currentState = 1;
    break;
    case 4:
    deleteSprite(Sprites, &nSprites, 2);
    deleteSprite(Sprites, &nSprites, 2);
    deleteSprite(Sprites, &nSprites, 2);
    deleteSprite(Sprites, &nSprites, 2);

    break;
    case 1:
      {

        //Sprites[0]->image = IMG_Load("images/background main 2.bmp");
        //PlaySound("audio/music.mp3", -1);
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

void updateAnims(Sprite * spr)
{
  if(spr->currentState != -1)
  {
    spr->width = spr->animations[spr->currentState].width;
    spr->height = spr->animations[spr->currentState].height;
    if (globalTime % spr->animations[spr->currentState].delay == 0) {
      int sFrame = spr->animations[spr->currentState].start;
      int numFrames = spr->animations[spr->currentState].end - spr->animations[spr->currentState].start + 1;
      if (spr -> currentSprite <= (sFrame - 1)) {
        spr -> currentSprite = sFrame - 1;
      }
      spr -> currentSprite = ((spr -> currentSprite - sFrame + 1) % (numFrames)) + (sFrame);
    }
  }
}
void playAnim(int anim, Man * man) {
  switch (anim) {
  case 1: //idle
    if (globalTime % 3 == 0) {
      man -> currentSprite++;
      man -> currentSprite %= 21;
      printf("playing idle: %d\n", man -> currentSprite);
    }
    break;
  case 2: //walking
    if (globalTime % 3 == 0) {
      int sFrame = 22;
      int numFrames = 19;
      if (man -> currentSprite >= (sFrame + numFrames - 1) || man -> currentSprite < (sFrame - 1)) {
        man -> currentSprite = sFrame - 1;
      }
      man -> currentSprite++;
      man -> currentSprite = ((man -> currentSprite - sFrame + 1) % numFrames) + (sFrame - 1);

      printf("playing walk: %d\n", man -> currentSprite);
    }
    break;
  }

}
int processEvents(SDL_Window * window) {
  SDL_Event event;
  int done = 0;
  while (SDL_PollEvent( & event)) {
    if (event.type == SDL_WINDOWEVENT_CLOSE) {
      if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
        done = 1;
      }
    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        done = 1;
        break;
      }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
      switch (event.button.button) {
      case SDL_BUTTON_LEFT:
        mouseDown = 1;
        break;
      }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
      switch (event.button.button) {
      case SDL_BUTTON_LEFT:
      mouseDown = 0;
      processedClick = 0;
        break;
      }
    }
    else if (event.type == SDL_QUIT) {
      done = 1;
    }
    else {
      //printf("another event.\n");
    }

  }

  const Uint8 * state = SDL_GetKeyboardState(NULL);

  return done;
}

void doRender(SDL_Renderer * renderer) {
  //set the drawing color to blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  //Clear the screen (to blue)
  SDL_RenderClear(renderer);

  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  //SDL_RenderFillRect(renderer, &rect);
  //SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

  for(int o=0; o<nSprites; o++)
    {
      if(Sprites[o]->visible != 1) continue;
      if(Sprites[o]->animated == 1)
      { 
        updateAnims(Sprites[o]);
              SDL_Rect srcRect = {
              Sprites[o]->width * Sprites[o] ->currentSprite,
              0,
              Sprites[o]->width,
              Sprites[o]->height
            };

            SDL_RenderCopyEx(renderer, Sprites[o] ->image, & srcRect, & Sprites[o]->pos, 0, NULL, Sprites[o]->flipped);

        

      }
      else if(Sprites[o]->type==1)
      {
        if(cMouseOver==o)
        {
          if(mouseDown==1)
          {
            if(Sprites[o]->autoSize == 1)
            {
              SDL_QueryTexture(Sprites[o]->clickImage, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
              Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
              Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
            }

            SDL_RenderCopy(renderer, Sprites[o]->clickImage, NULL, &Sprites[o]->pos);

            if(processedClick==0)
            {
              processedClick = 1;
              PlaySoundSingle("SFXs/CSG_UI_Open_01.mp3", 0);
              if(Sprites[o]->clickEvent != -1)
                processClickEvent(Sprites[o]->clickEvent);
            }
          }
          else
          {
                        if(Sprites[o]->autoSize == 1)
                        {
                          SDL_QueryTexture(Sprites[o]->hoverImage, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
                          Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
                          Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
                        }

            SDL_RenderCopy(renderer, Sprites[o]->hoverImage, NULL, &Sprites[o]->pos);

          }
        }
        else
        {
            if(Sprites[o]->autoSize == 1){
              SDL_QueryTexture(Sprites[o]->image, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
              Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
              Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
            }

            SDL_RenderCopy(renderer, Sprites[o]->image, NULL, &Sprites[o]->pos);
        }
      }
      else
      {
        
            if(Sprites[o]->autoSize == 1)
            {
              SDL_QueryTexture(Sprites[o]->image, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
              Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
              Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
            }
            SDL_RenderCopy(renderer, Sprites[o]->image, NULL, &Sprites[o]->pos);

      }
    }
    
  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

void updateLogic() {
  checkMouse();
  globalTime++;
}

int main(int argc, char * argv[]) {
  SDL_Window * window; // Declare a window
   // Declare a renderer

  SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2
  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window", // window title
    SDL_WINDOWPOS_UNDEFINED, // initial x position
    SDL_WINDOWPOS_UNDEFINED, // initial y position
    gameWidth, // width, in pixels
    gameHeight, // height, in pixels
    0 // flags
  );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderSetLogicalSize(renderer, gameWidth, gameHeight);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);


PlaySound("MusicTrial/CSG_BlueSky_Loop.mp3",-1);
/*
  SDL_Surface * sheet = IMG_Load("background.png");
  if (!sheet) {
    printf("Cannot find sheet\n");
    return 1;
  }  

backgroundTexture = SDL_CreateTextureFromSurface(renderer, sheet); 
  SDL_FreeSurface(sheet);
*/

  //load the bg  
  loadMenu();
  // The window is open: enter program loop (see SDL_PollEvent)

  //Event loop
  while (!done) {
    //Check for events
    done = processEvents(window);

    //Update logic
    updateLogic();

    //Render display
    doRender(renderer);

    //don't burn up the CPU
    SDL_Delay(10);
  }

  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(backgroundTexture);
  SDL_DestroyTexture(enemy.sheetTexture);

  // Clean up
  SDL_Quit();
  return 0;
}
