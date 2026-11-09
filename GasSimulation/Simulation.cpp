#include "Simulation.h"
#include <random>
#include <iostream>

int Simulation::initialize() {

	particles = (Particle*)malloc(sizeof(Particle) * particle_count);
	
	if (particles == nullptr) {
		return -1;
	}

	srand(glfwGetTime()*100000);
	for (int i = 0; i < particle_count; i++) {
		Vec2D prev_location(0.001 * (rand() % 1000) * box_width, 0.001 * (rand() % 1000) * box_height);
		//Vec2D prev_location = getWorldSize()*0.5;
		double v = (0.001*(rand()%1000)+1)*3;
		double theta = 0.001 * (rand() % 1000)*2*M_PI;
		Particle p(prev_location, Vec2D(cos(theta),sin(theta))*v);
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

double clamp(double value, double minimum, double maximum) {
	return fmax(fmin(value, maximum), minimum);
}

void Simulation::handleBoundaries(Particle* p) {
	Vec2D vel = p->velocity;
	if (p->position.x > box_width or p->position.x < 0) {
		p->position.x = clamp(p->position.x, 0,box_width);
		p->velocity.x = p->velocity.x*-1;
	}
	if (p->position.y > box_height or p->position.y < 0) {
		p->position.y = clamp(p->position.y, 0, box_height);
		p->velocity.y = p->velocity.y * -1;
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
Vec2D Simulation::getWorldSize() {
	return Vec2D(box_width, box_height);
}