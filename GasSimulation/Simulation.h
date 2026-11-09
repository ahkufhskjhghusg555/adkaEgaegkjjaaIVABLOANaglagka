#include "MathUtils.h"

class Simulation
{

public:
	int initialize();
	void mainLoop();
	void end();
	void togglePause();
	int getParticleCount();
	Vec2D getWorldSize();
	void screenshot();

	Particle* particles;

private:
	bool ended = false;

	const double box_width = 2.0, box_height = 1.5;
	const int particle_count = 10;
	const double dt = 0.02;
	
	bool paused = true;
	void handleBoundaries(Particle* p);
	void advanceTime();


};