/*
 * "Main.cpp"
 *
 * libcutie - Validate your opponent's data to detect cheating.
 * Copyright (c) 2016 Ammon Smith, Auggie Balquin, Bradley Cai
 * 
 * libcutie is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * libcutie is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with libcutie.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>


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



	bool checkInput(cutie::data * data) {
		char* check = data->data;
		if (check[0] == ROCK || check[0] == PAPER || check[0] == SCISSORS) {
			return true;
		}
		return false;
	}
};

// void getPlayerTurn(enum Move & temp);
// void outputScore(int myScore, int theirScore);
// void updateScore(bool winner, int & myScore, int & theirScore);

// 


int main(int argc, char *argv[])
{
	SessionType type;
	std::string ipAddress;
	int port;
	
	do {
		type = choice();
		if (type == JOIN) {
			std::cout << "What is the address you want to connect to? \n\n";
			std::cin >> ipAddress;
			std::cout << "On what port? \n\n";
			std::cin >> port;
			std::cout<< "Looking for opponent...\n";
			
			if (cutie::joinSession(ipAddress.c_str(), port)) {
				std::cout << "Opponent found!\n";
			}
			else {
				perror("Join failed: ");
				type = INVALID;
			}
		}
		else if (type == CREATE) {
			std::cout << "Waiting for opponent to connect...\n";
			
			if (cutie::createSession(port)) {
				std::cout << "Opponent found!\n";
			}
			else {
				perror("Create failed: ");
				type = INVALID;
			}
		}
	} 
	while (type != INVALID);
	
	//cutie::connect();

	//if(cutie::connect(address, timeout)) {
		//sets reject input
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

				bool forgery = false;
				Opponent = *(cutie::doTurn(&Player, checkInput, forgery));
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
		
	cutie::endSession();
    return 0;
}
