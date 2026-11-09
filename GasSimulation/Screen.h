#include "SimulationRenderer.h"

class Screen
{

public:
	void startWindow();
	void hook(Simulation* simulationPTR);
	void mainLoop();
	GLFWwindow* window;
private:
	Simulation* simulationPTR;
	
	SimulationRenderer simRenderer;

};