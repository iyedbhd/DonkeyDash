/**
* @file Game.c
* @brief Game Script.
* @author IyedBHD
* @version 1
* @date Jun 12, 2020
*
* Game main program
*
*/


#include <stdio.h>
#include "funcs.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include <string.h>
#include <SDL2/SDL_ttf.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


#define PLAYER_VELOCITY 50.0

#define PLAYER_GROUND_ACCEL_TIME 2
#define PLAYER_GROUND_ACCEL (PLAYER_VELOCITY / PLAYER_GROUND_ACCEL_TIME)

#define PLAYER_AIR_ACCEL_TIME 2
#define PLAYER_AIR_ACCEL (PLAYER_VELOCITY / PLAYER_AIR_ACCEL_TIME)

#define JUMP_HEIGHT 100.0
#define JUMP_BOOST_HEIGHT 80.0
#define FALL_VELOCITY 900.0
#define GRAVITY -30.0

cpSpace *_space = NULL;
/*cpFloat player.remainingBoost = 0;
cpBool player.grounded = cpFalse;
int player.doubleJumped = 0;
cpBool player.lastJumpState = cpFalse;
cpVect moveDir;*/
Camera gameCamera;
float oldVelX,oldVelY,Accleration;
enum CollisionTypes {
	COLLISION_TYPE_ONE_WAY = 1,
};
typedef struct 
{
    int posX;
    int posY;
    int lives;
    int maxLives;
    int score;
} SaveFile;
Player Players[5];
int numPlayers = 0;
typedef struct OneWayPlatform {
	cpVect n; // direction objects may pass through
} OneWayPlatform;

static OneWayPlatform platformInstance;

void SelectPlayerGroundNormal(cpBody *body, cpArbiter *arb, cpVect *groundNormal)
{
  cpVect n = cpvneg(cpArbiterGetNormal(arb));
  if (n.y < groundNormal->y)
  {
    (*groundNormal) = n;
  }
}
  SDL_Texture *heartTex;
  SDL_Texture *heartTex2;


void playerUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{

  
    int jumpState = (Players[0].moveDir.y < 0.0f);

    // Grab the grounding normal from last frame
    cpVect groundNormal = cpvzero;
    cpBodyEachArbiter(Players[0].playerBody, (cpBodyArbiterIteratorFunc)SelectPlayerGroundNormal, &groundNormal);

    Players[0].grounded = (groundNormal.y < 0.0);
    if(Players[0].grounded && Players[0].playerSprite->currentState == 2)
    {
        Players[0].playerSprite->currentState = 0;
    }
    else if(!Players[0].grounded && Players[0].playerSprite->currentState != 2 && (body->v.y < -50 || body->v.y > 50))
    {
        Players[0].playerSprite->currentState = 2;
    }
    //printf("ground normal y = %.6f\n", groundNormal.y);
    //if(groundNormal.y > 0.0f) player.remainingBoost = 0.0f;

    //Do a normal-ish update
    cpBool boost = (jumpState && Players[0].remainingBoost > 0.0f);
    cpVect g = (gravity);
    cpBodyUpdateVelocity(body, g, damping, dt);

    // Target horizontal speed for air/ground control
    cpFloat target_vx = PLAYER_VELOCITY * Players[0].moveDir.x;

    // Update the surface velocity and friction
    // Note that the "feet" move in the opposite direction of the player.
    cpVect surface_v = cpv(-target_vx, 0.0);
    Players[0].playerShape->surfaceV = surface_v;
    Players[0].playerShape->u = (Players[0].grounded ? (-PLAYER_GROUND_ACCEL / GRAVITY) : 0.0);

    // Apply air control if not player.grounded
    if (!Players[0].grounded)
    {
      // Smoothly accelerate the velocity
      Players[0].playerBody->v.x = cpflerpconst(Players[0].playerBody->v.x, target_vx, PLAYER_AIR_ACCEL * dt);
    }
    else
    {

      
    }
    
    body->v.y = cpfclamp(body->v.y, -FALL_VELOCITY, INFINITY);




  
  

  if(numPlayers > 0)
  {
  Accleration = abs((float)(Players[0].playerBody->v.x-oldVelX)/(float)dt)   +    abs((float)(Players[0].playerBody->v.y-oldVelY)/(float)dt);
  oldVelX = Players[0].playerBody->v.x;
  oldVelY = Players[0].playerBody->v.y;
  }

}

