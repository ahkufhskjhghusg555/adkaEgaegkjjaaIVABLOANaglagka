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

	Simulation sim;
	sim.initialize();

	Screen screen;
	screen.hook(&sim);
	screen.startWindow();


	std::thread mainthread(mainThread, &sim);
	//std::thread renderthread(renderThread, &screen);
	renderThread(&screen);

	//renderthread.join();
	mainthread.join();

}