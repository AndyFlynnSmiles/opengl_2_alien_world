#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include <GL/freeglut.h>
#include "Vector3.hpp"
#include "Macros.hpp"
#include "Textures.hpp"
#include "Colors.hpp"


void emitExplosion(Vector3 position);
void emitFlames(Vector3 position);
void emitDownDraft(Vector3 position);

void drawParticles();

void updateParticles();