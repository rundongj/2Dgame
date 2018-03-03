#include "ioMod.h"
#include "vector2f.h"
#include "renderContext.h"

ImageFactory& ImageFactory::getInstance() {
  //if ( !instance ) instance = new ImageFactory;
  static ImageFactory instance;
  return instance;
}

ImageFactory::~ImageFactory() {
  std::cout << "Deleting images in Factory" << std::endl;
  // Free single image containers
  std::map<std::string, SDL_Surface*>::iterator ptr = surfaces.begin();
  while ( ptr != surfaces.end() ) {
    SDL_FreeSurface(ptr->second);
    ++ptr;
  }
  //for(auto& ti : textures) SDL_DestroyTexture(ti.second);
  std::map<std::string, SDL_Texture*>::iterator ptrti=textures.begin();
  while(ptrti != textures.end())
  {
     SDL_DestroyTexture(ptrti->second);
     ptrti++;
  }

  
  /*for(auto& fi : images  ) {
    std::cout << "deleting " << fi.first << std::endl;
    delete fi.second;
  }*/
  

  std::map<std::string, Image*>::iterator ptrfi =images.begin();
  while(ptrfi != images.end())
  {
      std::cout << "deleting " << ptrfi->first << std::endl;
      delete ptrfi->second;
      ptrfi++;
  }


  // Free multi-image containers
  /*for ( auto surfaces : multiSurfaces ) {
    for (unsigned int i = 0; i < surfaces.second.size(); ++i) {
      SDL_FreeSurface( surfaces.second[i] );
    }
  }*/
  std::map<std::string, std::vector<SDL_Surface*> >::iterator surfacesptr= multiSurfaces.begin();
  while(surfacesptr!=multiSurfaces.end())
  {
      for (unsigned int i = 0; i < surfacesptr->second.size(); ++i) {
      SDL_FreeSurface( surfacesptr->second[i] );
      }
      surfacesptr++;
  }  

  for ( auto textures : multiTextures ) {
    for (unsigned int i = 0; i < textures.second.size(); ++i) {
      SDL_DestroyTexture( textures.second[i] );
    }
  }

  for ( auto images : multiImages ) {
    std::cout << "deleting " << images.first << std::endl;
    for (unsigned int i = 0; i < images.second.size(); ++i) {
      delete images.second[i];
    }
  }
}

Image* ImageFactory::getImage(const std::string& name) {
    std::map<std::string, Image*>::const_iterator it = images.find(name);
  if ( it == images.end() ) {
    SDL_Surface * const surface =
      IOmod::getInstance().readSurface( gdata.getXmlStr(name+"/file"));
    bool transparency = gdata.getXmlBool(name+"/transparency");
    if ( transparency ) {
      int keyColor = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
      SDL_SetColorKey(surface, SDL_TRUE, keyColor);
    }
    surfaces[name] = surface;
    RenderContext* renderContext  = RenderContext::getInstance();
    SDL_Texture * const texture =
      SDL_CreateTextureFromSurface(renderContext->getRenderer(), surface);
    Image * const image =new Image(surface, texture);
    images[name] = image;
    return image;
  }
  else {
    return it->second;
  }
}


std::vector<Image*> ImageFactory::getImages(const std::string& name) {
  // First search map to see if we've already made it:
  std::map<std::string, std::vector<Image*> >::const_iterator
    pos = multiImages.find(name);
  if ( pos != multiImages.end() ) {
    return pos->second;
  }

  IOmod& iomod = IOmod::getInstance();
  RenderContext* renderContext  = RenderContext::getInstance();
  std::string sheetPath = gdata.getXmlStr(name+"/file");
  SDL_Surface* spriteSurface = iomod.readSurface(sheetPath);
  bool transparency = gdata.getXmlBool(name+"/transparency");

  // It wasn't in the map, so we have to make the vector of Images:
  unsigned numberOfFrames = gdata.getXmlInt(name+"/frames");
  std::vector<Image*> images;
  std::vector<SDL_Surface*> surfaces;
  std::vector<SDL_Texture*> textures;
  images.reserve(numberOfFrames);
  surfaces.reserve(numberOfFrames);
  textures.reserve(numberOfFrames);

  int width = spriteSurface->w/numberOfFrames;
  int height = spriteSurface->h;

  if(  gdata.checkTag(name+"/imageWidth")
    && gdata.checkTag(name+"/imageHeight") ){
    width  = gdata.getXmlInt(name+"/imageWidth");
    height = gdata.getXmlInt(name+"/imageHeight");
  }

  SpriteSheet sheet(spriteSurface,width,height);

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    SDL_Surface* surface = sheet[i];
    if ( transparency ) {
      int keyColor = SDL_MapRGBA(spriteSurface->format, 255, 255, 255, 255);
      SDL_SetColorKey(surface, SDL_TRUE, keyColor);
    }
    SDL_Texture* texture =
      SDL_CreateTextureFromSurface(renderContext->getRenderer(),surface);
    surfaces.push_back( surface );
    textures.push_back( texture );
    images.push_back( new Image(surface, texture) );
  }
  multiSurfaces[name] = surfaces;
  multiTextures[name] = textures;
  multiImages[name] = images;
  return images;
}

