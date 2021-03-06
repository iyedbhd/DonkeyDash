#include <stdio.h>

#include "funcs.h"

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include "SDL2/SDL_mixer.h"
#include <SDL2/SDL_ttf.h>

#include <string.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>

#include "chipmunk/chipmunk_private.h"
TTF_Font *police = NULL;

//#include "ChipmunkDemo.h"
Sprite *Sprites[100];
int nSprites = 0;
int nButtons = 0;
int done = 0;
int currentScene = 0;
SDL_Window *window;
int gameRunning = 1;
int cMouseOver = -1;
int cBtnSelected = -1;
int oldMouseDown = -1;
int mouseDown = 0;
int enterPressed = 0;
int oldenterPressed = -1;
int currentHolding = -1;
int processedClick = 0;
SDL_Texture *backgroundTexture;
SDL_Renderer *renderer;
SDL_Renderer *MainRenderer;
int globalTime = 0;
//975x1920
int gameHeight = 850;
int gameWidth = 1450;
int IsFullscreen = 0;
//SDL_Texture *textTex;


/////////////////////PHYSICS CODEEEEEEEEEEEEEES


/////////////////////////////////////////////////
////////////////////////////////////////////////
///////////////////////////////////////////////

void loadScene(int n)
{
  switch(n)
  {
    case 0://menu
    loadMenu(Sprites,&nSprites, &nButtons,renderer);
    break;
    case 1://game
    loadGame(Sprites,&nSprites, &nButtons,renderer);
    break;
    case 2://settings
    loadSettings(Sprites,&nSprites, &nButtons,renderer);
    break;
  }


  currentScene = n;
}
Sprite *MakeSpriteHack(imageData data, int type)
{
MakeSprite(data, type, Sprites, &nSprites, &nButtons, renderer);
}
SDL_Texture* getTextureHack(char name[])
{
  getTexture(name, renderer);
}
void deleteAllSprites()
{
    deleteAll(Sprites, &nSprites, &nButtons);
}
void loadBG()
{

  /*imageData bgData = {"background.png"};
  Sprite *bg = MakeSprite(bgData, 0, Sprites, &nSprites, &nButtons, renderer);
  bg->pos.x = 0;
  bg->pos.y = 0;
  
  bg->autoSize = 1;
  bg->scale = 1;*/

  imageData monsterIdleData = {"monsterIdle.png"};

  Sprite *monsterIdleAnim = MakeSprite(monsterIdleData, 0, Sprites, &nSprites, &nButtons, renderer);
  monsterIdleAnim->animated = 1;
  monsterIdleAnim->pos.x = 350;
  monsterIdleAnim->pos.y = 500;
  monsterIdleAnim->pos.w = 80;
  monsterIdleAnim->pos.h = 108;
  monsterIdleAnim->autoSize = 1;
  monsterIdleAnim->scale = 2;
  monsterIdleAnim->currentSprite = 0;
  AnimState theAnim = {0, 49, 82, 107, 2, NULL};
  monsterIdleAnim->animations[0] = theAnim;
  monsterIdleAnim->totalAnims = 1;
  monsterIdleAnim->currentState = 0;
  monsterIdleAnim->flipped = 0;

  imageData monsterWalkData = {"MonsterWalk.png"};

  Sprite *monsterWalkAnim = MakeSprite(monsterWalkData, 0, Sprites, &nSprites, &nButtons, renderer);
  monsterWalkAnim->animated = 1;
  monsterWalkAnim->pos.x = 550;
  monsterWalkAnim->pos.y = 500;
  monsterWalkAnim->pos.w = 80;
  monsterWalkAnim->pos.h = 108;
  monsterWalkAnim->autoSize = 1;
  monsterWalkAnim->scale = 2;
  monsterWalkAnim->currentSprite = 0;
  AnimState theWalkAnim = {0, 59, 89, 111, 2, NULL};
  monsterWalkAnim->animations[0] = theWalkAnim;
  monsterWalkAnim->totalAnims = 1;
  monsterWalkAnim->currentState = 0;
  monsterWalkAnim->flipped = 0;

  imageData monsterTransitionData = {"MonsterTransition.png"};

  Sprite *monsterTransitionAnim = MakeSprite(monsterTransitionData, 0, Sprites, &nSprites, &nButtons, renderer);
  monsterTransitionAnim->animated = 1;
  monsterTransitionAnim->pos.x = 750;
  monsterTransitionAnim->pos.y = 500;
  monsterTransitionAnim->pos.w = 80;
  monsterTransitionAnim->pos.h = 108;
  monsterTransitionAnim->autoSize = 1;
  monsterTransitionAnim->scale = 2;
  monsterTransitionAnim->currentSprite = 0;
  AnimState theTransitionAnim = {0, 28, 88, 109, 2, NULL};
  monsterTransitionAnim->animations[0] = theTransitionAnim;
  monsterTransitionAnim->totalAnims = 1;
  monsterTransitionAnim->currentState = 0;
  monsterTransitionAnim->flipped = 0;

  imageData closeData = {"close0001.png", "close0002.png", "close0003.png"};

  Sprite *closeBtn = MakeSprite(closeData, 1, Sprites, &nSprites, &nButtons, renderer);
  closeBtn->pos.x = gameWidth - 200;
  closeBtn->pos.y = 25;
  closeBtn->autoSize = 1;
  closeBtn->clickEvent = 5;
  closeBtn->scale = 0.7;

  imageData fullScreenData = {"fullscreen0001.png", "fullscreen0002.png", "fullscreen0003.png"};

  Sprite *fullscreenBtn = MakeSprite(fullScreenData, 1, Sprites, &nSprites, &nButtons, renderer);
  fullscreenBtn->pos.x = gameWidth - 300;
  fullscreenBtn->pos.y = 35;
  fullscreenBtn->autoSize = 1;
  fullscreenBtn->clickEvent = 3;
  fullscreenBtn->scale = 0.7;
}

