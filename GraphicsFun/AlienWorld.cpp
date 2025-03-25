#include "AlienWorld.hpp"
using namespace std;


//--Globals ---------------------------------------------------------------
//Textures
GLUquadricObj* skyQuadric;

//Window
int windowWidthInit = 600;
int windowHeightInit = 600;

//Camera
Vector3 camPosition = Vector3(-30, 8, 0);
Vector3 camN = Vector3(0, 0, 0);
float camSpeed = 0.4;
float camYaw = 90;
float camPitch = 25;
float camSensitivity = 0.2;

//Lighting
float theta = 20;
float light[4] = { 500, 2000, 0, 0 };
float shadowMat[16] = { light[1], 0, 0, 0, -light[0], 0, -light[2],-1,
0, 0, light[1], 0, 0, 0, 0, light[1] };

//Input
bool inUp = false;
bool inDown = false;
bool inLeft = false;
bool inRight = false;
bool inShiftL = false;
bool inSpace = false;
bool inW = false;
bool inA = false;
bool inS = false;
bool inD = false;
int mouseDeltaX = 0;
int mouseDeltaY = 0;


void moonlight()
{
	glLightfv(GL_LIGHT0, GL_POSITION, light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, moonlightColor);
}


//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.

void drawSky()
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glTranslatef(camPosition.x, camPosition.y, camPosition.z);
	glRotatef(-90, 1, 0, 0);
	gluSphere(skyQuadric, 800.0, 36, 17);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void displayTranslucent()
{
	glEnable(GL_BLEND);

	drawUFOTranslucent();

	glDisable(GL_BLEND);
}


void display()  
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	Vector3 target = vecAdd(camPosition, camN);
	gluLookAt(camPosition.x, camPosition.y, camPosition.z, target.x, target.y, target.z, 0, 1, 0);

	moonlight();

	glDisable(GL_LIGHTING);
	drawSky();

	glEnable(GL_LIGHTING);
	drawUFO();

	drawIslands();



	glPushMatrix();
	glTranslatef(0, 6.01, 0);
	drawCreatures();

	glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glMultMatrixf(shadowMat);
	drawCreaturesShadow();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.01, 0);
	drawCreaturesB();

	glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glMultMatrixf(shadowMat);
	drawCreaturesShadowB();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.01, 0);
	drawBalls(skyQuadric);

	glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glMultMatrixf(shadowMat);
	drawBallsShadow(skyQuadric);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 6, 2);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[3]);
	gluSphere(skyQuadric, 2.0, 16, 16);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	drawParticles();

	drawOcean(camPosition);

	displayTranslucent();

	glFlush();
}

void generateQuadrics()
{
	skyQuadric = gluNewQuadric();
	gluQuadricDrawStyle(skyQuadric, GLU_FILL);
	gluQuadricNormals(skyQuadric, GLU_SMOOTH);
	gluQuadricTexture(skyQuadric, GL_TRUE);
}

//------- Initialize OpenGL parameters -----------------------------------
void initializeOpenGL()
{
	loadTextures();

	glClearColor(0, 0, 0, 1.0f);	//Background colour

	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHT0);

	generateQuadrics();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-8.0, 8.0, -4.5, 4.5, 5.0, 1000.0);   //Camera Frustum
}

//------------ Special key event callback ---------------------------------
void special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) { inUp = true; }
	if (key == GLUT_KEY_DOWN) { inDown = true; }
	if (key == GLUT_KEY_LEFT) { inLeft = true; }
	if (key == GLUT_KEY_RIGHT) { inRight = true; }
	if (key == GLUT_KEY_SHIFT_L) { inShiftL = true; }
}

void specialUp(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) { inUp = false; }
	if (key == GLUT_KEY_DOWN) { inDown = false; }
	if (key == GLUT_KEY_LEFT) { inLeft = false; }
	if (key == GLUT_KEY_RIGHT) { inRight = false; }
	if (key == GLUT_KEY_SHIFT_L) { inShiftL = false; }
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'l' || key == 'L') { glutLeaveMainLoop(); }

	if (key == ' ') { inSpace = true; launched = true; }
	if (key == 'w' || key == 'W') { inW = true; }
	if (key == 'a' || key == 'A') { inA = true; }
	if (key == 's' || key == 'S') { inS = true; }
	if (key == 'd' || key == 'D') { inD = true; }
}

void keyboardUp(unsigned char key, int x, int y)
{
	if (key == ' ') { inSpace = false; }
	if (key == 'w' || key == 'W') { inW = false; }
	if (key == 'a' || key == 'A') { inA = false; }
	if (key == 's' || key == 'S') { inS = false; }
	if (key == 'd' || key == 'D') { inD = false; }
}

void passiveMotion(int x, int y)
{
	mouseDeltaX = x + glutGet(GLUT_WINDOW_X) - glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseDeltaY = -(y + glutGet(GLUT_WINDOW_Y) - glutGet(GLUT_WINDOW_HEIGHT) / 2);
	SetCursorPos(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}


//Camera Movement
Vector3 moveCameraAxis(bool in, float yaw, float pitch, Vector3 movement)
{
	if (in) {
		Vector3 m = headingToNormalRad(TO_RAD(yaw), TO_RAD(pitch));
		return vecAdd(movement, m);
	}
	return movement;
}

void aimCamera()
{
	camYaw += camSensitivity * mouseDeltaX;
	camPitch += camSensitivity * mouseDeltaY;
	camYaw = clampAngle(camYaw);
	if (camPitch > 80) {
		camPitch = 80;
	}
	if (camPitch < -80) {
		camPitch = -80;
	}
	camPitch = clampAngle(camPitch);
	camN = headingToNormalRad(TO_RAD(camYaw), TO_RAD(camPitch));
}

void moveCamera()
{
	Vector3 movement = vecZero;
	movement = moveCameraAxis(inW && !inS, camYaw, camPitch, movement);
	movement = moveCameraAxis(inA && !inD, camYaw - 90, 0, movement);
	movement = moveCameraAxis(inS && !inW, camYaw + 180, -camPitch, movement);
	movement = moveCameraAxis(inD && !inA, camYaw + 90, 0, movement);
	movement = moveCameraAxis(inSpace && !inShiftL, 0, 90, movement);
	movement = moveCameraAxis(inShiftL && !inSpace, 0, -90, movement);
	movement = vecNorm(movement);
	camPosition = vecAdd(camPosition, vecScale(movement, camSpeed));
}


void update(int value)
{
	aimCamera();

	moveCamera();

	updateOcean();

	updateUFO();

	updateCreatures();

	updateBalls();

	updateParticles();

	glutPostRedisplay();
	glutTimerFunc(16, update, 0);
}


void initializeScene()
{
	
}


//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
   glutInitWindowSize(windowWidthInit, windowHeightInit); 
   glutInitWindowPosition(0, 0);
   glutCreateWindow("Alien World");
   initializeOpenGL();

   camN = headingToNormalRad(TO_RAD(camYaw), TO_RAD(camPitch));

   glutDisplayFunc(display);

   glutSpecialFunc(special); 
   glutSpecialUpFunc(specialUp);
   glutKeyboardFunc(keyboard);
   glutKeyboardUpFunc(keyboardUp);
   glutPassiveMotionFunc(passiveMotion);

   glutFullScreen();
   glutSetCursor(GLUT_CURSOR_NONE);
   SetCursorPos(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
   
   glutTimerFunc(16, update, 0);

   initializeScene();

   glutMainLoop();
   return 0;
}
