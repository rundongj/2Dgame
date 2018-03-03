#ifndef MULTISPRITEB__H
#define MULTISPRITEB__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class MultiSpriteB : public Drawable {
public:
  MultiSpriteB(const std::string&);
  MultiSpriteB(const std::string&,const std::string&);
  MultiSpriteB( const std::string& name,const std::string& name2,int initlocx,int initlocy,int initframe);
  MultiSpriteB(const MultiSpriteB&);

  virtual void draw() const;
  virtual void draw(int alpha) const;
  virtual void update(Uint32 ticks);
  virtual void update(Uint32 ticks, int uperbound, int lowerboud);

  virtual const Image* getImage() const { 
    return images[currentFrame]; 
  }
  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }

  bool change=0;

protected:


  std::vector<Image *> images;
  std::vector<Image *> imagesopposite;
  
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  void advanceFrame(Uint32 ticks);
  MultiSpriteB& operator=(const MultiSpriteB&);
};
#endif