void loadPlay()
{
  deleteFrom(Sprites, &nSprites, &nButtons, 5);
  Sprites[0]->image = getTexture("bgplay.png", renderer);

  imageData okData = {"leftbtn0001.png", "leftbtn0002.png", "leftbtn0003.png"};
  Sprite *ok = MakeSprite(okData, 1, Sprites, &nSprites, &nButtons, renderer);
  ok->pos.x = 30;
  ok->pos.y = 150;
  ok->autoSize = 1;
  ok->clickEvent = 6;
  ok->scale = 0.7;
}
void checkMouse()
{
  cMouseOver = -1;
  int mx, my;

  SDL_GetMouseState(&mx, &my);
  for (int o = nSprites - 1; o >= 0; o--)
  {
    if (Sprites[o]->pos.x <= mx && Sprites[o]->pos.y <= my && Sprites[o]->pos.x + Sprites[o]->pos.w >= mx && Sprites[o]->pos.y + Sprites[o]->pos.h >= my)
    {
      cMouseOver = o;
      if (Sprites[o]->type == 1)
        cBtnSelected = -1;
      break;
    }
  }
}
void processClickEvent(int e)
{
  printf("\nProcessing Click Event %d \n", e);
  switch (e)
  {
  case 5:
    done = 1;
    break;
  case 1:
    loadScene(1);
    break;
  case 2: //
    //donkeyAnimation->currentState = 1;
    /*Sprites[1]->currentState++;
    Sprites[1]->currentState = Sprites[1]->currentState % Sprites[1]->totalAnims;*/
        loadScene(1);
    loadSave(NULL);
    break;
  case 3: //fullscreen
    SDL_SetWindowFullscreen(window, (IsFullscreen) ? 0 : SDL_WINDOW_FULLSCREEN);
    IsFullscreen = IsFullscreen ? 0 : 1;
    break;
  case 4: //openSettings
    loadScene(2);
    break;
  case 6: //LoadMenu
    loadScene(0);
    break;
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
/**
* @brief To update animations .
* @param spr Sprite
* @return Nothing
*/
 
void updateAnims(Sprite *spr)
{
  if (spr->currentState != -1)
  {
    spr->width = spr->animations[spr->currentState].width;
    spr->height = spr->animations[spr->currentState].height;
    if (spr->autoSize == 1)
    {
      spr->pos.h = spr->animations[spr->currentState].height * spr->scale;
      spr->pos.w = spr->animations[spr->currentState].width * spr->scale;
    }
    if (spr->currentSprite < spr->animations[spr->currentState].start)
      {
        spr->currentSprite = spr->animations[spr->currentState].start;
      }
      else if (spr->currentSprite > spr->animations[spr->currentState].end)
      {
        spr->currentSprite = spr->animations[spr->currentState].end;
      }
    if (globalTime % spr->animations[spr->currentState].delay == 0)
    {
      int sFrame = spr->animations[spr->currentState].start;
      int numFrames = spr->animations[spr->currentState].end - spr->animations[spr->currentState].start + 1;
      if (spr->currentSprite <= (sFrame - 1))
      {
        spr->currentSprite = sFrame - 1;
      }
      spr->currentSprite = ((spr->currentSprite - sFrame + 1) % (numFrames)) + (sFrame);

      
    }
    
  }
}
int processEvents(SDL_Window *window)
{
  SDL_Event event;
  int done = 0;
  while (SDL_PollEvent(&event))
  {

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
      if(currentScene == 1)
      {
        processControlsGame(event.key.keysym.sym, event.type);
      }
    }

    if (event.type == SDL_WINDOWEVENT_CLOSE)
    {
      if (window)
      {
        SDL_DestroyWindow(window);
        window = NULL;
        done = 1;
      }
    }
    else if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        done = 1;
        break;
      case SDLK_RETURN:
      case SDLK_KP_ENTER:
        enterPressed = 1;
        break;
      }
    }
    else if (event.type == SDL_KEYUP)
    {
      switch (event.key.keysym.sym)
      {
      case SDLK_RETURN:
      case SDLK_KP_ENTER:
        enterPressed = 0;
        break;
      case SDLK_DOWN:
        cBtnSelected++;
        cBtnSelected = (cBtnSelected + 1) % (nButtons + 1) - 1;
        break;
      case SDLK_UP:
        cBtnSelected--;
        if (cBtnSelected <= -1)
          cBtnSelected = nButtons - 1;
        break;
      }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      switch (event.button.button)
      {
      case SDL_BUTTON_LEFT:
        mouseDown = 1;
        break;
      }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
      switch (event.button.button)
      {
      case SDL_BUTTON_LEFT:
        mouseDown = 0;
        currentHolding = -1;
        processedClick = 0;
        break;
      }
    }
    else if (event.type == SDL_QUIT)
    {
      done = 1;
    }
    else
    {
      //printf("another event.\n");
    }
  }



  


  ///MANAGE MOVEMENT


