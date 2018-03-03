#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "collisionStrategy.h"
#include "sound.h"


Engine::~Engine() {

  for ( SmartSprite* sprite : sprites ) {
    delete sprite;
  }

    for ( SmartSprite* sprite : sprites1 ) {
    delete sprite;
  }

    for ( SmartSprite* sprite : sprites2 ) {
    delete sprite;
  }

    for ( SmartSprite* sprite : sprites3 ) {
    delete sprite;
  }
  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  for (auto item :items)
  {
    delete item;
  }
  for (auto item1 :items1)
  {
    delete item1;
  }
  //delete items[0];
  //delete items[1];
  //delete items[2];
  //delete playersprite;
  delete player;
  delete butterfly0;
  delete decSprite0;
  delete decSprite1;
  delete decSprite2;
  delete decSprite3;
  delete decSprite4;


  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  myhud(),
  renderer( rc->getRenderer() ),
  back0("backsky", Gamedata::getInstance().getXmlInt("backsky/factor") ),
  back1("backsnowmountain", Gamedata::getInstance().getXmlInt("backsnowmountain/factor") ),
  back2("backriver", Gamedata::getInstance().getXmlInt("backriver/factor") ),
  back3("backgrass", Gamedata::getInstance().getXmlInt("backgrass/factor") ),
  back0BW("backskyBW", Gamedata::getInstance().getXmlInt("backskyBW/factor") ),
  back1BW("backsnowmountainBW", Gamedata::getInstance().getXmlInt("backsnowmountainBW/factor") ),
  back2BW("backriverBW", Gamedata::getInstance().getXmlInt("backriverBW/factor") ),
  back3BW("backgrassBW", Gamedata::getInstance().getXmlInt("backgrassBW/factor") ),
  items(),
  items1(),
  backfinish("backfinish", Gamedata::getInstance().getXmlInt("backfinish/factor") ),
  viewport( Viewport::getInstance() ),

  player(new Player("ButterflyR","ButterflyL")),
  sprites(),
  sprites1(),
  sprites2(),
  sprites3(),
  n(Gamedata::getInstance().getXmlInt("numberOfStars")),
  strategies(),
  currentStrategy(0),
  collision(false),

  butterfly0(new MultiSpriteB("ButterflyR0","ButterflyL")),
  decSprite0(new MultiSprite("SpinningStargreen")),
  decSprite1(new MultiSprite("SpinningStarblue")),
  decSprite2(new MultiSprite("SpinningStaryellow")),
  decSprite3(new MultiSprite("SpinningStarpurple")),
  decSprite4(new MultiSprite("SpinningStarrainbow")),


  currentSprite(3),
  makeVideo( false )
{
  for(int i = 0; i < itemsN; ++i) {
    //items.push_back(new MultiSpriteB("wildgooseR","wildgooseL"));
    items.push_back(new MultiSprite("SpinningStarrainbow"));
    items.back()->setScale(0.2);
    items.back()->setPosition(Vector2f(30+i*8,50-i*8));
    items.back()->setVelocity(items.back()->getVelocity()/2);
  }
  for(int i = 0; i < items1N; ++i) {
    items1.push_back(new MultiSprite("SpinningStarrainbow"));
    items1.back()->setScale(0.4);
    //items1.back()->setVelocity(Vector2f(30,40));
  }
  //items.push_back(new MultiSpriteB("ButterflyRtwinkle","ButterflyL"));

  
  
  sprites.reserve(n);
  sprites1.reserve(n);
  sprites2.reserve(n);
  sprites3.reserve(n);

  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();



  for (int i = 0; i < n; ++i) {
    sprites.push_back( new SmartSprite("SpinningStargreen", pos, w, h) );
    //sprites.back()->evasionmethod=2;//sprites2 can acclerate 
    player->attach( sprites[i] );
  }

  for (int i = 0; i < n; ++i) {
    sprites1.push_back( new SmartSprite("SpinningStarblue", pos, w, h) );
    sprites1.back()->evasionmethod=2;//sprites1 can jump
    player->attach( sprites1[i] );
  }

  for (int i = 0; i < n; ++i) {
    sprites2.push_back( new SmartSprite("SpinningStaryellow", pos, w, h) );
    sprites2.back()->evasionmethod=1;//sprites2 can acclerate 
    player->attach( sprites2[i] );
  }

  for (int i = 0; i < n; ++i) {
    sprites3.push_back( new SmartSprite("SpinningStarpurple", pos, w, h) );
    sprites3.back()->evasionmethod=1;
    sprites3.back()->accl();//sprites3 will always acclerate and they can jump
    player->attach( sprites3[i] );
  }


  //playersprite=new MultiSpriteB("ButterflyR","ButterflyL");
  //player=new Player(*playersprite);

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );



  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}


