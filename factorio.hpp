#include <SFML/Graphics.hpp>

#define ZOOM_FACTOR -.05
#define PERLIN_FACTOR 0.1


# include <cassert>
# include <iostream>
# include <fstream>
# include <sstream>
#include <stdio.h>
#include <vector>
#include <list>
#include <unordered_map>
#include "PerlinNoise.hpp"

using namespace sf;
using namespace std;
View Perspective;
int width;
int height;
float zoom = 1.f;



#include "assets.hpp"
#include "world.hpp"
