#include "Creature.hpp"

float coreAngleA = 0;
float coreAngleB = 0;
float coreAngleC = 0;
float rotationSpeed = 1;

Vector3 aStartPosition = Vector3(-8, 9, 10);
Vector3 aPosition = aStartPosition;
Vector3 aTarget = aPosition;
float aTargetTotalDis = 0;
Vector3 aTargetBoundsMin = Vector3(-7, 9, -7);
Vector3 aTargetBoundsMax = Vector3(7, 9, 7);
float aTargetMaxDis = 1;
float aMoveSpeed = 0.1;

Vector3 bStartPosition = Vector3(5, 6, 50);
Vector3 bPosition = bStartPosition;
Vector3 bTarget = bPosition;
float bTargetTotalDis = 0;
Vector3 bTargetBoundsMin = Vector3(-14, 9, -14);
Vector3 bTargetBoundsMax = Vector3(14, 9, 14);
float bTargetMaxDis = 1;
float bMoveSpeed = 0.1;

void drawCore(Vector3 position)
{
	glPushMatrix();

	emitFlames(position);
	
	glPushMatrix();
	glRotatef(coreAngleA, 1, 0, 0);
	glScalef(1, 1, 3);
	glutSolidTorus(0.04, 1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glRotatef(coreAngleB, 0, 1, 0);
	glScalef(1.1, 1.1, 1.1);
	glScalef(1, 1, 3);
	glutSolidTorus(0.04, 1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(coreAngleC, 0, 1, 0);
	glScalef(1.2, 1.2, 1.2);
	glScalef(1, 1, 3);
	glutSolidTorus(0.04, 1, 32, 32);
	glPopMatrix();
	
	glPopMatrix();
}

void drawHead() {
	glPushMatrix();

	glTranslatef(0, 1.6, 0);
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 6);
	glutSolidTorus(0.04, 0.6, 32, 32);
	glPopMatrix();

	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();
		glRotatef((360 / 6) * i, 0, 1, 0);
		glTranslatef(0.7, 0, 0);
		glutSolidSphere(0.15, 12, 12);
		glPopMatrix();
	}

	glDisable(GL_LIGHTING);
	glColor3f(fireRed[0], fireRed[1], fireRed[2]);
	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();
		glRotatef((360 / 6) * i, 0, 1, 0);
		glTranslatef(0.8, 0, 0);
		glutSolidSphere(0.08, 12, 12);
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void drawHeadShadow() {
	glPushMatrix();

	glTranslatef(0, 1.6, 0);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 6);
	glutSolidTorus(0.04, 0.6, 32, 32);
	glPopMatrix();

	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();
		glRotatef((360 / 6) * i, 0, 1, 0);
		glTranslatef(0.7, 0, 0);
		glutSolidSphere(0.15, 12, 12);
		glPopMatrix();
	}

	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();
		glRotatef((360 / 6) * i, 0, 1, 0);
		glTranslatef(0.8, 0, 0);
		glutSolidSphere(0.08, 12, 12);
		glPopMatrix();
	}

	glPopMatrix();
}

void updateCores()
{
	coreAngleA += rotationSpeed;
	coreAngleB += rotationSpeed;
	coreAngleC += rotationSpeed;
}

void drawCreature(Vector3 position)
{
	glPushMatrix();

	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, creatureSkinColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, creatureSkinColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);

	emitFlames(position);
	drawCore(position);
	drawHead();
	emitDownDraft(vecAdd(position, Vector3(0, -2.3, 0)));
	
	glPushMatrix();
	glTranslatef(0, -1.3, 0);
	glRotatef(90, 1, 0, 0),
	glutSolidCone(0.7, 1, 16, 16);
	glPopMatrix();

	glPopMatrix();
}

void drawCreatureShadow(Vector3 position)
{
	glPushMatrix();

	drawCore(position);
	drawHeadShadow();

	glPushMatrix();
	glTranslatef(0, -1.3, 0);
	glRotatef(90, 1, 0, 0),
		glutSolidCone(0.7, 1, 16, 16);
	glPopMatrix();

	glPopMatrix();
}

void drawCreatures() 
{
	glPushMatrix();
	glTranslatef(aPosition.x, aPosition.y - 6, aPosition.z);
	drawCreature(aPosition);
	glPopMatrix();
}

void drawCreaturesB()
{
	glPushMatrix();
	glTranslatef(bPosition.x, bPosition.y - 3, bPosition.z);
	drawCreature(bPosition);
	glPopMatrix();
}

void drawCreaturesShadow()
{
	glPushMatrix();
	glTranslatef(aPosition.x, aPosition.y - 6, aPosition.z);
	drawCreatureShadow(aPosition);
	glPopMatrix();
}

void drawCreaturesShadowB()
{
	glPushMatrix();
	glTranslatef(bPosition.x, bPosition.y - 3, bPosition.z);
	drawCreatureShadow(bPosition);
	glPopMatrix();
}

void updateCreatures()
{
	updateCores();

	if (vecDis(aPosition, aTarget) <= aTargetMaxDis) {
		float boundsWidth = aTargetBoundsMax.x - aTargetBoundsMin.x;
		float boundsHeight = aTargetBoundsMax.y - aTargetBoundsMin.y;
		float boundsDepth = aTargetBoundsMax.z - aTargetBoundsMin.z;
		aTarget = vecAdd(aTargetBoundsMin, Vector3(rand() % (int)boundsWidth, -9, rand() % (int)boundsDepth));
		aTarget = vecAdd(aTarget, aStartPosition);
		aTargetTotalDis = vecDis(aPosition, aTarget);
	}

	Vector3 moveDir = vecNorm(vecSub(aTarget, aPosition));
	float progress = vecDis(aPosition, aTarget);
	float step = aMoveSpeed;
	Vector3 movement = vecScale(moveDir, step);
	aPosition = vecAdd(aPosition, movement);


	if (vecDis(bPosition, bTarget) <= bTargetMaxDis) {
		float boundsWidth = bTargetBoundsMax.x - bTargetBoundsMin.x;
		float boundsHeight = bTargetBoundsMax.y - bTargetBoundsMin.y;
		float boundsDepth = bTargetBoundsMax.z - bTargetBoundsMin.z;
		bTarget = vecAdd(bTargetBoundsMin, Vector3(rand() % (int)boundsWidth, -9, rand() % (int)boundsDepth));
		bTarget = vecAdd(bTarget, bStartPosition);
		bTargetTotalDis = vecDis(bPosition, bTarget);
	}

	moveDir = vecNorm(vecSub(bTarget, bPosition));
	progress = vecDis(bPosition, bTarget);
	step = bMoveSpeed;
	movement = vecScale(moveDir, step);
	bPosition = vecAdd(bPosition, movement);
}