// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"

//ImageFactory*  ImageFactory::instance = NULL;
RenderContext* RenderContext::instance = NULL;

int main(int, char*[]) {
   try {
      Engine engine;
      engine.play();
      delete RenderContext::getInstance();
      
      //std::cout << "1111111111111111111111111111111111111" << std::endl;
      //throw("xxxxxxxxxxxxxxx");
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
