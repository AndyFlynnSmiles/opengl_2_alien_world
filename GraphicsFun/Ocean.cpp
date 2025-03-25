#include "Ocean.hpp"
using namespace std;


float waveShift = 0;
float waveSpeed = 0.02;
float waveXAmplitude = 2;
float waveXSquish = 0.4;
int waveXSpeedMultiple = 2;
float waveZAmplitude = 0.6;
float waveZSquish = 0.2;
int waveZSpeedMultiple = 1;
float sampleMultiplier = 1.07;
const int sampleRadius = 60;


float oceanWaveHeight(float s, float waveAmplitude, float waveSquish, float waveShift, float waveSpeedMultiple)
{
	return waveAmplitude * sin(waveSquish * s + waveShift * waveSpeedMultiple);
}

float oceanWaveSlope(float s, float waveAmplitude, float waveSquish, float waveShift, float waveSpeedMultiple)
{
	float slope = waveAmplitude * cos(waveSquish * s + waveShift * waveSpeedMultiple);
	if (slope == 0) {
		return 10000;
	}
	else {
		return 1 / slope;
	}
}

static void normFromSlopes(float xSlope, float zSlope)
{
	float xDir = 1;
	if (xSlope < 0) {
		xSlope = -xSlope;
		xDir = -xDir;
	}
	Vector3 xNorm = vecNorm(Vector3(xDir, xSlope, 0));

	float zDir = 1;
	if (zSlope < 0) {
		zSlope = -zSlope;
		zDir = -zDir;
	}
	Vector3 zNorm = vecNorm(Vector3(0, zSlope, zDir));

	glNormal3f((xNorm.x + zNorm.x) / 2, (xNorm.y + zNorm.y) / 2, (xNorm.z + zNorm.z) / 2);
}

