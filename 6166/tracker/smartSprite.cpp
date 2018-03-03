#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"


float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void SmartSprite::goLeft()  { setVelocityX( -std::abs(getVelocityX()) );  }
void SmartSprite::goRight() { setVelocityX( fabs(getVelocityX()) );  }
void SmartSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( fabs(getVelocityY()) );  }


void SmartSprite::jumprandom()
{
   float px=(rand()%300)*(rand()%2?1:-1),py=(rand()%300)*(rand()%2?1:-1);
   setPosition(Vector2f(getX()+px,getY()+py));
}
void SmartSprite::acclshadow(bool start)
{
   int dx=getVelocityX()>0?1:-1,dy=getVelocityY()>0?1:-1;
   if(start)
   {
     shadowstate=1;//start shadow and acclerate
     setVelocityX(dx*(std::abs(getVelocityX())+70));
     setVelocityY(dy*(std::abs(getVelocityY())+70));
   }
   else
   {
     shadowstate=0;//close shadow and recover the speed
     setVelocityX(dx*(Gamedata::getInstance().getXmlInt(getName()+"/speedX")));
     setVelocityY(dy*(Gamedata::getInstance().getXmlInt(getName()+"/speedY")));
   }
}



SmartSprite::SmartSprite(const std::string& name, const Vector2f& pos, 
  int w, int h) :
  MultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance")),
  explosion(NULL)
{}


SmartSprite::SmartSprite(const SmartSprite& s) : 
  MultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance),
  explosion(NULL)
{}

void SmartSprite::accl(){acclshadow(true);}



void SmartSprite::explode() {
  if ( !explosion && !exploded ) {
    Sprite sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
    //std::cout<<"explosion new:" <<std::endl;
    //throw(0);
  }
}

void SmartSprite::draw() const { 
  if ( explosion && !exploded) {
    explosion->draw();
    //std::cout<<"explosion draw"<< std::endl;
  }
  else 
  {if(!exploded)
    this->MultiSprite::draw(255);
    //std::cout<<"draw"<< std::endl;
   if(shadowstate && (explosion==nullptr) )
    {
       for(int i=0; i<shadowamounts;i++)
       {
              if(shadows[i].shadowimage!=nullptr)
              {

                shadows[i].shadowimage->draw(shadows[i].position[0], shadows[i].position[1],50);

              }

       }
    }
  }
  
}

void SmartSprite::update(Uint32 ticks) { 
  //std::cout<< "updateing:"<<explosion<<std::endl;
  if ( explosion && !exploded ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      exploded = 1;
      explosion=nullptr;
      //std::cout<<"exploded update:" <<std::endl;
      //throw(0);
    }
  }
  else
  {
    MultiSprite::update(ticks);
    float x= getX()+getImage()->getWidth()/2;
    float y= getY()+getImage()->getHeight()/2;
    float ex= playerPos[0]+playerWidth/2;
    float ey= playerPos[1]+playerHeight/2;
    float distanceToEnemy = ::distance( x, y, ex, ey );

    if  ( currentMode == NORMAL ) {
      if(distanceToEnemy < safeDistance) currentMode = EVADE;
    }
    else if  ( currentMode == EVADE ) {
      if(distanceToEnemy > safeDistance) 
        {
          currentMode=NORMAL;
          if(evasionmethod==2)
          {acclshadow(0);}

        }
      else {
        if(evasionmethod==0)
        {
          if ( x < ex ) goLeft();
          if ( x > ex ) goRight();
          if ( y < ey ) goUp();
          if ( y > ey ) goDown();
        }
        if(evasionmethod==1)
        {
          jumprandom();
          if ( x < ex ) goLeft();
          if ( x > ex ) goRight();
          if ( y < ey ) goUp();
          if ( y > ey ) goDown();
        }

        if(evasionmethod==2)
        {
          if ( x < ex ) goLeft();
          if ( x > ex ) goRight();
          if ( y < ey ) goUp();
          if ( y > ey ) goDown();
          acclshadow(1);
        }
      }
    }
  }
  

  if(shadowstate)
  {
    generateNumber=generateNumber%shadowamounts;
    for(int i=0; i<shadowamounts;i++)
         {
          //int i=generateNumber;
            if(shadows[i].starttime==0 && i==generateNumber)
              {
                shadows[i].shadowimage=const_cast<Image*>(getImage());
                shadows[i].position=getPosition();
                shadows[i].starttime+=ticks;

              }
            else
            {
              //std::cout<<ticks<<"  "<<shadows[i].starttime<<"time"<<ticks-shadows[i].starttime<<std::endl;
              if(ticks+shadows[i].starttime>shadows[i].displaytime )
                {
                  shadows[i].starttime=0;
                  shadows[i].shadowimage=nullptr;
                  shadows[i].position[0]=0;
                  shadows[i].position[1]=0;
                  //std::cout<<"position"<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<< std::endl;
                }
              else
                if(shadows[i].starttime!=0)
                shadows[i].starttime+=ticks;
            }
            
         }
      generateNumber++;
    }

}
