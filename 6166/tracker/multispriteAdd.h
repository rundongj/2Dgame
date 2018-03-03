#ifndef MULTISPRITEADD_H
#define MULTISPRITEADD_H


#include <string>
#include <vector>
#include <list>
#include <cmath>
#include "drawable.h"
#include "multispriteB.h"
//#include "shadow.h"

/*class MultiSpriteAdd 
{
  public:
   MultiSpriteAdd(const std::string& name,const std::string& name2,float distance1=1);//set distance between sprites
   virtual void draw() const;
   //virtual void draw(int alpha) const;
   virtual void update(Uint32 ticks);
   virtual ~MultiSpriteAdd();
   void reformat();
   float distance;
   MultiSpriteB* a;
   MultiSpriteB* b;
   MultiSpriteB* c;
};*/


class MultiSpriteAdd : public MultiSpriteB
{
  public:
      MultiSpriteAdd(const std::string& name,const std::string& name2):MultiSpriteB(name,name2) {
         //MultiSpriteB::MultiSpriteB(name,name2);
         for(int i=0; i<shadowamounts;i++)
         {
            shadows[i].shadowimage=nullptr;
            shadows[i].starttime=0;
            shadows[i].displaytime=150;
            shadows[i].position[0]=0;
            shadows[i].position[1]=0;
         }

      }
      virtual void update(Uint32 ticks);
      virtual void draw() const;
      

  private:
   struct shadow
   {
      Image* shadowimage=nullptr;
      Uint32 starttime=0;
      Uint32 displaytime=150;
      Vector2f position=Vector2f(0.0,0.0);

   };
   int shadowamounts=10;
   int generateNumber=0;
   shadow shadows[10];
   
};
#endif