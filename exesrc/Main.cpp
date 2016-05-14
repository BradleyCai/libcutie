#include <iostream>
#include <string>

#include "Cutie.hpp"


//#include "Main.hpp"


enum Move {ROCK, PAPER, SCISSORS};


// void getPlayerTurn(enum Move & temp);
// void outputScore(int myScore, int theirScore);
// void updateScore(bool winner, int & myScore, int & theirScore);



void getPlayerTurn(Move & temp)
{
	int choice = 1;
	std::cout << "Please enter your move!" << std::endl;
	std::cout << "1: ROCK" << std::endl;
	std::cout << "2: PAPER" << std::endl;
	std::cout << "3: SCISSORS!" << std::endl;
	std::cin >> choice;

	if (choice == 1) {
		temp = ROCK;
	}
	else if (choice == 2) {
		temp =  PAPER;
	}
	else {
		temp = SCISSORS;
	}
}

void outputScore(int myScore, int theirScore)
{
	std::cout << "YOU: " << myScore << std::endl;
	std::cout << "OPPONENT: " << theirScore << std:: endl;
}

void updateScore(bool winner, int & myScore, int & theirScore) 
{
	if (winner) {
		myScore++;
		return;
	}
	theirScore++;
	return;
} 
// bool compareTurn(Move player){

// }

int main(int argc, char *argv[])
{
	//cutie::connect();

	//if(cutie::connect(address, timeout)) {

		bool gameStarted = true;//gameInit(0,0);
		bool gameActive = true;

		if (gameStarted) {
			int myScore = 0;
			int theirScore = 0;
			bool winner = false;
			Move myTurn = ROCK;
			Move theirTurn = ROCK;


			while (gameActive) {

				outputScore(myScore, theirScore);
				getPlayerTurn(myTurn);

				//theirTurn =  cutie::doTurn(myTurn);

				if (myTurn == theirTurn) {
					winner = false;				
				}
				else if (myTurn == ROCK) {
					winner = (theirTurn == SCISSORS)? true : false;
				}
				else if (myTurn == PAPER) {
					winner = (theirTurn == ROCK)? true : false;
				}
				else {
					winner = (theirTurn == PAPER)? true : false;
				}

				updateScore(winner, myScore, theirScore);

			}


		}
	//}
    return 0;
}


