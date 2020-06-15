#ifndef BB_H_INCLUDED
#define BB_H_INCLUDED
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include "chipmunk/chipmunk_private.h"
#include <SDL2/SDL_ttf.h>

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
  cpBody *body;
  int totalAnims;
  int affectedByCam;
  AnimState animations[100];
  int currentState;
  int currentSprite;
  int flipped;
  int animated;
  int clickEvent;
  void (*clickFunc)(struct _s*);
  int type;
  int visible;
  int order;
  int autoSize;
  float scale;
} Sprite;

/**
* @struct Player
* @brief struct for player
*/

typedef struct 
{
  int lives;
  int score;
  int maxlives;
  cpBody *playerBody;
  cpShape *playerShape;
  Sprite *playerSprite;
  int arrowKeys[4];
  SDL_Keycode codeKeys[4];
  cpVect moveDir;
  cpBool grounded;
  int doubleJumped;
  cpBool lastJumpState;
  cpFloat remainingBoost;
} Player;
typedef struct
{
  char name[100];
  char over[100];
  char clicked[100];
} imageData;

typedef struct _camera
{
  int x;
  int y;

} Camera;
extern int gameHeight;
extern int gameWidth;
extern int globalTime;
extern int currentScene;
extern TTF_Font *police;
extern Camera gameCamera;
extern SDL_Renderer *MainRenderer;
void loadSave(struct _s *saveBtn);
Sprite *MakeSpriteHack(imageData data, int type);
SDL_Texture* getTextureHack(char name[]);
void gameRender(SDL_Renderer * renderer);
void addBox(cpSpace *space, int px, int py, int sx, int sy, imageData bgData,Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer);
void updatePhysics();
void deleteAllSprites();
void ProcessMovement();
void processControlsGame(SDL_Keycode key, SDL_EventType type);
void loadGame(Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer);
void loadMenu(Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer);
void loadSettings(Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer);
Sprite* MakeSprite(imageData data, int type, Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer);
int deleteSprite(Sprite* Sprites[], int *nSprites, int index);
void deleteAll(Sprite *Sprites[], int *nSprites, int *nButtons);
void deleteFrom(Sprite *Sprites[], int *nSprites, int *nButtons, int index);
SDL_Texture* getTexture(char name[] , SDL_Renderer * renderer);
#endif // BB_H_INCLUDED
