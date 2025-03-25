#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include <GL/freeglut.h>
#include "Vector3.hpp"
#include "Modeling.hpp"
#include "Animation.hpp"
#include "Macros.hpp"
#include "Particles.hpp"

extern bool launched;

void drawUFO();

void drawUFOTranslucent();

void updateUFO();