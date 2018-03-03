#ifndef WORLD_H
#define WORLD_H
#include <string>
#include "image.h"
#include "viewport.h"

class World {
public:
  World(const std::string& name, int fact);
  // ~World() { } // The image will be deleted by the FrameFactory
  void update();
  void draw() const;
  void draw(int alpha) const;
private:
  Image* const image;
  int factor;
  unsigned worldWidth;
  unsigned imageWidth;
  float viewX;
  float viewY;
  const Viewport & view;
  World(const World&);
  World& operator=(const World&);
};

#endif
