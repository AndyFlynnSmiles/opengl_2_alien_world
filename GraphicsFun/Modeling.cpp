#include "Modeling.hpp"

void drawCircle(float radius, int numSegments)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= numSegments; ++i) {
		float theta = 2.0f * PI * float(i) / float(numSegments);
		glVertex3f(radius * cos(theta), radius * sin(theta), 0);
	}
	glEnd();
}

void drawQuadRing(float y, float height, float radiusBottom, float radiusTop, int edges, float slopeYBottom, float slopeYTop)
{
	glPushMatrix();
	float angleStep = (2 * PI) / edges;

	glTranslatef(0, y, 0);

	glBegin(GL_QUAD_STRIP);

	Vector3 norm = Vector3(0, 0, 0);
	for (int i = 0; i <= edges; i++) {
		float cosAtStep = cos(angleStep * i);
		float sinAtStep = sin(angleStep * i);
		norm = vecNorm(Vector3(cosAtStep, slopeYTop, sinAtStep));
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(radiusTop * cosAtStep, height, radiusTop * sinAtStep);
		norm = vecNorm(Vector3(cosAtStep, slopeYBottom, sinAtStep));
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(radiusBottom * cosAtStep, 0, radiusBottom * sinAtStep);
	}

	glEnd();

	glPopMatrix();
}

void drawRingsFromFunc(float height, int ringNum, int edges, float (*func)(float), float (*funcN)(float))
{
	float yStep = height / (ringNum - 1);

	for (int i = 0; i < ringNum - 1; i++) {
		float slopeYBottom = -funcN(yStep * i);
		float slopeYTop = -funcN(yStep * (i + 1));
		drawQuadRing(yStep * i, yStep, func(yStep * i), func(yStep * (i + 1)), edges, slopeYBottom, slopeYTop);
	}
}

void drawQuadRingColor(float y, float height, float radiusBottom, float radiusTop, int edges, float slopeYBottom, float slopeYTop, float colorBottom[4], float colorTop[4])
{
	glPushMatrix();
	float angleStep = (2 * PI) / edges;

	glTranslatef(0, y, 0);

	glBegin(GL_QUAD_STRIP);

	Vector3 norm = Vector3(0, 0, 0);
	for (int i = 0; i <= edges; i++) {
		float cosAtStep = cos(angleStep * i);
		float sinAtStep = sin(angleStep * i);
		norm = vecNorm(Vector3(cosAtStep, slopeYTop, sinAtStep));
		glNormal3f(norm.x, norm.y, norm.z);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorTop);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorTop);
		glVertex3f(radiusTop * cosAtStep, height, radiusTop * sinAtStep);
		norm = vecNorm(Vector3(cosAtStep, slopeYBottom, sinAtStep));
		glNormal3f(norm.x, norm.y, norm.z);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorBottom);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorBottom);
		glVertex3f(radiusBottom * cosAtStep, 0, radiusBottom * sinAtStep);
	}

	glEnd();

	glPopMatrix();
}

void drawRingsFromFuncColor(float height, int ringNum, int edges, float (*func)(float), float (*funcN)(float), float colorBottom[4], float colorTop[4], float (*funcT)(float))
{
	float yStep = height / (ringNum - 1);

	for (int i = 0; i < ringNum - 1; i++) {
		float slopeYBottom = -funcN(yStep * i);
		float slopeYTop = -funcN(yStep * (i + 1));
		float ringColorBottom[4];
		colorLerp(ringColorBottom, funcT((yStep * i) / height), colorBottom, colorTop);

		float ringColorTop[4];
		colorLerp(ringColorTop, funcT((yStep * (i + 1)) / height), colorBottom, colorTop);
		drawQuadRingColor(yStep * i, yStep, func(yStep * i), func(yStep * (i + 1)), edges, slopeYBottom, slopeYTop, ringColorBottom, ringColorTop);
	}
}