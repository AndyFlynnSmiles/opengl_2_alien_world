#include "Islands.hpp"
using namespace std;

float height = 1;
float radius = 1;
float shoreWidth = 1;

float shoreSlopeFunc(float y)
{
	y /= height;
	float n = -(y / pow(1 - y * y, 0.5)) * shoreWidth;
	if (isinf(n)) {
		return -10000;
	}
	return n;
}

float flatSlopeFunc(float y)
{
	return -10000;
}

float evenFunc(float y)
{
	y /= height;
	return radius * y;
}

float shoreFunc(float y)
{
	y /= height;
	return radius + (pow(1 - y * y, 0.5)) * shoreWidth;
}

float shoreFuncT(float t)
{
	return max(0.0f, t * 4 - 3);
}

void drawIsland(int shoreRingNum, int edges, float plateauRadius, float shoreWid, float islandHeight, float colorBottom[4], float colorTop[4])
{
	height = islandHeight;
	radius = plateauRadius;
	shoreWidth = shoreWid;
	drawRingsFromFuncColor(height, shoreRingNum, edges, shoreFunc, shoreSlopeFunc, colorBottom, colorTop, shoreFuncT);
	
	glPushMatrix();
	glTranslatef(0, height, 0);
	glNormal3f(0, 0, -1);

	float plateauColor[4];
	colorLerp(plateauColor, shoreFuncT(1), colorBottom, colorTop);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, plateauColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, plateauColor);

	height = 0.0001;
	drawRingsFromFunc(0.0001, (int)(radius * 3 + 2), edges, evenFunc, flatSlopeFunc);
	glPopMatrix();
}

void drawIslands()
{
	glPushMatrix();

	glTranslatef(0, -2, 0);
	drawIsland(16, 32, 5, 14, 5, sand, grass);

	glTranslatef(6, 0, 16);
	drawIsland(16, 32, 3, 6, 14, rock, moss);

	glTranslatef(-15, 0, -8);
	drawIsland(16, 32, 12, 3, 8, grass, grass);

	glTranslatef(-20, 0, 70);
	drawIsland(32, 96, 55, 16, 5, sand, grass);

	glTranslatef(0, 3, -44);
	drawIsland(16, 32, 12, 3, 8, rock, grass);

	glPopMatrix();
}