#include <stdio.h>
#include "funcs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include <string.h>

void loadMenu(Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer)
{




  deleteAll(Sprites, nSprites, nButtons);
  imageData bgData = {"background.png"};
  Sprite *bg = MakeSprite(bgData, 0, Sprites, nSprites, nButtons, renderer);
  bg->pos.x = 0;
  bg->pos.y = 0;
  bg->autoSize = 1;
  bg->scale = 1;



  imageData closeData = {"close0001.png", "close0002.png", "close0003.png"};

  Sprite *closeBtn = MakeSprite(closeData, 1, Sprites, nSprites, nButtons, renderer);
  closeBtn->pos.x = gameWidth - 200;
  closeBtn->pos.y = 25;
  closeBtn->autoSize = 1;
  closeBtn->clickEvent = 5;
  closeBtn->scale = 0.7;

  imageData fullScreenData = {"fullscreen0001.png", "fullscreen0002.png", "fullscreen0003.png"};

  Sprite *fullscreenBtn = MakeSprite(fullScreenData, 1, Sprites, nSprites, nButtons, renderer);
  fullscreenBtn->pos.x = gameWidth - 300;
  fullscreenBtn->pos.y = 35;
  fullscreenBtn->autoSize = 1;
  fullscreenBtn->clickEvent = 3;
  fullscreenBtn->scale = 0.7;




  imageData playBtnData = {"startbtn0001.png", "startbtn0002.png", "startbtn0003.png"};
  Sprite *playBtn = MakeSprite(playBtnData, 1, Sprites, nSprites, nButtons, renderer);
  playBtn->pos.x = gameWidth / 2;
  playBtn->pos.y = 300;
  playBtn->autoSize = 1;
  playBtn->scale = 1;
  playBtn->clickEvent = 1;

  imageData customData = {"customize0001.png", "customize0002.png", "customize0003.png"};

  Sprite *customizeBtn = MakeSprite(customData, 1, Sprites, nSprites, nButtons, renderer);
  customizeBtn->pos.x = gameWidth / 2;
  customizeBtn->pos.y = 450;
  customizeBtn->autoSize = 1;
  customizeBtn->scale = 1;
  customizeBtn->clickEvent = 2;

  imageData settingsData = {"settings0001.png", "settings0002.png", "settings0003.png"};

  Sprite *settingsBtn = MakeSprite(settingsData, 1, Sprites, nSprites, nButtons, renderer);
  settingsBtn->pos.x = gameWidth / 2;
  settingsBtn->pos.y = 600;
  settingsBtn->autoSize = 1;
  settingsBtn->scale = 1;
  settingsBtn->clickEvent = 4;
}



void loadSettings(Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer)
{

  deleteAll(Sprites, nSprites, nButtons);
  imageData bgData = {"bg2.png"};
  Sprite *bg = MakeSprite(bgData, 0, Sprites, nSprites, nButtons, renderer);
  bg->pos.x = 0;
  bg->pos.y = 0;
  bg->autoSize = 1;
  bg->scale = 1;



  imageData closeData = {"close0001.png", "close0002.png", "close0003.png"};

  Sprite *closeBtn = MakeSprite(closeData, 1, Sprites, nSprites, nButtons, renderer);
  closeBtn->pos.x = gameWidth - 200;
  closeBtn->pos.y = 25;
  closeBtn->autoSize = 1;
  closeBtn->clickEvent = 5;
  closeBtn->scale = 0.7;




  imageData settingsMenu = {"settingsMenu.png"};
  Sprite *sm = MakeSprite(settingsMenu, 0, Sprites, nSprites, nButtons, renderer);
  sm->pos.x = gameWidth / 2 - sm->pos.w / 2;
  sm->pos.y = gameHeight / 2 - sm->pos.h / 2;
  sm->autoSize = 1;
  sm->scale = 1;

  imageData soundData = {"soundBar2.png"};
  Sprite *soundBar = MakeSprite(soundData, 3, Sprites, nSprites, nButtons, renderer);
  soundBar->pos.x = gameWidth / 2 - sm->pos.w / 2 + 182;
  soundBar->pos.y = gameHeight / 2 - sm->pos.h / 2 + 196;
  soundBar->clickEvent = 1;

  imageData fullScreenData = {"fullscreenbtn0001.png", "fullscreenbtn0002.png", "fullscreenbtn0003.png"};

  Sprite *fullscreenBtn = MakeSprite(fullScreenData, 1, Sprites, nSprites, nButtons, renderer);
  fullscreenBtn->pos.x = gameWidth / 2 - fullscreenBtn->pos.w / 2 - 10;
  fullscreenBtn->pos.y = gameHeight / 2 - sm->pos.h / 2 + 262;
  fullscreenBtn->autoSize = 1;
  fullscreenBtn->clickEvent = 3;
  fullscreenBtn->scale = 1;

  imageData okData = {"okbtn0001.png", "okbtn0002.png", "okbtn0003.png"};

  Sprite *ok = MakeSprite(okData, 1, Sprites, nSprites, nButtons, renderer);
  ok->pos.x = gameWidth / 2 - ok->pos.w / 2;
  ok->pos.y = gameHeight / 2 - sm->pos.h / 2 + 360;
  ok->autoSize = 1;
  ok->clickEvent = 6;
  ok->scale = 0.7;
}