if(currentScene == 1)
{
  ProcessMovement();
}





  ////////////
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  return done;
}

void customRender(SDL_Renderer *renderer, Sprite *spr, int index, int num)
{
  switch (num)
  {
  case 1:
  {
    if (cMouseOver == index && mouseDown == 1 || currentHolding == index)
    {
      processedClick = 1;
      currentHolding = index;
      int mx, my;
      SDL_GetMouseState(&mx, &my);
      int volume = (int)(((mx - spr->pos.x) * 128) / spr->pos.w);
      if (volume < 0)
        volume = 0;
      Mix_Volume(-1, volume);
      Mix_VolumeMusic(volume);
    }
    SDL_Rect srcRect = {
        0,
        0};
    SDL_Rect posNew = spr->pos;

    SDL_QueryTexture(spr->image, NULL, NULL, &srcRect.w, &srcRect.h);
    srcRect.w = srcRect.w * Mix_Volume(-1, -1) / 128;
    posNew.w = srcRect.w;
    SDL_RenderCopyEx(renderer, spr->image, &srcRect, &posNew, 0, NULL, spr->flipped);
  }
  break;
  }
}
void doRender(SDL_Renderer *renderer)
{
  //set the drawing color to blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  //Clear the screen (to blue)
  SDL_RenderClear(renderer);

  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  //SDL_RenderFillRect(renderer, &rect);
  //SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
  int btnCount = -1;
  for (int o = 0; o < nSprites; o++)
  {
    if (Sprites[o]->visible != 1)
      continue;
    if (Sprites[o]->animated == 1)
    {
      updateAnims(Sprites[o]);
      SDL_Rect srcRect = {
          Sprites[o]->width * Sprites[o]->currentSprite,
          0,
          Sprites[o]->width,
          Sprites[o]->height};
      if (Sprites[o]->body != NULL)
      {
        Sprites[o]->pos.x = Sprites[o]->body->p.x;
        Sprites[o]->pos.y = Sprites[o]->body->p.y;
      }
      
      SDL_Rect newPos1 = Sprites[o]->pos;
      if(Sprites[o]->affectedByCam)
      {
        newPos1.x -= gameCamera.x;
        newPos1.y -= gameCamera.y;
      }
      SDL_RenderCopyEx(renderer, (Sprites[o]->animations[Sprites[o]->currentState].customTex == NULL) ? Sprites[o]->image : Sprites[o]->animations[Sprites[o]->currentState].customTex, &srcRect, &newPos1, 0, NULL, Sprites[o]->flipped);
    }
    else if (Sprites[o]->type == 3 && Sprites[o]->clickEvent != -1)
    {

      customRender(renderer, Sprites[o], o, Sprites[o]->clickEvent);
    }
    else if (Sprites[o]->type == 1)
    {
      btnCount++;

      if (cMouseOver == o || cBtnSelected == btnCount)
      {
        if ((mouseDown == 1 && cMouseOver == o) || (enterPressed == 1 && cBtnSelected == btnCount))
        {
          if (Sprites[o]->autoSize == 1)
          {
            SDL_QueryTexture(Sprites[o]->clickImage, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
            Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
            Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
          }

          SDL_RenderCopy(renderer, Sprites[o]->clickImage, NULL, &Sprites[o]->pos);

          if (processedClick == 0)
          {
            processedClick = 1;
            PlaySoundSingle("CSG_UI_Open_01.mp3", 0);
            if (Sprites[o]->clickEvent != -1)
            {
              //processClickEvent(Sprites[o]->clickEvent);
              if (mouseDown == 1 && cMouseOver == o)
                oldMouseDown = o;
              if (enterPressed == 1 && cBtnSelected == btnCount)
                oldenterPressed = o;
            }
          }
        }
        else
        {
          if (Sprites[o]->autoSize == 1)
          {
            SDL_QueryTexture(Sprites[o]->hoverImage, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
            Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
            Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
          }
          if (Sprites[o]->body != NULL)
          {
            Sprites[o]->pos.x = Sprites[o]->body->p.x;
            Sprites[o]->pos.y = Sprites[o]->body->p.y;
          }
    SDL_Rect newPos = Sprites[o]->pos;
    if(Sprites[o]->affectedByCam)
          {
            newPos.x -= gameCamera.x;
            newPos.y -= gameCamera.y;
          }
          SDL_RenderCopy(renderer, Sprites[o]->hoverImage, NULL, &newPos);
        }
      }
      else
      {
        if (Sprites[o]->autoSize == 1)
        {
          SDL_QueryTexture(Sprites[o]->image, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
          Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
          Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
        }

        SDL_RenderCopy(renderer, Sprites[o]->image, NULL, &Sprites[o]->pos);
      }
      if (oldMouseDown == o && mouseDown != 1)
      {
        oldMouseDown = -1;
        if(Sprites[o]->clickEvent == 0)
        {
          (*Sprites[o]->clickFunc)(Sprites[o]);

        }
        else
        {
        processClickEvent(Sprites[o]->clickEvent);
        }
        
        processedClick = 0;
      }
      else if (oldenterPressed == o && enterPressed != 1)
      {
        oldenterPressed = -1;
        if(Sprites[o]->clickEvent == 0)
        {
          (*Sprites[o]->clickFunc)(Sprites[o]);

        }
        else
        {
        processClickEvent(Sprites[o]->clickEvent);
        }
        
                processedClick = 0;
      }
    }
    else
    {

SDL_Rect newPos = Sprites[o]->pos;
    if(Sprites[o]->affectedByCam)
          {
            newPos.x -= gameCamera.x;
            newPos.y -= gameCamera.y;
          }
      if (Sprites[o]->autoSize == 1)
      {
        SDL_QueryTexture(Sprites[o]->image, NULL, NULL, &(Sprites[o]->pos.w), &(Sprites[o]->pos.h));
        Sprites[o]->pos.h = (int)(Sprites[o]->pos.h * Sprites[o]->scale);
        Sprites[o]->pos.w = (int)(Sprites[o]->pos.w * Sprites[o]->scale);
      }
      SDL_RenderCopy(renderer, Sprites[o]->image, NULL, &newPos);
    }
  }
  SDL_Rect Textpos = {40, 20};
  /*SDL_QueryTexture(textTex, NULL, NULL, &(Textpos.w), &(Textpos.h));
  SDL_RenderCopy(renderer, textTex, NULL, &Textpos);*/
  if(currentScene == 1) gameRender(renderer);
  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

void updateLogic()
{
  checkMouse();
  if (currentScene==1)
  {
    updatePhysics();
  }
  globalTime++;
}
int main(int argc, char *argv[])
{
  // Declare a window
  // Declare a renderer

  SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2
  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window",           // window title
                            SDL_WINDOWPOS_UNDEFINED, // initial x position
                            SDL_WINDOWPOS_UNDEFINED, // initial y position
                            gameWidth,               // width, in pixels
                            gameHeight,              // height, in pixels
                            0                        // flags
  );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  MainRenderer = renderer;
  SDL_RenderSetLogicalSize(renderer, gameWidth, gameHeight);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

  //PlaySound("CSG_BlueSky_Loop.mp3", -1);
  TTF_Init();

  police = TTF_OpenFont("arnold.TTF", 30);

/*
  TTF_Init();
  TTF_Font *police = TTF_OpenFont("arnold.TTF", 65);
  if (police == NULL)
    printf("Failed to load font\n");
  SDL_Color couleurNoire = {255, 255, 255};*/
  /*SDL_Surface *texte = TTF_RenderText_Blended(police, "Donkey Dash!", couleurNoire);
  if (texte == NULL)
    printf("Failed To Create text\n");

  textTex = SDL_CreateTextureFromSurface(renderer, texte);
  SDL_FreeSurface(texte);
*/
  //load the bg
  //loadBG();
  //loadMenu();
  // The window is open: enter program loop (see SDL_PollEvent)

  //loadGame();
  loadScene(0);
  //Event loop
  while (!done)
  {
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

  // Clean up
  SDL_Quit();
  return 0;
}
