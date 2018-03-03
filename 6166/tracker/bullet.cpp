#include <iostream>
#include <cmath>
#include "bullet.h"

void Bullet::update(Uint32 ticks) { 
  Vector2f pos = getPosition();
  MultiSpriteB::update(ticks);
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  //std::cout<< "distance: "<<distance<<std::endl;
  //std::cout<< "speed: "<<this->getVelocityX()<<std::endl;
  if (distance > maxDistance) tooFar = true;
}

