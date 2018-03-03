#include "multispriteB.h"
#include "multispriteAdd.h"
#include "gamedata.h"
#include "renderContext.h"


/*MultiSpriteAdd::MultiSpriteAdd( const std::string& name,const std::string& name2, float distance1) :

  distance(distance1),
	a(new MultiSpriteB(name,name2)),
	b(new MultiSpriteB(name,name2,a->getVelocityX()*distance1,a->getVelocityY()*distance1,0)),// set x y and start frame 
	c(new MultiSpriteB(name,name2,a->getVelocityX()*distance1,a->getVelocityY()*distance1,0))

{}

MultiSpriteAdd::~MultiSpriteAdd()
{
  delete a;
  delete b;
  delete c;
}

void MultiSpriteAdd::reformat()//refresh the position
{
     //MultiSprite* a1=dynamic_cast<MultiSprite*>(a);
     //MultiSprite* b1=dynamic_cast<MultiSprite*>(b);
     //MultiSprite* c1=dynamic_cast<MultiSprite*>(c);
     if((a-> getVelocityX()>0) && (b-> getVelocityX()>0) && (c-> getVelocityX()>0) )
     //if(a-> getVelocityX() == b-> getVelocityX() == c-> getVelocityX() )
      {
      
      Vector2f aPos=a-> getPosition();
      aPos[0]+=a->getVelocityX()*distance;aPos[1]+=a->getVelocityY()*distance;
      b-> setPosition(aPos);
      aPos[0]+=a->getVelocityX()*distance;aPos[1]+=a->getVelocityY()*distance;
      c-> setPosition(aPos);
 
      //return(0);
      }
}*/

void MultiSpriteAdd::draw() const
{
   MultiSpriteB::draw();

   for(int i=0; i<shadowamounts;i++)
   {
          if(shadows[i].shadowimage!=nullptr)
          {
            //shadows[i].shadowimage->draw(0,0,shadows[i].position[0],shadows[i].position[1],50);
            shadows[i].shadowimage->draw(shadows[i].position[0], shadows[i].position[1],50);
            //std::cout<<"draw shadow"<<std::endl;
            //std::cout<<"shadow position "<<shadows[i].position <<std::endl;
            //std::cout<<"now position"<<getPosition()<< std::endl;
            //std::cout<<"position"<<shadows[i].position-getPosition()<< std::endl;
            //generateNumber
          }

   }



    /*std::list<Shadow*>::iterator shadow2= myshadows.begin();
    while(shadow2!=myshadows.end())
    {
      if(!(*shadow2)->deletestate())
      {
        //delete *shadow2;
        //myshadows.erase(shadow2);
        *shadow2->draw();
      }
      else 
        shadow2++;
    }*/



}
//void MultiSpriteAdd::draw(int alpha) const{}

void MultiSpriteAdd::update(Uint32 ticks)
{
    MultiSpriteB::update(ticks);
    //std::cout<<ticks<<"input time"<<std::endl;
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


