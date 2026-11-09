#include "Simulation.h"

class SimulationRenderer
{

public:
	void render(GLFWwindow* window);
	void hook(Simulation* simulation);
private:
	Simulation* sim;
	double conversion = 1.0; //conversion factor from meters to pixels; units is pixels/meter
	void drawCircle(double x, double y, double r, hsv color, GLenum type);
	void drawLine(double x1, double y1, double x2, double y2, hsv color);
};