void Engine::reInitial()
{
  n=5;
  gamelevel=0;
  catchedsprites=0;
  catchedsprites1=0;
  catchedsprites2=0;
  catchedsprites3=0;

  player->setPosition(Vector2f(0,300));
  
  std::vector<SmartSprite*>().swap(sprites);
  std::vector<SmartSprite*>().swap(sprites1);
  std::vector<SmartSprite*>().swap(sprites2);
  std::vector<SmartSprite*>().swap(sprites3)
  ;
  sprites.reserve(n);
  sprites1.reserve(n);
  sprites2.reserve(n);
  sprites3.reserve(n);

  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();



  for (int i = 0; i < n; ++i) {
    sprites.push_back( new SmartSprite("SpinningStargreen", pos, w, h) );
    //sprites.back()->evasionmethod=2;//sprites2 can acclerate 
    player->attach( sprites[i] );
  }

  for (int i = 0; i < n; ++i) {
    sprites1.push_back( new SmartSprite("SpinningStarblue", pos, w, h) );
    sprites1.back()->evasionmethod=2;//sprites1 can jump
    player->attach( sprites1[i] );
  }

  for (int i = 0; i < n; ++i) {
    sprites2.push_back( new SmartSprite("SpinningStaryellow", pos, w, h) );
    sprites2.back()->evasionmethod=1;//sprites2 can acclerate 
    player->attach( sprites2[i] );
  }

  for (int i = 0; i < n; ++i) {
    sprites3.push_back( new SmartSprite("SpinningStarpurple", pos, w, h) );
    sprites3.back()->evasionmethod=1;
    sprites3.back()->accl();//sprites3 will always acclerate and they can jump
    player->attach( sprites3[i] );
  }


  //playersprite=new MultiSpriteB("ButterflyR","ButterflyL");
  //player=new Player(*playersprite);

  // strategies.push_back( new RectangularCollisionStrategy );
  // strategies.push_back( new PerPixelCollisionStrategy );
  // strategies.push_back( new MidPointCollisionStrategy );



  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}



