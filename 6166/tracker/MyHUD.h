#include <sstream>
#include <string>
#include "ioMod.h"
#include "gamedata.h"
#include "world.h"
#include "viewport.h"
#include "renderContext.h"

class MyHUD
{
	public:
		MyHUD();
		MyHUD(MyHUD&)=delete;
		MyHUD& operator=(MyHUD&)=delete;
		void display(int go);
		void display2( int dash, int clip,int alpha=255);
		~MyHUD();	
    private:
    	Image* const image;
    	Image* const imagebg;
    	Image* const imagelg;
    	unsigned imageWidth;
		float viewX;
		float viewY;
    	const Viewport & view;
    	World HUDback;
    	std::string message;

};