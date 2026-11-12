#include "SimulationRenderer.h"
#include <iostream>
void SimulationRenderer::hook(Simulation* simulation) {

	sim = simulation;
	Vec3D world_size = simulation->getWorldSize();
	cameraR = fmax(world_size.x, fmax(world_size.y, world_size.z))*sqrt(3);
	
}

void SimulationRenderer::renderBox(GLFWwindow* window, Vec3D i_hat, Vec3D j_hat) {

	Vec3D world_size = sim->getWorldSize();

	Vec2D corners[8];
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 1; k++) {

				corners[i * 4 + j * 2 + k] = renderSpaceToScreenSpace(boxSpaceToRenderSpace(Vec3D(i*world_size.x, j*world_size.y, k*world_size.z),world_size),i_hat,j_hat);

			}
		}
	}

	int pairs1[12] = {0,0,0,1,1,2,2,3,4,4,5,6};
	int pairs2[12] = {1,2,4,3,5,3,6,7,5,6,7,7};

	for (int i = 0; i < 12; i++) {

		drawLine(corners[pairs1[i]].x, corners[pairs1[i]].y, corners[pairs2[i]].x, corners[pairs2[i]].y,hsv(0,0,1));

	}
	return;
}

void SimulationRenderer::render(GLFWwindow* window)
{
	view_vector = Vec3D(sin(cameraTheta) * cos(cameraPhi), sin(cameraTheta) * sin(cameraPhi), cos(cameraTheta));
	camera = view_vector * -cameraR;

	Vec3D i_hat = Vec3D(-sin(cameraPhi), cos(cameraPhi), 0);
	Vec3D j_hat = cross(i_hat, view_vector);

	for (int i = 0; i < sim->getParticleCount(); i++) {
		Vec2D pos = renderSpaceToScreenSpace(boxSpaceToRenderSpace(sim->particles[i].position,sim->getWorldSize()),i_hat,j_hat);
		srand(i*500);
		hsv color((rand() % 360),1.0,1.0);
		drawCircle(pos.x, pos.y, 0.005, color, GL_POLYGON);
	}
	/*
	Vec2D corner1 = Vec2D(sim->getWorldSize().x, sim->getWorldSize().z) * -0.5;
	Vec2D corner2 = Vec2D(sim->getWorldSize().x, sim->getWorldSize().z) * 0.5;
	hsv color(0, 0, 1);
	drawLine(-sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, -sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, color);
	drawLine(-sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, color);
	drawLine(sim->getWorldSize().x * 0.5, sim->getWorldSize().y * 0.5, sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, color);
	drawLine(sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, -sim->getWorldSize().x * 0.5, -sim->getWorldSize().y * 0.5, color);
	*/
	renderBox(window, i_hat, j_hat);
}

void SimulationRenderer::drawCircle(double x, double y, double r, hsv color, GLenum type) {

	glBegin(type);
	double e;

	if (r< 20) {
		e = 12;
	}
	else if (r< 100) {
		e = 18;
	}
	else if (r< 300) {
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

Vec2D SimulationRenderer::renderSpaceToScreenSpace(Vec3D pos, Vec3D i_hat, Vec3D j_hat) {
	
	Vec3D Pos = (pos - camera) * projection_screen_dist/((pos-camera)*view_vector) - view_vector*projection_screen_dist;
	return Vec2D(Pos * i_hat, Pos * j_hat);

}

void SimulationRenderer::rotateCamera(double dTheta, double dPhi) {

	cameraTheta = clamp(cameraTheta + dTheta, 0, M_PI);
	cameraPhi = fmod(cameraPhi + dPhi, 2 * M_PI);

}

double zoom_parameter = 0;

double zoom_clamp(double x) {
	if (x < 0)return exp(x);
	return x + 1;
}

void SimulationRenderer::zoom(double dz) {
	zoom_parameter += dz;
	projection_screen_dist = initial_screen_dist * zoom_clamp(zoom_parameter);
}