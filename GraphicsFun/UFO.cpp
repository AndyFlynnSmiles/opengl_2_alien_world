#include "UFO.hpp"


Vector3 ufoPosition = Vector3(-29, 9, 34);
Vector3 ufoTarget = ufoPosition;
float targetTotalDis = 0;
Vector3 ufoTargetBoundsMin = Vector3(-100, 30, -100);
Vector3 ufoTargetBoundsMax = Vector3(100, 80, 100);
float ufoTargetMaxDis = 16;
float moveSpeed = 0.01;
int moveSpeedMin = 1;
int moveSpeedMax = 3;

float lightRingAngle = 0;
float lightRingSpinSpeed = 1;
bool flickerLightStates[12] = { false };
int lightFlickerChancePerFrame = 6; //chance / 1000


float cockpitSphereSlope(float y)
{
	float n = -(y / pow(9 - y * y, 0.5));
	if (isinf(n)) {
		return -10000;
	}
	return n;
}

float cockpitSphere(float y)
{
	return pow(9 - y * y, 0.5);
}

float bodyParabolaSlope(float y)
{
	return -4 * y + 8;
}

float bodyParabola(float y)
{
	return -(2 * (y * (y - 4)));
}

void drawLightRing()
{
	glPushMatrix();

	glTranslatef(0, 2.2, 0);
	glRotatef(lightRingAngle, 0, 1, 0);
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(8.2,0.4, 16, 4);
	glPopMatrix();

	
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.2, 0);
	glPushMatrix();
	glRotatef(360 / 32.0, 0, 1, 0);
	
	for (int i = 0; i < 16; i++) {
		glTranslatef(0, 0, 8.05);
		drawCircle(0.2, 8);
		glTranslatef(0, 0, -8.05);
		glRotatef(360 / 16.0, 0, 1, 0);
	}
	
	glPopMatrix();
	glEnable(GL_LIGHTING);


	glPopMatrix();
}

void drawLowerFlickerLightRing()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

	glPushMatrix();

	glTranslatef(0, 1.2, 0);

	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 0);
	glTranslatef(0, -0.2, 0);
	glPushMatrix();
	glRotatef(360 / 32.0, 0, 1, 0);

	for (int i = 0; i < 12; i++) {
		if (flickerLightStates[i]) {
			glEnable(GL_LIGHTING);
		} else {
			glDisable(GL_LIGHTING);
		}
		glTranslatef(0, 0, 6);
		glRotatef(76, 1, 0, 0);
		drawCircle(0.4, 8);
		glRotatef(-76, 1, 0, 0);
		glTranslatef(0, 0, -6);
		glRotatef(360 / 12.0, 0, 1, 0);
	}

	glPopMatrix();
	glEnable(GL_LIGHTING);


	glPopMatrix();
}

void tractorBeam()
{
	glEnable(GL_LIGHT1);
	float light[] = { ufoPosition.x, ufoPosition.y-2, ufoPosition.z, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, tractorBeamColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, tractorBeamColor);
	float spotdir[] = { 0, -1.0, 0 };
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);

}

void drawUFO()
{
	tractorBeam();

	glPushMatrix();
	glTranslatef(ufoPosition.x, ufoPosition.y, ufoPosition.z);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ufoBodyColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ufoBodyColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

	drawRingsFromFunc(4, 16, 32, bodyParabola, bodyParabolaSlope);

	glPushMatrix();
	glTranslatef(0, 4, 0);
	glRotatef(90, 1, 0, 0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ufoCockpitRingColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ufoCockpitRingColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

	glutSolidCylinder(3.2, 0.5, 32, 16);
	glPopMatrix();

	drawLightRing();

	drawLowerFlickerLightRing();

	glPushMatrix();

	glTranslatef(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(4, 1, 32, 4);
	
	glTranslatef(0, 0, 1.01);

	glDisable(GL_LIGHTING);
	glColor3f(1,0.5,1);
	drawCircle(3.4, 32);
	glEnable(GL_LIGHTING);

	glTranslatef(0, 0, -8.8);
	glutSolidCylinder(0.05, 2.3, 32, 4);

	glDisable(GL_LIGHTING);
	glColor3f(1, 0.5, 1);
	glutSolidSphere(0.2, 16, 16);
	glEnable(GL_LIGHTING);

	glPopMatrix();

	glPopMatrix();
}

void drawUFOTranslucent()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef(ufoPosition.x, ufoPosition.y, ufoPosition.z);

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ufoCockpitColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ufoCockpitColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 60);
	glTranslatef(0, 3.5, 0);
	drawRingsFromFunc(3, 16, 32, cockpitSphere, cockpitSphereSlope);
	glPopMatrix();

	glPopMatrix();
}

int takeOffTimer = 300;
bool launched = false;
void updateUFO()
{
	if (launched) {
		lightRingAngle += lightRingSpinSpeed;
		lightRingAngle = clampAngle(lightRingAngle);

		for (int i = 0; i < 12; i++) {
			if (rand() % 1000 <= lightFlickerChancePerFrame) {
				flickerLightStates[i] = !flickerLightStates[i];
			}
		}
		if (takeOffTimer <= 0) {
			if (vecDis(ufoPosition, ufoTarget) <= ufoTargetMaxDis) {
				float boundsWidth = ufoTargetBoundsMax.x - ufoTargetBoundsMin.x;
				float boundsHeight = ufoTargetBoundsMax.y - ufoTargetBoundsMin.y;
				float boundsDepth = ufoTargetBoundsMax.z - ufoTargetBoundsMin.z;
				ufoTarget = vecAdd(ufoTargetBoundsMin, Vector3(rand() % (int)boundsWidth, rand() % (int)boundsHeight, rand() % (int)boundsDepth));
				targetTotalDis = vecDis(ufoPosition, ufoTarget);
				moveSpeed = moveSpeedMin + (rand() % (moveSpeedMax - moveSpeedMin));
			}

			Vector3 moveDir = vecNorm(vecSub(ufoTarget, ufoPosition));
			float progress = vecDis(ufoPosition, ufoTarget) / targetTotalDis;
			float step = easeInOut(progress) * moveSpeed;
			Vector3 movement = vecScale(moveDir, step);
			ufoPosition = vecAdd(ufoPosition, movement);
		} else {
			takeOffTimer--;

			if (takeOffTimer <= 200) {
				for (int i = 0; i < 8; i++) {
					emitDownDraft(vecAdd(ufoPosition, Vector3(cos(((2 * PI) / 8) * i) * 6, 1, sin(((2 * PI) / 8) * i) * 6)));
				}

				moveSpeed *= 1.04;

				Vector3 moveDir = Vector3(0, 1, 0);
				float progress = (float)takeOffTimer / (float)200;
				float step = easeInOut(progress) * moveSpeed;
				Vector3 movement = vecScale(moveDir, step);
				ufoPosition = vecAdd(ufoPosition, movement);
				ufoTarget = ufoPosition;
			}
		}
	}
}