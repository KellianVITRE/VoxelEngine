#include <iostream>
#include "Game.h"

#define TPS_CAP 60

int main() {

	Game game(800, 600, "MobaGame");

	int ticks = 0, frames = 0;

	double dt;
	double lt = 0.0;

	while (game.open()) {
		double nt = glfwGetTime();
		dt = nt - lt;

		if ( dt >= 1.0/TPS_CAP) {
			game.Update(nt);
			ticks++;
			dt--;
			lt = nt;
		}
		
		game.Render(nt);
		frames++;

		//std::cout << "Average FPS: " << frames / nt << " ||| " << "Average TPS: " << ticks / nt << std::endl;
	}

	glfwTerminate();

	return 0;
}