void Engine::draw() {
  
  /*back0.draw();
  back1.draw();
  back2.draw();
  back3.draw();*/
  bool gamefinished=0;

  if(catchedsprites3==n)
    back0.draw(255);
  else
    back0BW.draw(255);

  for(auto item :items) {
   item->draw();
  }

  if(catchedsprites2==n)
    back1.draw(255);
  else
    back1BW.draw(255);

  for(auto item1 :items1) {
   item1->draw();
  }

  if(catchedsprites1==n)
    back2.draw(255);
  else
    back2BW.draw(255);

  if(catchedsprites==n)
    back3.draw(255);
  else
    back3BW.draw(50);

  //items[0]->draw();
  //items[1]->draw();
  //items[2]->draw(alpha);
  //
  //butterfly0->reformat();


 switch(gamelevel)
 {
   case 0:   
      for ( const Drawable* sprite : sprites ) {
        sprite->draw();
      }; 
      io.writeText("LEVEL1 NORMAL",550,400,{255,0,255,200});
      io.writeText("HINT:Just catch them!",520,420,{255,0,255,200});
      break;
   case 1:
      for ( const Drawable* sprite : sprites1 ) {
       sprite->draw();
      }; 
      io.writeText("LEVEL2 ACCLERATE",550,400,{255,0,255,200});
      io.writeText("HINT:They will provoke you. Just hit SPACE!",380,420,{255,0,255,200});
      break;
   case 2:
      for ( const Drawable* sprite : sprites2 ) {
        sprite->draw();
      };

      io.writeText("LEVEL3 JUMP",550,400,{255,0,255,200});
      io.writeText("HINT:They can just jump 10 times. Be patient!",350,420,{255,0,255,200});

      break;
   case 3:
      for ( const Drawable* sprite : sprites3 ) {
        sprite->draw();
      };

      io.writeText("LEVEL4 JUMP&ACCEL",550,400,{255,0,255,200});
      io.writeText("HINT:Last batch. Good Luck!",515,420,{255,0,255,200});

      break;
   default: gamefinished=1;break;
 }
  std::stringstream strm;
  strm <<" EG:"<< sprites.size() ;
  strm <<" EB:"<< sprites1.size(); 
  strm <<" EY:"<< sprites2.size(); 
  strm <<" EP:"<< sprites3.size()<< " Smart elfin Remaining    Press R to restart"; 
  io.writeText(strm.str(), 20, 25, {255, 255, 0, 255});
  //strategies[currentStrategy]->draw();

  player->draw(player->getalphastate());
  if(player->dashingstate())
    {
     player->dashdraw();
    }

  int fps=clock.getFps();
  std::stringstream temp;
  temp<<fps;
  std::string temp1=temp.str();

  viewport.draw("fps: "+temp1,30,50);
  io.writeText("Rundong Jiang ",30,400,{0,0,255,200});
  //strategies[currentStrategy]->draw();
  //if ( collision ) {
  //  IOmod::getInstance().writeText("Oops: Collision", 500, 90);
  //}
  
  if(gamefinished)
  {
     backfinish.draw();
     io.writeText("CONGRATULATIONS!",300,150,{0,0,255,200});
     io.writeText("Thank you bring colors back to the world!",200,200,{0,0,255,200});
     io.writeText("Press R to replay this game",250,280,{0,0,255,200});

  }


  //viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision = false;
  for ( const Drawable* d : sprites ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }
  if ( collision ) {
    player->collided();
  }
  else {
    player->missed();
    collision = false;
  }//used to check the collision for butterfly0

  if(gamelevel==0)
  {
      auto it = sprites.begin();
      while ( it != sprites.end() ) {
        SmartSprite* doa = *it;
        if ( strategies[currentStrategy]->execute(*player, **it) ) {
          doa->explode();catchsound=1;
        }
        if (player->dashingstate())
        {
          //auto dashCollision=(*player).dashlist.begin();
          for(auto dashCollision :(*player).dashlist)
          {
            //std::cout<<"checking dashing collosion"<<std::endl;
            if( strategies[currentStrategy]->execute(dashCollision, **it) )
              {doa->explode();catchsound=1; break;}
          }
        }

        if(doa->exploded)
          {
            player->detach(doa);
            delete doa;
            it = sprites.erase(it);
            catchedsprites++;
            if(catchedsprites==n)
            {
              gamelevel+=1;
            }
          }
         else ++it;
      }// check the collision for the smart sprite. and the evasion depends on speed.
  }  


  if(gamelevel==1)
  {
      auto it1 = sprites1.begin();
      while ( it1 != sprites1.end() ) {
        SmartSprite* doa = *it1;
        if ( strategies[currentStrategy]->execute(*player, **it1) ) {
          doa->explode();catchsound=1;
          //std::cout<<"catch blue and explode()"<<std::endl;
          //std::cout<<"exploding:"<< doa->exploded <<std::endl;
          //throw(0);
        }
        if (player->dashingstate())
        {
          auto dashCollision=(*player).dashlist.begin();
          while(dashCollision!=(*player).dashlist.end())
          {
            //std::cout<<"checking dashing collosion"<<std::endl;
            if( strategies[currentStrategy]->execute(*dashCollision, **it1) )
              {doa->explode();catchsound=1; break;}
            dashCollision++;
          }
        }
        if(doa->exploded)
          {
          //std::cout<<"exploded and delete blue:"<<std::endl;
          //throw(0);
            player->detach(doa);
            delete doa;
            it1 = sprites1.erase(it1);
            catchedsprites1++;
            if(catchedsprites1==n)
            {
              gamelevel+=1;
            }

          }
        else ++it1;
      }// check the collision for the smart sprite. and the evasion depends on speed.
  }


  if(gamelevel==2)
  {
      auto it2 = sprites2.begin();
      while ( it2 != sprites2.end() ) {
        SmartSprite* doa = *it2;
        if ( strategies[currentStrategy]->execute(*player, **it2) ) {
          doa->explode();catchsound=1;
        }
        if (player->dashingstate())
        {
          auto dashCollision=(*player).dashlist.begin();
          while(dashCollision!=(*player).dashlist.end())
          {
            //std::cout<<"checking dashing collosion"<<std::endl;
            if( strategies[currentStrategy]->execute(*dashCollision, **it2) )
              {doa->explode();catchsound=1; break;}
            dashCollision++;
          }
        }
        if(doa->exploded)
          {
            player->detach(doa);
            delete doa;
            it2 = sprites2.erase(it2);
            catchedsprites2++;
            if(catchedsprites2==n)
            {
              gamelevel+=1;
            }
          }
        else ++it2;
      }// check the collision for the smart sprite. and the evasion depends on speed.
  }


  if(gamelevel==3)
  {
      auto it3 = sprites3.begin();
      while ( it3 != sprites3.end() ) {
        SmartSprite* doa = *it3;
        if ( strategies[currentStrategy]->execute(*player, **it3) ) { 
          doa->explode();catchsound=1;
        }
        if (player->dashingstate())
        {
          auto dashCollision=(*player).dashlist.begin();
          while(dashCollision!=(*player).dashlist.end())
          {
            //std::cout<<"checking dashing collosion"<<std::endl;
            if( strategies[currentStrategy]->execute(*dashCollision, **it3) )
              {doa->explode(); catchsound=1;break;}
            dashCollision++;
          }
        }
        if(doa->exploded)
          {
            player->detach(doa);
            delete doa;
            it3 = sprites3.erase(it3);
            catchedsprites3++;
            if(catchedsprites3==n)
            {
              gamelevel+=1;
            }
          }
        else ++it3;
      }// check the collision for the smart sprite. and the evasion depends on speed.
  }

}


