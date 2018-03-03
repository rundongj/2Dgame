#include "MyHUD.h"
#include <sstream>
MyHUD::MyHUD():
        //(std::string)Gamedata::getInstance().getXmlStr("MyHUD/file")
		image( RenderContext::getInstance()->getImage("MyHUD") ),
    imagebg( RenderContext::getInstance()->getImage("HUDbackbg") ),
    imagelg( RenderContext::getInstance()->getImage("HUDbacklg") ),
		imageWidth( image->getWidth() ),
	  viewX(650.0), viewY(0.0), 
	  view(Viewport::getInstance()),
		HUDback("HUDback", Gamedata::getInstance().getXmlInt("HUDback/factor") ),
    message((std::string)Gamedata::getInstance().getXmlStr("MyHUD/message"))
		{
  
    }
 
void MyHUD::display(int go)
		{
      if (go==0)
      {
			HUDback.draw();
      imagebg->draw(0,0,20,250);
      }
      else
      {
      HUDback.draw();
      imagelg->draw(0,0,20,250);
      }


			int position=0,x=30, y=200;

			while(position<=(int)message.length())
			{
        std::string temp=message.substr(position,80);
               // std::cout<< temp<<"::aaaaaaaaaaaaaaaaa"<<std::endl;
				IOmod::getInstance().writeText(temp, x, y, {247, 0, 9, 255});
				position=position+80;
				y=y+50;
			}

		}

void MyHUD::display2(int dash, int clip,int alpha)
  {
  	image->draw(0,0,viewX,viewY,alpha);
  	std::stringstream s;
  	s<<dash;
  	std::string a=s.str();
  	s.str("");
  	s<<clip;
  	std::string b=s.str();
    //image->draw(0,0,viewX,viewY,alpha);

    IOmod::getInstance().writeText("***HUD***", 700, 0, {0, 0, 0, 255});
    IOmod::getInstance().writeText("Move: w,a,s,d", 680, 45, {0, 0, 0, 255});
    IOmod::getInstance().writeText("Dash: Space", 680, 90, {0, 0, 0, 255});
    IOmod::getInstance().writeText("Aim:Catch all", 680, 135, {0, 0, 0, 255});
    IOmod::getInstance().writeText("DashList:"+a, 680, 180, {0, 0, 0, 255});
    IOmod::getInstance().writeText("DashPool:"+b, 680, 225, {0, 0, 0, 255});
  }


MyHUD::~MyHUD()
	{
        //the image will be destroyed by the image factory.
	}