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
	CREATE,
	INVALID
};

namespace {
	SessionType choice() 
	{
		int res = 0;
		
		std::cout << "Would you like to create a game or join a game?\n";
		std::cout << "1: Join\n2:Create\n\n ";
		std::cin >> res;
		
		std::cin >> res;
		
		std::cin.clear();
		std::cin.ignore(256, '\n');
		switch (res) {
			case 1: 
				return JOIN;
			case 2:
				return CREATE;
			default:
				return INVALID;
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

	bool compareTurn(Move myTurn, Move theirTurn)
	{
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

	void outputEndgame(bool winner)
	{

		if (winner) {
			std::cout << "Victory!" << std::endl;
			std::cout << "YOU WON" << std::endl;
		}
		else {
			std::cout << "Defeat!" << std::endl;
			std::cout << "YOU LOST" << std::endl;
		}
	}

	// char* turnConvert(Move turn) {
	// 	if (turn == ROCK) {
	// 		return new char(1);
	// 	}
	// 	else if (turn == PAPER) {
	// 		return new char(2);
	// 	}
	// 	else {
	// 		return new char(3);
	// 	}
	// }

	bool checkInput(char* data) {
		
	}
};

// void getPlayerTurn(enum Move & temp);
// void outputScore(int myScore, int theirScore);
// void updateScore(bool winner, int & myScore, int & theirScore);

// 


int main(int argc, char *argv[])
{
	SessionType type = choice();
	std::string ipaddress;
	int port;
	
	while (type != INVALID) {
		if (type == JOIN) {
			std::cout << "What is the address you want to connect to? \n\n";
			std::cin >> ipaddress;
			std::cout << "On what port? \n\n";
			std::cin >> port;
		}
		else if (type == CREATE) {
			// 
		}
		else {
			
		}
	}
	
	//cutie::connect();

	//if(cutie::connect(address, timeout)) {
		//ask user for reject input
		cutie::setRejectTimes(5);
		bool gameStarted = true;//gameInit(0,0);
		bool gameActive = true;

		if (gameStarted) {
			int myScore = 0;
			int theirScore = 0;
			bool winner = false;
			Move myTurn = ROCK;
			Move theirTurn = ROCK;

			cutie::data Opponent;
			cutie::data Player;
			Opponent.length = 1;
			Player.length = 1;

			while (gameActive) {

				//Outputs Score
				outputScore(myScore, theirScore);
				//Prompts User for turn
				getPlayerTurn(myTurn);
				Player.data = new char(static_cast<int>(myTurn));

				Opponent = cutie::doTurn(Player, );
				theirTurn = static_cast<Move>(*(Opponent.data));

				winner = compareTurn(myTurn,theirTurn);
		
				updateScore(winner, myScore, theirScore);


				//Endgame check  Set final winner
				if (myScore >= 5 || theirScore >= 5) {
					gameActive = false;
					if (myScore == 5) {
						winner = true;
					}
					else {
						winner = false;
					}
				}

			}

			outputEndgame(winner);

		}
	//}
    return 0;
}