void Engine::update(Uint32 ticks) {

  checkForCollisions();
  player->update(ticks);

  switch(gamelevel)
  {
    case 0:
        for ( Drawable* sprite : sprites ) {
          sprite->update( ticks );
        };break;
    case 1:
          for ( Drawable* sprite : sprites1 ) {
          //sprite->update( ticks, 500, 700 );// set the upper and lower bound for the sprites
            sprite->update( ticks);
        }; break;
    case 2:
          for ( Drawable* sprite : sprites2 ) {
          sprite->update( ticks );
        };break;
    case 3:
          for ( Drawable* sprite : sprites3 ) {
          sprite->update( ticks );
        };break;

  }

  //items[0]->update(ticks,500,700);
  //items[1]->update(ticks,100,200);
  //items[2]->update(ticks);
  //std::cout<<"ENGINETIME"<<ticks<<std::endl;

  //butterfly0->update(ticks); 


  /*back0.update();  
  back1.update();
  back2.update();
  back3.update();*/
 
  if(catchedsprites3==n)
    back0.update();
    else
    back0BW.update();
  for(auto item :items)
  {
    item->update(ticks,150,250);
    //item->setVelocity(back1.getVelocity()+item->getVelocity());
    //int viewX = static_cast<int>(view.getX() / 1) % ;
    //int viewY = view.getY();
  }
  if(catchedsprites2==n)
    back1.update();
    else
    back1BW.update();
  for(auto item1 :items1)
  {
    item1->update(ticks,300,400);
  }
  if(catchedsprites1==n)
    back2.update();
    else
    back2BW.update();
  if(catchedsprites==n)
    back3.update();
    else
    back3BW.update();

  viewport.update(); // always update viewport last
 
}

