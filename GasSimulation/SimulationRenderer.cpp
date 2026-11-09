#include "SimulationRenderer.h"
#include <iostream>
void SimulationRenderer::hook(Simulation* simulation) {

	sim = simulation;

}

void SimulationRenderer::render(GLFWwindow* window)
{
	for (int i = 0; i < sim->getParticleCount(); i++) {
		Vec2D pos = sim->particles[i].position - Vec2D(sim->getWorldSize().x, sim->getWorldSize().y) * 0.5;
		srand(i*500);
		hsv color((rand() % 360),1.0,1.0);
		drawCircle(pos.x, pos.y, 0.005, color, GL_POLYGON);
	}

	Vec2D corner1 = Vec2D(sim->getWorldSize().x, sim->getWorldSize().y) * -0.5;
	Vec2D corner2 = Vec2D(sim->getWorldSize().x, sim->getWorldSize().y) * 0.5;
	hsv color(0, 0, 1);
	drawLine(-sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, -sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, color);
	drawLine(-sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, color);
	drawLine(sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, color);
	drawLine(sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, -sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, color);
}

void SimulationRenderer::drawCircle(double x, double y, double r, hsv color, GLenum type) {

	glBegin(type);
	double e;

	if (r * conversion < 20) {
		e = 12;
	}
	else if (r * conversion < 100) {
		e = 18;
	}
	else if (r * conversion < 300) {
		e = 24;
	}
	else {
		e = 120;
	}

	rgb col = convertToRGB(color);
	glColor3f(col.red, col.green, col.blue);
	for (int i = 0; i < e; i++) {
		glVertex2d(x + r * cos(2 * i * M_PI / e), y + r * sin(2 * i * M_PI / e));

	}
	glEnd();
}

void SimulationRenderer::drawLine(double x1, double y1, double x2, double y2, hsv color) {
	GLenum type = GL_LINES;
	rgb col = convertToRGB(color);
	glColor3f(col.red, col.green, col.blue);
	glLineWidth(1.0);
	glBegin(type);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}