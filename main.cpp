#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include "Utility.h"
#include "AI.h"
#include "Game.h"
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


int main() {	
	// Getting AI Mode
	int isAIMode = 0;
	string AIMode;
	cout << "AI mode? (y/n): ";
	getline(cin, AIMode);
	if (AIMode == "y") {
		isAIMode = 1;
	}
	else if (AIMode == "n") {
		isAIMode = 0;
	}

	if (isAIMode == 0) {
		Game manualGame;
		while (!manualGame.getIsLost()) {
			manualGame.gameTick(0, 0, ' ');
		}
		return 0;
	}

	ofstream outf;
	outf.open("generations.txt");

	AI ai;
	char possMoves[POSSIBLE_MOVE_COUNT][MAX_MOVE_LENGTH] = {' '};
	ai.assignPossibleMoveCombos(possMoves);
	int possMovesLens[POSSIBLE_MOVE_COUNT] = {0};
	ai.assignPossibleMoveCombosLens(possMovesLens);
	// Runs 1000 generations
	for (int i = 0; i < 10001; i++) {
		cout << endl << "Generation " << i << endl;
		// For each individual in the generation
		for (int j = 0; j < GENERATION_POPULATION; j++) {
			//string junk;
			//getline(cin, junk);
			Game game;
			// Each individual will make 1000 moves
			double movesMadeCount = 0;
			for (int k = 0; k < 100000; k++) {
				//if (i != 0) {
					string junk;
					getline(cin, junk);
				//}
				// Only play if the game isn't lost
				if (!game.getIsLost()) {
					movesMadeCount++;
					int bestMoveCombo = ai.findBestMove(game, j);
					game.setMoveEnded(false);
					// make the move in the real game; bestMoveCombo is the index of 
					// the best list in possMoves
					for (int l = 0; l < possMovesLens[bestMoveCombo]; l++) {
						if (game.getMoveValid() && !game.getMoveEnded()) {
							game.gameTick(1, 1, possMoves[bestMoveCombo][l]);
						}
					}
					while (!game.getMoveEnded()) {
						game.gameTick(1, 1, ' ');
					}
				}
				else {
					break;
				}
				//if (i != 0) {
					game.printBoard();
				//}
			}
			cout << game.getUserScore() << endl;
			if (!game.getIsLost()) {
				cout << "Win!" << endl;
			}
			//game.printBoard();
			if (game.getUserScore() > 0) {
				if (!game.getIsLost()) {
					ai.setScoreVal(game.getUserScore(), j);
				}
				else if (game.getIsLost()) {
					ai.setScoreVal(game.getUserScore() / 2, j);
				}
			}
			else {
				ai.setScoreVal(movesMadeCount * 0.1, j);
			}
		}

		// Saving the generation
		if ((i < 100 && (i % 10) == 0) || ((i % 50) == 0)) {
			int genWinners[GENERATION_POPULATION] = { 0 };
			ai.findWinners(genWinners);
			ai.saveGen(outf, i, genWinners);
		}


		ai.createNewGen();
		ai.resetScores();
	}

	outf.close();
	return 0;
}