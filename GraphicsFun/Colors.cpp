#include "Colors.hpp"


float transparent[4] = { 1.0, 1.0, 1.0, 0.0 };
float white[4] = { 1.0, 1.0, 1.0, 1.0 };
float gray[4] = { 0.5, 0.5, 0.5, 1.0 };
float black[4] = { 0, 0, 0, 1.0 };
float oceanColor[4] = { 0, 0.4, 0.6, 1.0 };
float ufoBodyColor[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float ufoCockpitColor[4] = { 0.6, 0.6, 1, 0.5f };
float ufoCockpitRingColor[4] = { 0.3, 0.3, 0.3, 1.0f };
float grass[4] = { 0.0, 0.6, 0.0, 1 };
float sand[4] = { 0.9, 0.8, 0, 1 };
float rock[4] = { 0.4, 0.4, 0.4, 1 };
float moss[4] = { 0.4, 0.1, 0.3, 1 };
float creatureSkinColor[4] = { 1, 0.843, 0, 1 };
float ballColor[4] = { 0.9, 0.9, 1, 1 };

float moonlightColor[3] = { 0.6, 0.6, 0.8 };
float tractorBeamColor[3] = { 1, 1, 1 };
float fireRed[3] = { 1, 0.5, 0 };
float fireYellow[3] = { 1, 1, 0 };
float draftBlue[3] = { 0.8, 0.8, 1 };


void colorLerp(float out[4], float t, float colorA[4], float colorB[4])
{
	out[0] = colorA[0] + (colorB[0] - colorA[0]) * t;
	out[1] = colorA[1] + (colorB[1] - colorA[1]) * t;
	out[2] = colorA[2] + (colorB[2] - colorA[2]) * t;
	out[3] = colorA[3] + (colorB[3] - colorA[3]) * t;
}