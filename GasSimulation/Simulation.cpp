#include "Simulation.h"
#include <random>
#include <iostream>
#include <time.h>

int Simulation::initialize(int p_count) {
	particle_count = p_count;
	particles = (Particle*)malloc(sizeof(Particle) * particle_count);
	
	if (particles == nullptr) {
		return -1;
	}

	srand(time(NULL));
	for (int i = 0; i < particle_count; i++) {
		Vec3D prev_location(0.001 * (rand() % 1000) * box_width, 0.001 * (rand() % 1000) * box_depth, 0.001 * (rand() % 1000) * box_height);
		//Vec2D prev_location = getWorldSize()*0.5;
		double v = (0.001*(rand()%1000)+1)*3;
		double x1, x2, x3;
		do {

			x1 = (0.002 * (rand() % 1000) - 1.0);
			x2 = (0.002 * (rand() % 1000) - 1.0);
			x3 = (0.002 * (rand() % 1000) - 1.0);

		} while (x1 * x1 + x2 * x2 + x3 * x3 <= 1.0);
		Particle p(prev_location, Vec3D(x1,x2,x3).normalize()*v);
		p.id = i;
		particles[i] = p;

	}
	return 1;
}

double before_timer;

void timerBegin() {
	before_timer = glfwGetTime();
}
double timerEnd() {
	return glfwGetTime() - before_timer;
}

void Simulation::mainLoop() {

	double freq = 60.0;
	double lastFrameTime = glfwGetTime();
	timerBegin();
	while (!ended) {
		//framerate control
		double now = glfwGetTime();
		if (now - lastFrameTime < 1 / freq) {
			continue;
		}

		lastFrameTime = now;

		if (paused) {
			continue;
		}
		if (timerEnd() > 0.5) {
			screenshot();
			timerBegin();
		}

		advanceTime();
	}

	free(particles);
}

void Simulation::end() {
	ended = true;
}

void Simulation::handleBoundaries(Particle* p) {
	Vec3D vel = p->velocity;
	if (p->position.x > box_width or p->position.x < 0) {
		p->position.x = clamp(p->position.x, 0,box_width);
		p->velocity.x = p->velocity.x*-1;
	}
	if (p->position.y > box_depth or p->position.y < 0) {
		p->position.y = clamp(p->position.y, 0, box_depth);
		p->velocity.y = p->velocity.y * -1;
	}
	if (p->position.z > box_height or p->position.z < 0) {
		p->position.z = clamp(p->position.z, 0, box_height);
		p->velocity.z = p->velocity.z * -1;
	}
}

void Simulation::advanceTime() {

	for (int i = 0; i < particle_count; i++) {
		particles[i].position = particles[i].position + particles[i].velocity * dt;
		handleBoundaries(particles + i);
	}

}

void Simulation::screenshot() {

	int left_partition = 0;
	for (int i = 0; i < particle_count; i++) {

		if (particles[i].position.x < box_width / 2)left_partition++;

	}
	printf("%d\n", left_partition);

}

void Simulation::togglePause() {
	paused = !paused;
}

int Simulation::getParticleCount() {
	return particle_count;
}
Vec3D Simulation::getWorldSize() {
	return Vec3D(box_width, box_depth, box_height);
}