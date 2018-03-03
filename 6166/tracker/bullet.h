#include <iostream>
#include "sprite.h"
#include "gamedata.h"
#include "multispriteB.h"

class Bullet : public MultiSpriteB {
public:
  explicit Bullet(const string& name1,const string& name2) :
    MultiSpriteB(name1,name2), 
    distance(0), 
    maxDistance(Gamedata::getInstance().getXmlInt(name1+"/distance")), 
    tooFar(false) 
  { }
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }
  float minSpeed(){return minSpeeds;}
  bool getTooFar(){return tooFar;}
  /*virtual void draw(int alpha){
  std::cout<<"bulletdraw"<<std::endl;
  MultiSpriteB::draw(alpha);

  }*/

private:
  float distance;
  float maxDistance;
  bool tooFar;
  float minSpeeds=500;
};
