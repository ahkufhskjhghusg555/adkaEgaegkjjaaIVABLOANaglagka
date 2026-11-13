#include "MathUtils.h"

class Simulation
{

public:
	int initialize(int p_count);
	void mainLoop();
	void end();
	void togglePause();
	int getParticleCount();
	Vec3D getWorldSize();
	void screenshot();

	Particle* particles;

private:
	bool ended = false;

	const double box_width = 2.0, box_height = 1.5, box_depth = 3.0;
	int particle_count = 10;
	const double dt = 0.02;
	
	bool paused = true;
	void handleBoundaries(Particle* p);
	void advanceTime();


};