#include "player.h"

Player::Player( const std::string& name) :
  //dashlist(),
  MultiSpriteB(name),
  dashlist(),
  clip(),
  dashname( Gamedata::getInstance().getXmlStr(name+"/bullet")),
  collision(false),
  initialVelocity(getVelocity()),
  minSpeed( Gamedata::getInstance().getXmlInt(dashname+"/speedX") ),
  dashInterval(Gamedata::getInstance().getXmlInt(dashname+"/interval")),
  timeSinceLastFrame(0),
  observers()
{ for(int x=0; x<15; x++)
     {
         clip.push_back(Bullet(dashname, (dashname+"L")));
     }
}

Player::Player( const std::string& name,const std::string& name2) :
  //dashlist(),
  MultiSpriteB(name,name2),
  dashlist(),
  clip(),
  dashname( Gamedata::getInstance().getXmlStr(name+"/bullet")),
  collision(false),
  initialVelocity(getVelocity()),
  minSpeed( Gamedata::getInstance().getXmlInt(dashname+"/speedX") ),
  dashInterval(Gamedata::getInstance().getXmlInt(dashname+"/interval")),
  timeSinceLastFrame(0),
  observers()
{ for(int x=0; x<15; x++)
     {
         clip.push_back(Bullet(dashname,(dashname+"L")));
     }
}

Player::Player(const MultiSpriteB & MSpriteB):
  //dashlist(),
  MultiSpriteB(MSpriteB),
  dashlist(),
  clip(),
  dashname( Gamedata::getInstance().getXmlStr(MSpriteB.getName()+"/bullet")),
  collision(false),
  initialVelocity(MSpriteB.getVelocity()),
  //change(MSpriteB.change),
  minSpeed( Gamedata::getInstance().getXmlInt(dashname+"/speedX") ),
  dashInterval(Gamedata::getInstance().getXmlInt(dashname+"/interval")),
  timeSinceLastFrame(0),
  observers()

{ for(int x=0; x<15; x++)
     {
         clip.push_back(Bullet(dashname,(dashname+"L")));
     }
}

Player::Player(const Player& s) :
  MultiSpriteB(s), 
  dashlist(s.dashlist),
  clip(s.clip),
  dashname(s.dashname),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  minSpeed(s.minSpeed),
  dashInterval(s.dashInterval),
  timeSinceLastFrame(s.timeSinceLastFrame),
  observers(s.observers)
  //change(s.change)
  { }

Player& Player::operator=(const Player& s) {
  MultiSpriteB::operator=(s);
  dashname=s.dashname;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  observers=s.observers;
  dashlist=s.dashlist;
  clip=s.clip;
  //change(s.change)
  return *this;
}



void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
    change=false;
  }
} 
void Player::left()  { 
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
    change=true;
  }
} 
void Player::up()    { 
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::dash() { 
// in this function we need judge if we finished dash, when the butterfly is dashing we can't move it untile the dashing state finished. 
  //timeSinceLastFrame = 0;
  if(!clip.empty() && (timeSinceLastFrame>dashInterval))
  { 
    stop();
    dashing=1;// we are under the state of dashing.
    dashlist.splice(dashlist.begin(),clip,clip.begin());
    timeSinceLastFrame=0;
    dashlist.begin()->reset();
    if(alphastate>25)
      {alphastate-=25;}
    else
      {alphastate=0;}
    dashlist.front().setPosition(getPosition());
    dashlist.front().change=change;
    if(change==0)
      {
        //if(dashlist.size()<1)
          dashlist.front().setVelocity(getVelocity()+Vector2f(dashlist.front().minSpeed(),0));
        //set the velocity for the fist dash sprite. 
        //else //if there are sprite in the dshlist we will set the velocity the same as the first sprite.
         //dashlist.front().setVelocity(dashlist.back().getVelocity());
        //std::cout<<"sprite speed is:"<<dashlist.front().getVelocity();
        //throw 0;
      }
    else
      {  
        //if(dashlist.size()<1)
          dashlist.front().setVelocity(-(getVelocity()+Vector2f(dashlist.front().minSpeed(),0)));
       //std::cout<<"sprite speed is:"<<dashlist.front().getVelocity();
        //else //if there are sprite in the dshlist we will set the velocity the same as the first sprite.
         // dashlist.front().setVelocity(dashlist.back().getVelocity());
       //throw 0;
      }

  }
}

void Player::dashupdate(Uint32 ticks) { 
// in this function we need update the dash state 
  timeSinceLastFrame += ticks;
  if(dashing==1)
    {
      //std::cout<<"dashupdate"<<std::endl;
      dash();//if dash started every time update we will shoot a dash sprite automaticallly. we can also add dashinterval here.
      int countdashfinish=0;
      for(Bullet& dashsprites: dashlist )
      { 
        if(dashsprites.getTooFar()==false)
        {
          dashsprites.update(ticks);
          //std::cout<<"nottoofar"<<dashsprites.getX()<<std::endl;
        }
        else
          {
            countdashfinish++;
            //std::cout<<"toofar countdash++"<<std::endl;
          }
      }
      if(countdashfinish==15)// when evey sprites get to the position,finish dashing
        { this->setPosition(dashlist.back().getPosition());//set new position for player
          this->change= dashlist.back().change;
          clip.splice(clip.begin(),dashlist);

          dashing=0;//change the dashing state
          alphastate=255;
          //std::cout<<"clean dashlist"<<std::endl;
          //std::cout<<"sizeof dashlist" <<dashlist.size() <<std::endl;
          //std::cout<<"sizeof cliplist" <<clip.size() <<std::endl;
        }
    }

}

void Player::dashdraw() {
  for (Bullet& dashsprites: dashlist)
    { 
      //std::cout<<"dashdraw"<<std::endl;
      //std::cout<<"sizeof dashlist" <<dashlist.size() <<std::endl;
      //std::cout<<"sizeof cliplist" <<clip.size() <<std::endl;
      dashsprites.draw(50);
    }
}


void Player::update(Uint32 ticks) {
  if ( !collision ) 
  {
     advanceFrame(ticks);//refresh for the next frame
  }

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);


  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
  dashupdate(ticks);
  stop();
}



void Player::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

