#include <iostream>
#include <string>

#include "Cutie.hpp"


//#include "Main.hpp"


enum Move {
	ROCK,
	PAPER,
	SCISSORS
};
	
enum SessionType {
	JOIN,
	CREATE
};

// void getPlayerTurn(enum Move & temp);
// void outputScore(int myScore, int theirScore);
// void updateScore(bool winner, int & myScore, int & theirScore);

// 
int choice() 
{
	int res = 0;
	
	std::cout << "Would you like to create a game or join a game?" << endl;
	std::cout << "1: Join\n2:Create\n> ";
	std::cin >> res;
	
	cin >> res;
	
	cin.clear();
	cin.ignore(256, '\n');
	switch (res) {
		case 1: 
			return JOIN;
		case 2:
			return CREATE;
		default:
			return -1;
	}
}

void getPlayerTurn(Move& temp)
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

bool compareTurn(Move myTurn, Move theirTurn){
	bool winner = false;
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
	return winner;
}

void outputEndgame(bool winner) {

	if (winner) {

	}
}

 
int main(int argc, char *argv[])
{
	SessionType type = choice();
	
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

				//Outputs Score
				outputScore(myScore, theirScore);
				//Prompts User for turn
				getPlayerTurn(myTurn);

				//theirTurn =  cutie::doTurn(myTurn);
				winner =  compareTurn(myTurn,theirTurn);
		
				updateScore(winner, myScore, theirScore);

				if (myScore == 5 || theirScore == 5) {
					gameActive = false;
					if (myScore == 5) {
						winner = true;
					}
					else {
						winner = false;
					}
				}

			}

			outputEndgame(winner, myScore);

		}
	//}
    return 0;
}


