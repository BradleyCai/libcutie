#include <iostream>

#include "Cutie.hpp"


//#include "Main.hpp"


enum Move {ROCK, PAPER, SCISSORS};



void getPlayerTurn(enum Move * temp) {
	std::cout << "Please enter your move!"
}

int main(int argc, char *argv[])
{
	cutie::connect();

	if(connect(address, timeout)) {

		bool gameStarted = gameInit(0,0);
		bool gameActive = true;

		if (gameStarted) {
			int myScore = 0;
			int theirScore = 0;
			Move myTurn = 1;
			Move theirTurn = 1;

			while (gameActive) {

				getPlayerTurn();

				theirTurn = doTurn(myTurn);

				if (myTurn == theirTurn) {

					std::cout << "Draw Placeholder" << std::endl;
				}

				if (myTurn == ROCK) {

				}

			}


		}
	}
    return 0;
}


