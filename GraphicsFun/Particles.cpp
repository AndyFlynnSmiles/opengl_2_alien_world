#include <vector>
#include "Particles.hpp"
using namespace std;

struct Particle
{
	int framesToLive;
	float color[3];
	float size;
	Vector3 position = vecZero;
	Vector3 velocity = vecZero;

	Particle(int framesToLive, float color[3], float size, Vector3 position, Vector3 velocity)
	{
		this->framesToLive = framesToLive;
		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
		this->size = size;
		this->position = position;
		this->velocity = velocity;
	}
};

vector<Particle> particles;

void emitExplosion(Vector3 position)
{
	for (int i = 0; i < 60; i++) {
		float nX = 60.0 / (float)(rand() % 100) - 60.0 / (float)(rand() % 100);
		float nZ = 60.0 / (float)(rand() % 100) - 60.0 / (float)(rand() % 100);
		float nY = 1;
		if (rand() % 2) {
			nY -= 2;
		}
		Vector3 n = vecNorm(Vector3(nX, nY, nZ));
		Vector3 velocity = vecScale(n, 0.2 / (rand() % 4));
		Particle newParticle = Particle((rand() % 5) + 20, fireRed, 1.2, vecAdd(position, velocity), velocity);
		particles.push_back(newParticle);
	}
}

void emitFlames(Vector3 position)
{
	for (int i = 0; i < 2; i++) {
		float nX = 60.0 / (float)(rand() % 100) - 60.0 / (float)(rand() % 100);
		float nZ = 60.0 / (float)(rand() % 100) - 60.0 / (float)(rand() % 100);
		float nY = 1;
		if (rand() % 2) {
			nY -= 2;
		}
		Vector3 n = vecNorm(Vector3(nX, nY, nZ));
		Vector3 velocity = vecScale(n, 0.07 / (rand() % 4));
		Particle newParticle = Particle((rand() % 5) + 10, fireYellow, 0.3, vecAdd(position, velocity), velocity);
		particles.push_back(newParticle);
	}
}

void emitDownDraft(Vector3 position)
{
	for (int i = 0; i < 3; i++) {
		float nX = 10.0 / (float)(rand() % 100) - 10.0 / (float)(rand() % 100);
		float nZ = 10.0 / (float)(rand() % 100) - 10.0 / (float)(rand() % 100);
		float nY = -1;
		Vector3 n = vecNorm(Vector3(nX, nY, nZ));
		Vector3 velocity = vecScale(n, 0.2 / (rand() % 4));
		Particle newParticle = Particle((rand() % 5) + 10, draftBlue, 0.3, vecAdd(position, velocity), velocity);
		particles.push_back(newParticle);
	}

}

void drawParticle(Particle particle)
{
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glColor3f(particle.color[0], particle.color[1], particle.color[2]);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[1]);

	glPushMatrix();
	glTranslatef(particle.position.x, particle.position.y, particle.position.z);
	glScalef(particle.size, particle.size, particle.size);

	glBegin(GL_QUADS);
	//A quad on the xy-plane
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, -0.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.5, 0);

	//A quad on the yz-plane
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.5, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.5, 0.5);

	//A quad on the xz-plane
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0, 0.5);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void drawParticles()
{
	for (int i = 0; i < particles.size(); i++) {
		Particle particle = particles[i];
		drawParticle(particle);
	}
}

void updateParticles()
{
	vector<Particle>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++)
	{
		it->position = vecAdd(it->position, it->velocity);
		it->framesToLive--;
	}

	int i = 0;
	while (i < particles.size()) {
		if (particles[i].framesToLive <= 0) {
			particles.erase(particles.begin() + i);
		}
		else {
			i++;
		}
	}
}

