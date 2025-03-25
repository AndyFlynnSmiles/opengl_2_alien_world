#pragma once

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include "Vector3.hpp"
#include "Macros.hpp"
#include "Colors.hpp"


void drawCircle(float radius, int numSegments);

void drawQuadRing(float y, float height, float radiusBottom, float radiusTop, int edges, float slopeYBottom, float slopeYTop);

void drawRingsFromFunc(float height, int ringNum, int edges, float (*func)(float), float (*funcN)(float));

void drawQuadRingColor(float y, float height, float radiusBottom, float radiusTop, int edges, float slopeYBottom, float slopeYTop, float colorBottom[4], float colorTop[4]);

void drawRingsFromFuncColor(float height, int ringNum, int edges, float (*func)(float), float (*funcN)(float), float colorBottom[4], float colorTop[4], float (*funcT)(float));