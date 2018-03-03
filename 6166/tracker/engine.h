#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "multispriteB.h"
#include "multispriteAdd.h"
#include "sprite.h"
#include "player.h"
#include "MyHUD.h"

class Player;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
  void play();
  void reInitial();
  //void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;
  //int alpha;
  MyHUD myhud;
  SDL_Renderer * const renderer;
  World back0;
  World back1;
  World back2;
  World back3;
  World back0BW;
  World back1BW;
  World back2BW;
  World back3BW;
  
  int itemsN=5;
  int items1N=10;
  std::vector< Drawable* > items;
  std::vector< Drawable* > items1;

  World backfinish;

  Viewport& viewport;

  //MultiSpriteB * playersprite;
  Player* player;

  std::vector<SmartSprite*> sprites;
  std::vector<SmartSprite*> sprites1;
  std::vector<SmartSprite*> sprites2;
  std::vector<SmartSprite*> sprites3;

  int n;//the total number of sprite should be catched
  int gamelevel=0;
  int catchedsprites=0;
  int catchedsprites1=0;
  int catchedsprites2=0;
  int catchedsprites3=0;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  //std::vector< Drawable* > items;

  MultiSpriteB* butterfly0;
  MultiSprite* decSprite0;
  MultiSprite* decSprite1;
  MultiSprite* decSprite2;
  MultiSprite* decSprite3;
  MultiSprite* decSprite4;



  int currentSprite;
  bool makeVideo;

  void draw();
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
  bool catchsound=0;

};
