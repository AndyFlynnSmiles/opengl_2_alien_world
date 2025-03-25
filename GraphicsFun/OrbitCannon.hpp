#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include "Vector3.hpp"
#include "Macros.hpp"
#include "Colors.hpp"
#include "Particles.hpp"
#include "Modeling.hpp"

void updateBalls();

void drawBalls(GLUquadricObj* sunQuadric);

void drawBallsShadow(GLUquadricObj* sunQuadric);