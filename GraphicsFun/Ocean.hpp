#pragma once

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include "Vector3.hpp"
#include "Colors.hpp"

#define PI 3.14159265359
#define TO_RAD(d) (d * (PI / 180))


float oceanWaveHeight(float s, float waveAmplitude, float waveSquish, float waveShift, float waveSpeedMultiple);

float oceanWaveSlope(float s, float waveAmplitude, float waveSquish, float waveShift, float waveSpeedMultiple);

static void normFromSlopes(float xSlope, float zSlope);

void drawOcean(Vector3 camPosition);

void updateOcean();