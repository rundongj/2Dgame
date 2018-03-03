#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
//#include "sprite.h"
#include "multisprite.h"
#include "explodingSprite.h"





class SmartSprite : public MultiSprite {
public:
  SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { } 

  virtual void update(Uint32 ticks);
  virtual void draw()const;
  SmartSprite& operator=(SmartSprite&)=delete;

  void setPlayerPos(const Vector2f& p) { playerPos = p; }

  void accl();

  void explode();

  bool exploded=0;

  int evasionmethod=0;

  

private:

  struct shadow
  {
      Image* shadowimage=nullptr;
      Uint32 starttime=0;
      Uint32 displaytime=150;
      Vector2f position=Vector2f(0.0,0.0);
  };
  int shadowamounts=10;
  bool shadowstate=0;



  enum MODE {NORMAL, EVADE};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;

  ExplodingSprite* explosion=NULL;



  void goLeft();
  void goRight();
  void goUp();
  void goDown();
  
  int jumptimes=10;
  void jumprandom();
  void acclshadow(bool start);

  int generateNumber=0;
  shadow shadows[10];

};
#endif
