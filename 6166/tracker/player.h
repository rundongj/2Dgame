#ifndef PLAYER__H
#define PLAYER__H
#include <list>
#include "multispriteB.h"
#include "smartSprite.h"
#include "bullet.h"


class Player : public MultiSpriteB {
public:
  Player(const std::string&);
  Player( const std::string& name,const std::string& name2);
  Player(const MultiSpriteB & MSpritB );
  Player(const Player&);
  ~Player(){//delete[] shooting; delete[] bolletclip;
           }
  virtual void update(Uint32 ticks);

  //void update(Uint32 ticks);
  void attach( SmartSprite* o ) { observers.push_back(o); } 
  void detach( SmartSprite* o );

  bool getcollstate() {return collision;}

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();
  void stop();
  void dash();

  void dashupdate(Uint32 ticks);
  void dashdraw();
  int  getalphastate(){return alphastate;}
  bool dashingstate(){return dashing;}
  
  std::list<Bullet> dashlist;
  //dashlist.reserve(10);
  std::list<Bullet> clip;
  //clip.reserve(10); 

private:

  int alphastate=255;

  bool dashing=0;
  std::string dashname;
  bool collision;
  Vector2f initialVelocity;
  float minSpeed;
  float dashInterval;

  float timeSinceLastFrame;


  std::list<SmartSprite*> observers;

};
#endif