void playerUpdateVelocity2(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{

  
    int jumpState = (Players[1].moveDir.y < 0.0f);

    // Grab the grounding normal from last frame
    cpVect groundNormal = cpvzero;
    cpBodyEachArbiter(Players[1].playerBody, (cpBodyArbiterIteratorFunc)SelectPlayerGroundNormal, &groundNormal);

    Players[1].grounded = (groundNormal.y < 0.0);
    if(Players[1].grounded && Players[1].playerSprite->currentState == 2)
    {
        Players[1].playerSprite->currentState = 0;
    }
    else if(!Players[1].grounded && Players[1].playerSprite->currentState != 2 && (body->v.y < -50 || body->v.y > 50))
    {
        Players[1].playerSprite->currentState = 2;
    }
    //printf("ground normal y = %.6f\n", groundNormal.y);
    //if(groundNormal.y > 0.0f) player.remainingBoost = 0.0f;

    //Do a normal-ish update
    cpBool boost = (jumpState && Players[1].remainingBoost > 0.0f);
    cpVect g = (gravity);
    cpBodyUpdateVelocity(body, g, damping, dt);

    // Target horizontal speed for air/ground control
    cpFloat target_vx = PLAYER_VELOCITY * Players[1].moveDir.x;

    // Update the surface velocity and friction
    // Note that the "feet" move in the opposite direction of the player.
    cpVect surface_v = cpv(-target_vx, 0.0);
    Players[1].playerShape->surfaceV = surface_v;
    Players[1].playerShape->u = (Players[1].grounded ? (-PLAYER_GROUND_ACCEL / GRAVITY) : 0.0);

    // Apply air control if not player.grounded
    if (!Players[1].grounded)
    {
      // Smoothly accelerate the velocity
      Players[1].playerBody->v.x = cpflerpconst(Players[1].playerBody->v.x, target_vx, PLAYER_AIR_ACCEL * dt);
    }
    else
    {

      
    }
    
    body->v.y = cpfclamp(body->v.y, -FALL_VELOCITY, INFINITY);




  
  

  if(numPlayers > 0)
  {
  Accleration = abs((float)(Players[0].playerBody->v.x-oldVelX)/(float)dt)   +    abs((float)(Players[0].playerBody->v.y-oldVelY)/(float)dt);
  oldVelX = Players[0].playerBody->v.x;
  oldVelY = Players[0].playerBody->v.y;
  }

}

void playerUpdateVelocity3(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{

  
    int jumpState = (Players[2].moveDir.y < 0.0f);

    // Grab the grounding normal from last frame
    cpVect groundNormal = cpvzero;
    cpBodyEachArbiter(Players[2].playerBody, (cpBodyArbiterIteratorFunc)SelectPlayerGroundNormal, &groundNormal);

    Players[2].grounded = (groundNormal.y < 0.0);
    if(Players[2].grounded && Players[2].playerSprite->currentState == 2)
    {
        Players[2].playerSprite->currentState = 0;
    }
    else if(!Players[2].grounded && Players[2].playerSprite->currentState != 2 && (body->v.y < -50 || body->v.y > 50))
    {
        Players[2].playerSprite->currentState = 2;
    }
    //printf("ground normal y = %.6f\n", groundNormal.y);
    //if(groundNormal.y > 0.0f) player.remainingBoost = 0.0f;

    //Do a normal-ish update
    cpBool boost = (jumpState && Players[2].remainingBoost > 0.0f);
    cpVect g = (gravity);
    cpBodyUpdateVelocity(body, g, damping, dt);

    // Target horizontal speed for air/ground control
    cpFloat target_vx = PLAYER_VELOCITY * Players[2].moveDir.x;

    // Update the surface velocity and friction
    // Note that the "feet" move in the opposite direction of the player.
    cpVect surface_v = cpv(-target_vx, 0.0);
    Players[2].playerShape->surfaceV = surface_v;
    Players[2].playerShape->u = (Players[2].grounded ? (-PLAYER_GROUND_ACCEL / GRAVITY) : 0.0);

    // Apply air control if not player.grounded
    if (!Players[2].grounded)
    {
      // Smoothly accelerate the velocity
      Players[2].playerBody->v.x = cpflerpconst(Players[2].playerBody->v.x, target_vx, PLAYER_AIR_ACCEL * dt);
    }
    else
    {

      
    }
    
    body->v.y = cpfclamp(body->v.y, -FALL_VELOCITY, INFINITY);




  
  

  if(numPlayers > 0)
  {
  Accleration = abs((float)(Players[0].playerBody->v.x-oldVelX)/(float)dt)   +    abs((float)(Players[0].playerBody->v.y-oldVelY)/(float)dt);
  oldVelX = Players[0].playerBody->v.x;
  oldVelY = Players[0].playerBody->v.y;
  }

}

void initSpace()
{
  cpSpace *space = cpSpaceNew();
  space->iterations = 60;
  space->gravity = cpv(0, -GRAVITY);
  //	space->sleepTimeThreshold = 1000;

  cpBody *body, *staticBody = cpSpaceGetStaticBody(space);
  cpShape *shape;

  /*
	// Create segments around the edge of the screen.
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(0,0), cpv(800,0), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	//cpShapeSetFilter(shape, NOT_GRABBABLE_FILTER);

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(0,0), cpv(0,480), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	//cpShapeSetFilter(shape, NOT_GRABBABLE_FILTER);

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(800,480), cpv(0,480), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	//cpShapeSetFilter(shape, NOT_GRABBABLE_FILTER);

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(800,480), cpv(800,0), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	//cpShapeSetFilter(shape, NOT_GRABBABLE_FILTER);
  */

  // Set up the player
 // Player player;
  body = cpSpaceAddBody(space, cpBodyNew(1.0f, INFINITY));
  body->p = cpv(50, 500);
  body->velocity_func = playerUpdateVelocity;
  Players[0].playerBody = body;
  Players[0].arrowKeys[0] = 0;Players[0].arrowKeys[1] = 0;Players[0].arrowKeys[2] = 0;Players[0].arrowKeys[3] = 0;
  Players[0].codeKeys[0] = SDLK_q;Players[0].codeKeys[1] = SDLK_z;Players[0].codeKeys[2] = SDLK_s;Players[0].codeKeys[3] = SDLK_d;
  numPlayers++;

  //playerBody = body;

  shape = cpSpaceAddShape(space, cpBoxShapeNew2(body, cpBBNew(0.0, 0, 60.0, 80), 2.0));
  //	shape = cpSpaceAddShape(space, cpSegmentShapeNew(playerBody, cpvzero, cpv(0, radius), radius));
  shape->e = 0.0f;
  shape->u = 0.0f;
  shape->type = 1;
  //playerShape = shape;
  Players[0].playerShape = shape;

  // Add some boxes to jump on
  /*for(int i=0; i<6; i++){
		for(int j=0; j<3; j++){
			body = cpSpaceAddBody(space, cpBodyNew(4.0f, INFINITY));
			body->p = cpv(100 + j*60, -200 + i*60);

			shape = cpSpaceAddShape(space, cpBoxShapeNew(body, 50, 50, 0.0));
			shape->e = 0.0f; shape->u = 0.7f;
		}
	}*/

  _space = space;
}



void addBox(cpSpace *space, int px, int py, int sx, int sy, imageData bgData,Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer)
{
cpVect tris[] = {
		cpv(0,0),
		cpv(  sx, 0),
		cpv(  sx, sy),
		cpv(  0, sy)
	};

cpBody *staticBody = cpSpaceGetStaticBody(space);

  //staticBody->p = cpv(px + sx / 2, py + sy / 2);
  cpShape *shape;
  			cpVect offset =  cpv(px , py );

  //shape = cpSpaceAddShape(space, cpBoxShapeNew(staticBody, sx, sy, 0));
shape = cpSpaceAddShape(space, cpPolyShapeNew(staticBody, 4, tris, cpTransformTranslate(offset), 0.0));
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
			//cpShapeSetFilter(shape, NOT_GRABBABLE_FILTER);

  /*shape->e = 0;
  shape->u = 0;*/
  //cpBodySetType(staticBody, CP_BODY_TYPE_STATIC);

    /*
  cpBody *staticBody = cpSpaceGetStaticBody(space);

  //staticBody->p = cpv(px + sx / 2, py + sy / 2);
  cpShape *shape;
  shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(px,py), cpv(px+sx,py), 0.0f));
  //cpBoxShapeNew(staticBody, sx, sy, 0));
  shape->e = 1.0f;
  shape->u = 1.0f;
  	cpShapeSetCollisionType(shape, COLLISION_TYPE_ONE_WAY);
	cpShapeSetUserData(shape, &platformInstance);
*/






  Sprite *bg = MakeSprite(bgData, 0, Sprites, nSprites, nButtons, renderer);
  bg->pos.x = px;
  bg->pos.y = py;
  bg->pos.w = sx;
  bg->pos.h = sy;
  bg->affectedByCam = 1;

  //bg->autoSize = 1;
  bg->scale = 1;
  bg->body = staticBody;
}



void processControlsGame(SDL_Keycode key, SDL_EventType type)
{
  for(int s=0;s<numPlayers;s++)
  {
    if(key == Players[s].codeKeys[1])
    {
        Players[s].arrowKeys[1] = type == SDL_KEYDOWN ? 1 : 0;
    }
    else if(key == Players[s].codeKeys[2])
    {
        Players[s].arrowKeys[2] = type == SDL_KEYDOWN ? 1 : 0;
    }
    else if(key == Players[s].codeKeys[0])
    {
        Players[s].arrowKeys[0] = type == SDL_KEYDOWN ? 1 : 0;
    }
    else if(key == Players[s].codeKeys[3])
    {
        Players[s].arrowKeys[3] = type == SDL_KEYDOWN ? 1 : 0;
    }
  }
}


void ProcessMovement()
{
  for(int s=0;s<numPlayers;s++)
  {
    if(Players[s].arrowKeys[0] && Players[s].arrowKeys[3] || !Players[s].arrowKeys[0] && !Players[s].arrowKeys[3])
        {
          Players[s].moveDir.x = 0;
                if(Players[s].grounded) Players[s].playerSprite->currentState = 0;
        }
        else if(Players[s].arrowKeys[3])
        {
            Players[s].moveDir.x = 1;
            if(Players[s].grounded) Players[s].playerSprite->currentState = 1;
            Players[s].playerSprite->flipped = 0;
        }
        else if(Players[s].arrowKeys[0])
        {
            Players[s].moveDir.x = -1;
            if(Players[s].grounded) Players[s].playerSprite->currentState = 1;
            Players[s].playerSprite->flipped = 1;
        }



        if(Players[s].arrowKeys[1] && Players[s].arrowKeys[2] || !Players[s].arrowKeys[1] && !Players[s].arrowKeys[2])
        {
          Players[s].moveDir.y = 0;
        }
        else if(Players[s].arrowKeys[1])
        {
          Players[s].moveDir.y = -1;
          //playerSprite->currentState = 2;
        }
        else if(Players[s].arrowKeys[2])
        {
          Players[s].moveDir.y = 1;
        }
  }
}



void updatePhysics()
{
  double dt = 0.2;

  for(int s=0;s<numPlayers;s++)
  {
  int jumpState = (Players[s].moveDir.y < 0.0f);
  //printf("jump state = %d\n", jumpState);
  //printf("player.grounded = %d\n", player.grounded);

  // If the jump key was just pressed this frame, jump!
  if (jumpState && !Players[s].lastJumpState && (Players[s].grounded || !Players[s].doubleJumped))
  {
    cpFloat jump_v = -cpfsqrt(2.0 * JUMP_HEIGHT * GRAVITY * -1);
    printf("f = %.5f\n", jump_v);
    Players[s].playerShape->u = (0.0);
    Players[s].playerBody->v = cpvadd(Players[s].playerBody->v, cpv(0.0, jump_v - Players[s].playerBody->v.y));
    if (!Players[s].grounded)
      Players[s].doubleJumped = 1;
    else
      Players[s].doubleJumped = 0;
    //player.remainingBoost = JUMP_BOOST_HEIGHT/jump_v;

  }
        Players[s].lastJumpState = jumpState;

  }
  // Step the space
  cpSpaceStep(_space, dt);
  for(int s=0;s<numPlayers;s++)
  {
    //player.remainingBoost -= dt;

    //printf("gonna print images.\n");

    if (Players[s].playerBody->p.y > 1500)
    {
      Players[s].playerBody->p.x = 50;
      Players[s].playerBody->p.y = 500;
      Players[s].lives--;
      Players[s].score -= 5;
    }

    Players[s].playerSprite->pos.x = floor(Players[s].playerBody->p.x);
    Players[s].playerSprite->pos.y = floor(Players[s].playerBody->p.y);

  }

  if(numPlayers>0)
  {
    //printf("pos = %.2f , %.2f\n", playerBody->p.x, playerBody->p.y);
    gameCamera.x = Players[0].playerSprite->pos.x - gameWidth/2;
    if(Players[0].playerSprite->pos.y< gameCamera.y - (-100))
    {
        gameCamera.y = Players[0].playerSprite->pos.y + (-100);
    }
    else if(Players[0].playerSprite->pos.y> gameCamera.y + (500))
    {
        gameCamera.y = Players[0].playerSprite->pos.y - (500);
    }
  }
}

void saveGame(struct _s *saveBtn)
{
    FILE *filePointer ;  
    filePointer = fopen("saveFile.bin", "wb") ; 
      
    if ( filePointer == NULL ) 
    { 
        printf( "Failed to open save file." ) ; 
    } 
    else
    { 
        SaveFile save = {Players[0].playerBody->p.x,Players[0].playerBody->p.y,Players[0].lives,Players[0].maxlives,Players[0].score};

        // Write the dataToBeWritten into the file 
        fwrite(&save, sizeof(SaveFile), 1, filePointer); 
  
        
        // Closing the file using fclose() 
        fclose(filePointer) ; 
        printf("Data successfully Saved\n"); 
    } 
}



void addPlayer(struct _s *btn)
{
  if(numPlayers == 1)
  {
  cpBody *body = cpSpaceAddBody(_space, cpBodyNew(1.0f, INFINITY));
  body->p = cpv(50, 500);
  body->velocity_func = playerUpdateVelocity2;
  Players[1].playerBody = body;
  Players[1].arrowKeys[0] = 0;Players[1].arrowKeys[1] = 0;Players[1].arrowKeys[2] = 0;Players[1].arrowKeys[3] = 0;
  Players[1].codeKeys[0] = SDLK_LEFT;Players[1].codeKeys[1] = SDLK_UP;Players[1].codeKeys[2] = SDLK_DOWN;Players[1].codeKeys[3] = SDLK_RIGHT;
  numPlayers++;
  //playerBody = body;
  Players[1].lives = 3;
  Players[1].maxlives = 5;
  Players[1].score = 100;

  cpShape *shape = cpSpaceAddShape(_space, cpBoxShapeNew2(body, cpBBNew(0.0, 0, 60.0, 80), 2.0));
  //	shape = cpSpaceAddShape(space, cpSegmentShapeNew(playerBody, cpvzero, cpv(0, radius), radius));
  shape->e = 0.0f;
  shape->u = 0.0f;
  shape->type = 1;
  //playerShape = shape;
  Players[1].playerShape = shape;



  

  imageData donkeyData = {"donkeywhiteidle.png"};

  Players[1].playerSprite = MakeSpriteHack(donkeyData, 0);
  Players[1].playerSprite->animated = 1;
  Players[1].playerSprite->pos.x = 0;
  Players[1].playerSprite->pos.y = 0;
  Players[1].playerSprite->pos.w = 254;
  Players[1].playerSprite->pos.h = 295;
  Players[1].playerSprite->autoSize = 1;
  Players[1].playerSprite->scale = 0.5;
  Players[1].playerSprite->currentSprite = 0;
  AnimState donkeyIdle = {0, 20, 129, 181, 2, NULL};
  AnimState donkeyWalk = {0, 18, 126, 182, 2, getTextureHack("donkeywhitewalk.png")};
  AnimState donkeyJump = {0, 0, 123, 180, 2, getTextureHack("donkeywhitejump.png")};
  Players[1].playerSprite->animations[0] = donkeyIdle;
  Players[1].playerSprite->animations[1] = donkeyWalk;
  Players[1].playerSprite->animations[2] = donkeyJump;
  Players[1].playerSprite->affectedByCam = 1;
  Players[1].playerSprite->totalAnims = 3;
  Players[1].playerSprite->currentState = 0;
  Players[1].playerSprite->flipped = 0;




  }
  else if(numPlayers == 2)
  {
  cpBody *body = cpSpaceAddBody(_space, cpBodyNew(1.0f, INFINITY));
  body->p = cpv(50, 500);
  body->velocity_func = playerUpdateVelocity3;
  Players[2].playerBody = body;
  Players[2].arrowKeys[0] = 0;Players[2].arrowKeys[1] = 0;Players[2].arrowKeys[2] = 0;Players[2].arrowKeys[3] = 0;
  Players[2].codeKeys[0] = SDLK_KP_4;Players[2].codeKeys[1] = SDLK_KP_8;Players[2].codeKeys[2] = SDLK_KP_5;Players[2].codeKeys[3] = SDLK_KP_6;
  numPlayers++;
  //playerBody = body;
  Players[2].lives = 3;
  Players[2].maxlives = 5;
  Players[2].score = 100;

  cpShape *shape = cpSpaceAddShape(_space, cpBoxShapeNew2(body, cpBBNew(0.0, 0, 60.0, 80), 2.0));
  //	shape = cpSpaceAddShape(space, cpSegmentShapeNew(playerBody, cpvzero, cpv(0, radius), radius));
  shape->e = 0.0f;
  shape->u = 0.0f;
  shape->type = 1;
  //playerShape = shape;
  Players[2].playerShape = shape;



  

  imageData donkeyData = {"donkeyblueidle.png"};

  Players[2].playerSprite = MakeSpriteHack(donkeyData, 0);
  Players[2].playerSprite->animated = 1;
  Players[2].playerSprite->pos.x = 0;
  Players[2].playerSprite->pos.y = 0;
  Players[2].playerSprite->pos.w = 254;
  Players[2].playerSprite->pos.h = 295;
  Players[2].playerSprite->autoSize = 1;
  Players[2].playerSprite->scale = 0.5;
  Players[2].playerSprite->currentSprite = 0;
  AnimState donkeyIdle = {0, 20, 129, 181, 2, NULL};
  AnimState donkeyWalk = {0, 18, 126, 182, 2, getTextureHack("donkeybluewalk.png")};
  AnimState donkeyJump = {0, 0, 123, 180, 2, getTextureHack("donkeybluejump.png")};
  Players[2].playerSprite->animations[0] = donkeyIdle;
  Players[2].playerSprite->animations[1] = donkeyWalk;
  Players[2].playerSprite->animations[2] = donkeyJump;
  Players[2].playerSprite->affectedByCam = 1;
  Players[2].playerSprite->totalAnims = 3;
  Players[2].playerSprite->currentState = 0;
  Players[2].playerSprite->flipped = 0;




  }


}


void loadSave(struct _s *saveBtn)
{
    printf("i loaded game");
    FILE *filePointer ;  
    filePointer = fopen("saveFile.bin", "rb") ; 
      
    if ( filePointer == NULL ) 
    { 
        printf( "Failed to open save file." ) ; 
    } 
    else
    { 
          
        SaveFile save;

        // Write the dataToBeWritten into the file 
        fread(&save, sizeof(SaveFile), 1, filePointer); 
        Players[0].playerBody->p.x = save.posX;
        Players[0].playerBody->p.y = save.posY;
        Players[0].lives = save.lives;
        Players[0].maxlives = save.maxLives;
        Players[0].score = save.score;

          
        // Closing the file using fclose() 
        fclose(filePointer) ; 
        printf("Data successfully Saved\n"); 
    } 
}

void loadGame(Sprite* Sprites[], int *nSprites, int *nButtons, SDL_Renderer * renderer)
{
  deleteAll(Sprites, nSprites, nButtons);
  gameCamera.y = gameHeight/2-300;
  gameCamera.x = 0;
    SDL_Surface *heartPic = IMG_Load("hearton.png");
  SDL_Surface *heartPicOff = IMG_Load("heartoff.png");
  heartTex = SDL_CreateTextureFromSurface(renderer, heartPic);
  heartTex2 = SDL_CreateTextureFromSurface(renderer, heartPicOff);
  SDL_FreeSurface(heartPic);
  SDL_FreeSurface(heartPicOff);

  Players[0].lives = 3;
  Players[0].maxlives = 5;
  Players[0].score = 100;
  initSpace();
  //addSprite("images/gamebg1", 0, 0, 0);
  imageData bgData = {"assets/bg.png"};
  Sprite *bg = MakeSprite(bgData, 0, Sprites, nSprites, nButtons, renderer);
  bg->pos.x = 0;
  bg->pos.y = 0;

  bg->autoSize = 1;
  bg->scale = 1;
  imageData blackRect = {"blackrec.png"};
  imageData block0 = {"assets/block0.png"};
  imageData block1 = {"assets/block1.png"};
  imageData block2 = {"assets/block2.png"};
  imageData block3 = {"assets/block3.png"};



///SPAWNING TILES




  addBox(_space, -170, 600, 100, 100,block2,Sprites, nSprites, nButtons, renderer);
  addBox(_space, -70, 600, 100, 100,block3,Sprites, nSprites, nButtons, renderer);


  addBox(_space, 30, 700, 100, 100,block2,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 130, 700, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 230, 700, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 330, 700, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 430, 700, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 530, 700, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 630, 700, 100, 100,block3,Sprites, nSprites, nButtons, renderer);


  addBox(_space, 730, 600, 100, 100,block2,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 830, 600, 100, 100,block3,Sprites, nSprites, nButtons, renderer);




  addBox(_space, 930, 500, 100, 100,block2,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 1030, 500, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 1130, 500, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 1230, 500, 100, 100,block3,Sprites, nSprites, nButtons, renderer);

  addBox(_space, 1530, 500, 100, 100,block2,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 1630, 500, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 1730, 500, 100, 100,block1,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 1830, 500, 100, 100,block3,Sprites, nSprites, nButtons, renderer);





  addBox(_space, 1930, 400, 100, 100,block0,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 2030, 300, 100, 100,block0,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 2130, 200, 100, 100,block0,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 2230, 100, 100, 100,block0,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 2330, 0, 100, 100,block0,Sprites, nSprites, nButtons, renderer);
  addBox(_space, 2430, -100, 100, 100,block0,Sprites, nSprites, nButtons, renderer);

  /*addBox(_space, 500, 100, 100, 100,blackRect);
  addBox(_space, -500, 500, 10000, 100,blackRect);*/

  /*addBox(_space, 70, 360, 260, 30);
    addBox(_space, 470, 360, 260, 30);*/





//SPAWNING DECORATIONS




  imageData signPic = {"assets/sign.png"};
  Sprite *sign = MakeSprite(signPic, 0, Sprites, nSprites, nButtons, renderer);
  sign->pos.x = 300;
  sign->pos.y = 620;
  sign->autoSize = 1;
  sign->scale = 0.4;
  sign->affectedByCam = 1;







  imageData donkeyData = {"donkeyanimation.png"};

  Players[0].playerSprite = MakeSprite(donkeyData, 0, Sprites, nSprites, nButtons, renderer);
  Players[0].playerSprite->animated = 1;
  Players[0].playerSprite->pos.x = 0;
  Players[0].playerSprite->pos.y = 0;
  Players[0].playerSprite->pos.w = 254;
  Players[0].playerSprite->pos.h = 295;
  Players[0].playerSprite->autoSize = 1;
  Players[0].playerSprite->scale = 0.5;
  Players[0].playerSprite->currentSprite = 0;
  AnimState donkeyIdle = {0, 20, 125, 177, 2, NULL};
  AnimState donkeyWalk = {0, 18, 123, 180, 2, getTexture("donkeyanimationrun.png", renderer)};
  AnimState donkeyJump = {0, 0, 123, 180, 2, getTexture("donkeyjump.png", renderer)};
  Players[0].playerSprite->animations[0] = donkeyIdle;
  Players[0].playerSprite->animations[1] = donkeyWalk;
  Players[0].playerSprite->animations[2] = donkeyJump;
  Players[0].playerSprite->affectedByCam = 1;
  Players[0].playerSprite->totalAnims = 3;
  Players[0].playerSprite->currentState = 0;
  Players[0].playerSprite->flipped = 0;








  
  imageData saveButtonData = {"save0001.png", "save0002.png", "save0003.png"};

  Sprite *saveBtn = MakeSprite(saveButtonData, 1, Sprites, nSprites, nButtons, renderer);
  saveBtn->pos.x = gameWidth - 120;
  saveBtn->pos.y = 35;
  saveBtn->autoSize = 1;
  saveBtn->clickEvent = 0;
  saveBtn->clickFunc = &saveGame;
  saveBtn->scale = 1;


  imageData loadButtonData = {"load0001.png", "load0002.png", "load0003.png"};

  Sprite *loadBtn = MakeSprite(loadButtonData, 1, Sprites, nSprites, nButtons, renderer);
  loadBtn->pos.x = gameWidth - 120;
  loadBtn->pos.y = 135;
  loadBtn->autoSize = 1;
  loadBtn->clickEvent = 0;
  loadBtn->clickFunc = &loadSave;
  loadBtn->scale = 1;






  imageData addButtonData = {"add0001.png", "add0002.png", "add0003.png"};

  Sprite *addBtn = MakeSprite(addButtonData, 1, Sprites, nSprites, nButtons, renderer);
  addBtn->pos.x = gameWidth - 120;
  addBtn->pos.y = 235;
  addBtn->autoSize = 1;
  addBtn->clickEvent = 0;
  addBtn->clickFunc = &addPlayer;
  addBtn->scale = 1;




}




void gameRender(SDL_Renderer * renderer)
{

    ///VELOCITY TEXT
  SDL_Color couleurNoire = {255, 255, 255};
  char VelX[50];
  char VelY[50];
  char Acc[50];
  sprintf(VelX, "Velocity x: %.3f m/s", Players[0].playerBody->v.x); 
  sprintf(VelY, "Velocity y: %.3f m/s", Players[0].playerBody->v.y); 
  sprintf(Acc, "Acceleration: %.3f m/s/s", Accleration); 
  SDL_Surface *texte = TTF_RenderText_Blended(police, VelX, couleurNoire);
  SDL_Surface *texte2 = TTF_RenderText_Blended(police, VelY, couleurNoire);
  SDL_Surface *texte3 = TTF_RenderText_Blended(police, Acc, couleurNoire);
  SDL_Texture *textTex;
  SDL_Texture *textTex2;
  SDL_Texture *textTex3;
  if (texte == NULL || texte2 == NULL || texte3 == NULL)
  {
  printf("Failed To Create text\n");
  }
  else
  {
  textTex = SDL_CreateTextureFromSurface(renderer, texte);
  textTex2 = SDL_CreateTextureFromSurface(renderer, texte2);
  textTex3 = SDL_CreateTextureFromSurface(renderer, texte3);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(texte2);
  SDL_FreeSurface(texte3);
  SDL_Rect Textpos = {40, 800};
  SDL_Rect Textpos2 = {40, 760};
  SDL_Rect Textpos3 = {40, 720};
  SDL_QueryTexture(textTex, NULL, NULL, &(Textpos.w), &(Textpos.h));
  SDL_RenderCopy(renderer, textTex, NULL, &Textpos);
  SDL_DestroyTexture(textTex);
  SDL_QueryTexture(textTex2, NULL, NULL, &(Textpos2.w), &(Textpos2.h));
  SDL_RenderCopy(renderer, textTex2, NULL, &Textpos2);
  SDL_DestroyTexture(textTex2);
  SDL_QueryTexture(textTex3, NULL, NULL, &(Textpos3.w), &(Textpos3.h));
  SDL_RenderCopy(renderer, textTex3, NULL, &Textpos3);
  SDL_DestroyTexture(textTex3);

  }








  /////////////////////////HEARTS DISPLAY


  for(int i=0;i<numPlayers;i++)
  {
    for(int s=0;s<Players[i].maxlives;s++)
    {
      SDL_Rect heartPos = {40, 40};
      heartPos.x += s*90;
      heartPos.y += i*130;

      if(s<Players[i].lives)
      {
         SDL_QueryTexture(heartTex, NULL, NULL, &(heartPos.w), &(heartPos.h));
         SDL_RenderCopy(renderer, heartTex, NULL, &heartPos);
      }
      else
      {
         SDL_QueryTexture(heartTex2, NULL, NULL, &(heartPos.w), &(heartPos.h));
         SDL_RenderCopy(renderer, heartTex2, NULL, &heartPos);

      }
      
    }
  }

//////////////////SCORE

for(int i=0;i<numPlayers;i++)
  {
    char Score[50];
    sprintf(Score, "Score: %d", Players[0].score); 
    SDL_Surface *ScoreTxt = TTF_RenderText_Blended(police, Score, couleurNoire);
    SDL_Texture *ScoreTex;
    if (ScoreTxt == NULL)
    {
    printf("Failed To Create text\n");
    }
    else
    {
    ScoreTex = SDL_CreateTextureFromSurface(renderer, ScoreTxt);
    SDL_FreeSurface(ScoreTxt);
    SDL_Rect ScorePos = {40, 120};
    ScorePos.y += i*130;
    SDL_QueryTexture(ScoreTex, NULL, NULL, &(ScorePos.w), &(ScorePos.h));
    SDL_RenderCopy(renderer, ScoreTex, NULL, &ScorePos);
    }
  }
}