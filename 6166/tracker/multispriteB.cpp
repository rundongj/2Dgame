#include "multispriteB.h"
#include "gamedata.h"
#include "renderContext.h"

void MultiSpriteB::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}


MultiSpriteB::MultiSpriteB( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  change(false),
  images( RenderContext::getInstance()->getImages(name) ),
  //imageschange( nullptr ),
  imagesopposite(),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

MultiSpriteB::MultiSpriteB( const std::string& name,const std::string& name2) ://bidirection: get two picture from two name, change is the flag
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  change(false),
  images( RenderContext::getInstance()->getImages(name) ),
  imagesopposite( RenderContext::getInstance()->getImages(name2) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

MultiSpriteB::MultiSpriteB( const std::string& name,const std::string& name2,int initlocx,int initlocy,int initframe) : 
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x")+initlocx, 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")+initlocy), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  change(false),
  images( RenderContext::getInstance()->getImages(name) ),
  imagesopposite( RenderContext::getInstance()->getImages(name2) ),

  currentFrame(initframe),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

MultiSpriteB::MultiSpriteB(const MultiSpriteB& s) :
  Drawable(s), 
  change(s.change),
  images(s.images),
  imagesopposite(s.imagesopposite),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

MultiSpriteB& MultiSpriteB::operator=(const MultiSpriteB& s) {
  Drawable::operator=(s);
  images = (s.images);
  imagesopposite =(s.imagesopposite);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  change=s.change;
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );

  return *this;

}

void MultiSpriteB::draw() const { 
  if(change==false)
  {
  images[currentFrame]->draw(getX(), getY(), getScale());
  }
  else
  {
  imagesopposite[currentFrame]->draw(getX(), getY(), getScale());
  }
}

void MultiSpriteB::draw(int alpha) const { 
  if(change==false)
  {
  images[currentFrame]->draw(getX(), getY(), alpha);
  }
  else
  {
  imagesopposite[currentFrame]->draw(getX(), getY(), alpha);
  }
}

void MultiSpriteB::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    if(change==false){change=true;}
    else{change=false;}
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
    if(change==false){change=true;}
    else{change=false;}
  }  

}


void MultiSpriteB::update(Uint32 ticks,int uperbound, int lowerbound) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < uperbound) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > lowerbound) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    if(change==false){change=true;}
    else{change=false;}
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
    if(change==false){change=true;}
    else{change=false;}
  }  

}