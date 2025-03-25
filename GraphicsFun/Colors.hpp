#pragma once


extern float transparent[4];
extern float white[4];
extern float gray[4];
extern float black[4];
extern float oceanColor[4];
extern float ufoBodyColor[4];
extern float ufoCockpitColor[4];
extern float ufoCockpitRingColor[4];
extern float grass[4];
extern float greon[4];
extern float sand[4];
extern float rock[4];
extern float moss[4];
extern float creatureSkinColor[4];
extern float ballColor[4];

extern float moonlightColor[3];
extern float tractorBeamColor[3];
extern float fireRed[3];
extern float fireYellow[3];
extern float draftBlue[3];


void colorLerp(float out[4], float t, float colorA[4], float colorB[4]);