#include "Simulation.h"

class SimulationRenderer
{

public:
	void render(GLFWwindow* window);
	void hook(Simulation* simulation);
	void rotateCamera(double dTheta, double dPhi);
	void zoom(double dz);
private:
	Simulation* sim;
	void renderBox(GLFWwindow* window, Vec3D i_hat, Vec3D j_hat);
	
	void drawCircle(double x, double y, double r, hsv color, GLenum type);
	void drawLine(double x1, double y1, double x2, double y2, hsv color);
	
	Vec3D view_vector;
	Vec3D camera;

	double cameraTheta = M_PI/2;
	double cameraPhi = -M_PI/2;
	double cameraR = 1;
	
	double initial_screen_dist = 1;
	double projection_screen_dist = initial_screen_dist;

	Vec2D renderSpaceToScreenSpace(Vec3D pos, Vec3D i_hat, Vec3D j_hat);
	

};