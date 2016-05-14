#include <iostream>

#include "Cutie.hpp"


//#include "Main.hpp"




int main(int argc, char *argv[])
{
	cutie::connect();

	if(connect(address, timeout)) {

		bool gameStarted = gameInit(0,0);
		bool gameActive = true;

		if (gameStarted) {
			int myScore = 0;
			int theirScore = 0;
			int myTurn = 1;
			int theirTurn = 1;

			while (gameActive) {

			theirTurn = doTurn(myTurn);

			if (myTurn == theirTurn) {
				std::cout << "Draw" << std::endl;
			}

			if (myTurn > theirTurn) {


			}

			}



		}


	}


    return 0;
}


