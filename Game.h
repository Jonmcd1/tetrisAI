#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Utility.h"
#include "Piece.h"
using namespace std;

// FIXME: Add piece storing mechanic
class Game {
private:
	int gameBoard[BOARD_HEIGHT][BOARD_WIDTH] = {0};
	Piece currPiece;
	Piece heldPiece;
	int userScore = 0;
	bool lost = false;

	int rowsJustCleared = 0;
	bool moveEnded = false;
	bool moveValid = true;

public:
	/***** MAJOR GAME FUNCTIONS ******/
	/**
	 * Requires: Nothing
	 * Modifies: gameBoard
	 * Effects:  Starts Game with a piece on the boards
	 */
	Game();


	/**
	 * Requires: Nothing
	 * Modifies: Piece, gameBoard
	 * Effects:  Calls userMove and movePieceDown
	 */
	void gameTick(int isAI, int isHyp, char AIMove = ' ');



	/****** MOVING THE PIECE ******/
	/**
	 * Requires: user inputs either "l"(left), "r"(right), "d"(down), or "t"(tilt/rotate)
	 * Modifies: cin, gameBoard, Piece
	 * Effects:  moves the piece in the way specified by the user;
	 *			 calls collision checks
	 */
	void userMove(int isAI, char AIMove);


	/**
	 * Requires: Nothing
	 * Modifies: gameBoard
	 * Effects:  Removes the places on the gameBoard that match the coords of currPiece
	 */
	void takePieceOffBoard();

	/**
	 * Requires: Nothing
	 * Modifies: gameBoard
	 * Effects:  Fills the places on the gameBoard that match the coords of currPiece
	 */
	void putPieceOnBoard();



	/****** COLLISION CHECKS ******/
	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns true if there is a bottom collision on a down move, else false
	 */
	bool checkBottomCollision();


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns true if there is a side collision on an l/r move, else false
	 */
	bool checkSideCollision(int move);


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns true if there is a collision on a t move, else false
	 */
	bool checkRotateCollision();



	/****** NEW PIECE ******/
	/**
	 * Requires: Nothing
	 * Modifies: Piece, gameBoard
	 * Effects:  Is run when there's a bottom collision; finishes the currPiece's
	 *			 movement and prompts a new piece for generation
	 */
	void movingDone();


	/**
	 * Requires: Nothing
	 * Modifies: Piece
	 * Effects:  Is called when it's time to create a new piece; makes a random one
	 */
	void generateRandomPiece();



	/****** BOARD UTILITIES ******/
	/**
	 * Requires: Nothing
	 * Modifies: cout
	 * Effects:  Prints the board to the terminal
	 */
	void printBoard();


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Clears rows that have been completed when a piece is done moving
	 */
	void clearFinishedRows();


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Ends the game if the spawned piece collides with anythings
	 */
	void checkLoss();

	/**
	 * Requires: Nothing
	 * Modifies: gameBoard
	 * Effects:  Empties the board
	 */
	void clear();



	/****** SCORE ******/
	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Adds points to the score if necessary
	 */
	void addScore(int rowsCleared);


	/****** SETTERS ******/
	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets Game to game
	 */
	void setGame(Game game);
	
	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets currPiece to piece
	 */
	void setPiece(Piece piece);

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets heldPiece to piece
	 */
	void setHeldPiece(Piece piece);

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Assigns gameBoard's values to an array's
	 */
	void setGameBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]);

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets userScore to score
	 */
	void setUserScore(int score);

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets lost to lossVal
	 */
	void setIsLost(bool lossVal);


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets rowsJustCleared to rowCount
	 */
	void setRowsJustCleared(int rowCount);


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets moveEnded to ended
	 */
	void setMoveEnded(bool ended);

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  sets moveValid to valid
	 */
	void setMoveValid(bool valid);



	/****** GETTERS ******/
	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns currPiece
	 */
	Piece getPiece();


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns heldPiece
	 */
	Piece getHeldPiece();


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Assigns an array with gameBoard's values
	 */
	void assignGameBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]);

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns userScore
	 */
	int getUserScore();

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns lost
	 */
	bool getIsLost();


	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns rowsJustCleared
	 */
	int getRowsJustCleared();

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns moveEnded
	 */
	bool getMoveEnded();

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns moveValid
	 */
	bool getMoveValid();
};


#endif