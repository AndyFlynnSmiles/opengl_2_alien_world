#include "OrbitCannon.hpp"

Vector3 sunPosition = Vector3(-10, 100, 80);
Vector3 cannonPosition = Vector3(-10, 15, 80);;

struct CannonBall
{
	int framesToLive;
	Vector3 position = vecZero;
	Vector3 velocity = vecZero;

	CannonBall(int framesToLive, Vector3 position, Vector3 velocity)
	{
		this->framesToLive = framesToLive;
		this->position = position;
		this->velocity = velocity;
	}
};

vector<CannonBall> balls;
int timer = 16;
void updateBalls()
{
	timer--;
	if (timer <= 0) {
		timer = 16;
		float nX = 1.6 / (float)(rand() % 5) - 1.6 / (float)(rand() % 5);
		float nZ = 1.6 / (float)(rand() % 5) - 1.6 / (float)(rand() % 5);
		float nY = 1;
		Vector3 n = vecNorm(Vector3(nX, nY, nZ));
		Vector3 velocity = vecScale(n, 0.4);
		CannonBall newBall = CannonBall(400, vecAdd(cannonPosition, Vector3(0, 11, 0)), velocity);
		balls.push_back(newBall);
	}

	vector<CannonBall>::iterator it;
	for (it = balls.begin(); it != balls.end(); it++)
	{
		Vector3 gravity = vecScale(vecNorm(vecSub(sunPosition, it->position)), 0.02);
		it->velocity = vecAdd(it->velocity, gravity);
		it->position = vecAdd(it->position, it->velocity);
		it->framesToLive--;
	}

	int i = 0;
	while (i < balls.size()) {
		if (balls[i].framesToLive <= 0 || vecDis(balls[i].position, sunPosition) < 10) {
			emitExplosion(balls[i].position);
			balls.erase(balls.begin() + i);
		}
		else {
			i++;
		}
	}
}

void drawCannon() 
{
	glPushMatrix();
	glTranslatef(cannonPosition.x, cannonPosition.y, cannonPosition.z);
	
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0, 11.01, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawCircle(2, 16);
	glPopMatrix();
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(0, 11, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(2.5, 1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(2, 10, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(4, 3, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(4, 6, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -6, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(4, 3, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -9, 0);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	emitDownDraft(vecAdd(cannonPosition, Vector3(0, -10, 0)));

	glPopMatrix();
}

void drawCannonShadow()
{
	glPushMatrix();
	glTranslatef(cannonPosition.x, cannonPosition.y, cannonPosition.z);

	glPushMatrix();
	glTranslatef(0, 11.01, 0);
	glRotatef(90, 1, 0, 0);
	drawCircle(2, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 11, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(2.5, 1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(2, 10, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(4, 3, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(4, 6, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -6, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(4, 3, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -9, 0);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	emitDownDraft(vecAdd(cannonPosition, Vector3(0, -10, 0)));

	glPopMatrix();
}

void drawSun(GLUquadricObj* sunQuadric)
{
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[2]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glTranslatef(sunPosition.x, sunPosition.y, sunPosition.z);
	glRotatef(-90, 1, 0, 0);
	gluSphere(sunQuadric, 10.0, 32, 16);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void drawSunShadow(GLUquadricObj* sunQuadric)
{
	glBindTexture(GL_TEXTURE_2D, txId[2]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glTranslatef(sunPosition.x, sunPosition.y, sunPosition.z);
	glRotatef(-90, 1, 0, 0);
	gluSphere(sunQuadric, 10.0, 32, 16);
	glPopMatrix();
}

void drawBall(CannonBall ball)
{
	glPushMatrix();
	glTranslatef(ball.position.x, ball.position.y, ball.position.z);
	glutSolidSphere(1.4, 8, 8);
	glPopMatrix();
}

void drawBalls(GLUquadricObj* sunQuadric)
{
	glPushMatrix();

	glTranslatef(0, -3, 0);

	drawSun(sunQuadric);

	drawCannon();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ballColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ballColor);
	for (int i = 0; i < balls.size(); i++) {
		CannonBall ball = balls[i];
		drawBall(ball);
	}

	glPopMatrix();
}

void drawBallsShadow(GLUquadricObj* sunQuadric)
{
	glPushMatrix();

	glTranslatef(0, -5, 0);

	drawSunShadow(sunQuadric);

	drawCannonShadow();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ballColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ballColor);
	for (int i = 0; i < balls.size(); i++) {
		CannonBall ball = balls[i];
		drawBall(ball);
	}

	glPopMatrix();
}