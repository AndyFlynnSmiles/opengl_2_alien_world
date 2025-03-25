#pragma once

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include "Vector3.hpp"
#include "Macros.hpp"
#include "Colors.hpp"
#include "Particles.hpp"


void drawCreature(Vector3 position);

void updateCreatures();

void drawCreatures();
void drawCreaturesShadow();

void drawCreaturesB();
void drawCreaturesShadowB();