void drawOcean(Vector3 camPosition)
{
	//Collect Samples
	int last = 2 * sampleRadius - 1;
	float sampleDistances[sampleRadius];
	float xHeightSamples[2 * sampleRadius];
	float xSlopeSamples[2 * sampleRadius];
	float zHeightSamples[2 * sampleRadius];
	float zSlopeSamples[2 * sampleRadius];

	float initSampleDistance = (abs(camPosition.y) + 4.8) / 8;
	float sampleDistance = initSampleDistance;

	xHeightSamples[0] = oceanWaveHeight(camPosition.x, waveXAmplitude, waveXSquish, waveShift, waveXSpeedMultiple);
	xSlopeSamples[0] = oceanWaveSlope(camPosition.x, waveXAmplitude, waveXSquish, waveShift, waveXSpeedMultiple);
	zHeightSamples[0] = oceanWaveHeight(camPosition.z, waveZAmplitude, waveZSquish, waveShift, waveZSpeedMultiple);
	zSlopeSamples[0] = oceanWaveSlope(camPosition.z, waveZAmplitude, waveZSquish, waveShift, waveZSpeedMultiple);

	xHeightSamples[2 * sampleRadius - 1] = xHeightSamples[0];
	xSlopeSamples[2 * sampleRadius - 1] = xSlopeSamples[0];
	zHeightSamples[2 * sampleRadius - 1] = zHeightSamples[0];
	zSlopeSamples[2 * sampleRadius - 1] = zSlopeSamples[0];

	sampleDistances[0] = 0;
	for (int i = 1; i < sampleRadius; i++) {
		sampleDistances[i] = sampleDistance;
		float disXPos = camPosition.x + sampleDistance;
		float disZPos = camPosition.z + sampleDistance;
		xHeightSamples[i] = oceanWaveHeight(disXPos, waveXAmplitude, waveXSquish, waveShift, waveXSpeedMultiple);
		xSlopeSamples[i] = oceanWaveSlope(disXPos, waveXAmplitude, waveXSquish, waveShift, waveXSpeedMultiple);
		zHeightSamples[i] = oceanWaveHeight(disZPos, waveZAmplitude, waveZSquish, waveShift, waveZSpeedMultiple);
		zSlopeSamples[i] = oceanWaveSlope(disZPos, waveZAmplitude, waveZSquish, waveShift, waveZSpeedMultiple);

		int iNeg = 2 * sampleRadius - 1 - i;
		float disXNeg = camPosition.x - sampleDistance;
		float disZNeg = camPosition.y - sampleDistance;
		xHeightSamples[iNeg] = oceanWaveHeight(disXNeg, waveXAmplitude, waveXSquish, waveShift, waveXSpeedMultiple);
		xSlopeSamples[iNeg] = oceanWaveSlope(disXNeg, waveXAmplitude, waveXSquish, waveShift, waveXSpeedMultiple);
		zHeightSamples[iNeg] = oceanWaveHeight(disZNeg, waveZAmplitude, waveZSquish, waveShift, waveZSpeedMultiple);
		zSlopeSamples[iNeg] = oceanWaveSlope(disZNeg, waveZAmplitude, waveZSquish, waveShift, waveZSpeedMultiple);

		sampleDistance *= sampleMultiplier;
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, oceanColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, oceanColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

	glPushMatrix();

	glBegin(GL_QUADS);

	for (int x = 1; x < sampleRadius; x++)
	{
		for (int z = 1; z < sampleRadius; z++)
		{
			normFromSlopes(xSlopeSamples[x - 1], zSlopeSamples[z - 1]);
			glVertex3f(camPosition.x + sampleDistances[x - 1], (xHeightSamples[x - 1] + zHeightSamples[z - 1]) / 2, camPosition.z + sampleDistances[z - 1]);
			normFromSlopes(xSlopeSamples[x - 1], zSlopeSamples[z]);
			glVertex3f(camPosition.x + sampleDistances[x - 1], (xHeightSamples[x - 1] + zHeightSamples[z]) / 2, camPosition.z + sampleDistances[z]);
			normFromSlopes(xSlopeSamples[x], zSlopeSamples[z]);
			glVertex3f(camPosition.x + sampleDistances[x], (xHeightSamples[x] + zHeightSamples[z]) / 2, camPosition.z + sampleDistances[z]);
			normFromSlopes(xSlopeSamples[x], zSlopeSamples[z - 1]);
			glVertex3f(camPosition.x + sampleDistances[x], (xHeightSamples[x] + zHeightSamples[z - 1]) / 2, camPosition.z + sampleDistances[z - 1]);
		}
	}

	for (int x = 1; x < sampleRadius; x++)
	{
		for (int z = 1; z < sampleRadius; z++)
		{
			normFromSlopes(xSlopeSamples[last - (x - 1)], zSlopeSamples[last - (z - 1)]);
			glVertex3f(camPosition.x - sampleDistances[x - 1], (xHeightSamples[last - (x - 1)] + zHeightSamples[last - (z - 1)]) / 2, camPosition.z - sampleDistances[z - 1]);
			normFromSlopes(xSlopeSamples[last - (x - 1)], zSlopeSamples[last - z]);
			glVertex3f(camPosition.x - sampleDistances[x - 1], (xHeightSamples[last - (x - 1)] + zHeightSamples[last - z]) / 2, camPosition.z - sampleDistances[z]);
			normFromSlopes(xSlopeSamples[last - x], zSlopeSamples[last - z]);
			glVertex3f(camPosition.x - sampleDistances[x], (xHeightSamples[last - x] + zHeightSamples[last - z]) / 2, camPosition.z - sampleDistances[z]);
			normFromSlopes(xSlopeSamples[last - x], zSlopeSamples[last - (z - 1)]);
			glVertex3f(camPosition.x - sampleDistances[x], (xHeightSamples[last - x] + zHeightSamples[last - (z - 1)]) / 2, camPosition.z - sampleDistances[z - 1]);
		}
	}

	for (int x = 1; x < sampleRadius; x++)
	{
		for (int z = 1; z < sampleRadius; z++)
		{
			normFromSlopes(xSlopeSamples[x - 1], zSlopeSamples[last - (z - 1)]);
			glVertex3f(camPosition.x + sampleDistances[x - 1], (xHeightSamples[x - 1] + zHeightSamples[last - (z - 1)]) / 2, camPosition.z - sampleDistances[z - 1]);
			normFromSlopes(xSlopeSamples[x - 1], zSlopeSamples[last - z]);
			glVertex3f(camPosition.x + sampleDistances[x - 1], (xHeightSamples[x - 1] + zHeightSamples[last - z]) / 2, camPosition.z - sampleDistances[z]);
			normFromSlopes(xSlopeSamples[x], zSlopeSamples[last - z]);
			glVertex3f(camPosition.x + sampleDistances[x], (xHeightSamples[x] + zHeightSamples[last - z]) / 2, camPosition.z - sampleDistances[z]);
			normFromSlopes(xSlopeSamples[x], zSlopeSamples[last - (z - 1)]);
			glVertex3f(camPosition.x + sampleDistances[x], (xHeightSamples[x] + zHeightSamples[last - (z - 1)]) / 2, camPosition.z - sampleDistances[z - 1]);
		}
	}

	for (int x = 1; x < sampleRadius; x++)
	{
		for (int z = 1; z < sampleRadius; z++)
		{
			normFromSlopes(xSlopeSamples[last - (x - 1)], zSlopeSamples[z - 1]);
			glVertex3f(camPosition.x - sampleDistances[x - 1], (xHeightSamples[last - (x - 1)] + zHeightSamples[z - 1]) / 2, camPosition.z + sampleDistances[z - 1]);
			normFromSlopes(xSlopeSamples[last - (x - 1)], zSlopeSamples[z]);
			glVertex3f(camPosition.x - sampleDistances[x - 1], (xHeightSamples[last - (x - 1)] + zHeightSamples[z]) / 2, camPosition.z + sampleDistances[z]);
			normFromSlopes(xSlopeSamples[last - x], zSlopeSamples[z]);
			glVertex3f(camPosition.x - sampleDistances[x], (xHeightSamples[last - x] + zHeightSamples[z]) / 2, camPosition.z + sampleDistances[z]);
			normFromSlopes(xSlopeSamples[last - x], zSlopeSamples[z - 1]);
			glVertex3f(camPosition.x - sampleDistances[x], (xHeightSamples[last - x] + zHeightSamples[z - 1]) / 2, camPosition.z + sampleDistances[z - 1]);
		}
	}

	glEnd();

	glPopMatrix();
}

void updateOcean()
{
	waveShift += waveSpeed;
	if (waveShift > 2 * PI) {
		waveShift -= 2 * PI;
	}
}