/*void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 4;
  if ( currentSprite==1 ) {
    Viewport::getInstance().setObjectToTrack(items[1]);//wildgoose
  }
  
  else {
        if (currentSprite==2)
        Viewport::getInstance().setObjectToTrack(items[2]);//butterflytwinkle
        else
        {
            if(currentSprite==3)  
            Viewport::getInstance().setObjectToTrack(butterfly0->a);
            else
            Viewport::getInstance().setObjectToTrack(items[0]);//ship

        }
  }
}*/

void Engine::play() {



  SDLSound sound;
  int tempsoundtimer=0;

  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;
  int intr=0;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }

        if (keystate[SDL_SCANCODE_R] ) {
          reInitial();
          intr=0;
        }

        if ( keystate[SDL_SCANCODE_M] ) {
          sound.toggleMusic();
        }

        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          //switchSprite();
          myhud.display2((*player).dashlist.size(),(*player).clip.size(),80);
          SDL_RenderPresent(renderer);
          SDL_Delay(1000);
         
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          //switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:


    ticks = clock.getElapsedTicks();
    //std::cout<<"aaaaaaaaaaaaaaaaaaaaaaaaENGINETIMEgets"<<ticks<<std::endl;
    if ( ticks > 0 ) {
      clock.incrFrame();
      if(intr==0)
      {
        if (keystate[SDL_SCANCODE_G] ) {
          myhud.display(1);
          SDL_RenderPresent(renderer);
          SDL_Delay(500);
          intr=1;
        }
        else
        {
          myhud.display(0);
          butterfly0->setPosition(Vector2f(10,300));
          butterfly0->draw();
          butterfly0->update(ticks);

          decSprite0->setPosition(Vector2f(570,100));
          decSprite0->draw();
          decSprite0->update(ticks);

          decSprite1->setPosition(Vector2f(600,350));
          decSprite1->draw();
          decSprite1->update(ticks);

          decSprite2->setPosition(Vector2f(670,270));
          decSprite2->draw();
          decSprite2->update(ticks);

          decSprite3->setPosition(Vector2f(560,400));
          decSprite3->draw();
          decSprite3->update(ticks);

          decSprite4->setPosition(Vector2f(690,50));
          decSprite4->draw();
          decSprite4->update(ticks);


          SDL_RenderPresent(renderer);
        }         
      }
      else
      {

      if (keystate[SDL_SCANCODE_A] ) {
        if(!(player->dashingstate()))
         player->left();
      }
      if (keystate[SDL_SCANCODE_D] ) {
        if(!(player->dashingstate()))
        player->right();
      }
      if (keystate[SDL_SCANCODE_W] ) {
        if(!(player->dashingstate()))
        player->up();
      }
      if (keystate[SDL_SCANCODE_S] ) {
        if(!(player->dashingstate()))
        player->down();
      }
      if (keystate[SDL_SCANCODE_SPACE] ) {
        player->dash();
        sound[1];

      }



      tempsoundtimer+=ticks;
       if(catchsound && tempsoundtimer>150)
      {sound[0];
        catchsound=0;
        tempsoundtimer=0;
      }


      update(ticks);
      
      draw();
      }


      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
