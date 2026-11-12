#include <iostream>
#include <thread>
#include "Screen.h"

void mainThread(Simulation* simulationPTR) {

	simulationPTR->mainLoop();

}

void renderThread(Screen* screenPTR) {

	screenPTR->mainLoop();

}

int main()
{

	printf("Input particle count:\n");
	int particle_count;
	scanf_s("%d", &particle_count);
	printf("Particles in left partition:\n");
	Simulation sim;
	sim.initialize(particle_count);

	Screen screen;
	screen.hook(&sim);
	screen.startWindow();


	std::thread mainthread(mainThread, &sim);
	//std::thread renderthread(renderThread, &screen);
	renderThread(&screen);

	//renderthread.join();
	mainthread.join();

}