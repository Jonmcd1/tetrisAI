#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Utility.h"
using namespace std;

class Piece {
private:
	int currentPiece = -1;
	int currentRotation = 0;

	// (0, 0) is top-left
	int currentVertical = -1;
	int currentHorizontal = -1;
	
	// The 4 tiles occupied in {vertical, horizontal} form
	int occupiedSpaces[PIECE_SIZE][2] = {0};

public:
	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Constructor for Piece; Piece values get set by newPiece
	 */
	Piece();


	/**
	 * Requires: randomNum is >= 0 and < 6
	 * Modifies: all private data members
	 * Effects:  Sets the piece's position/type/tiles based on what type is selected
	 */
	void newPiece(int randomNum);


	/**
	 * Requires: Nothing
	 * Modifies: occupiedSpaces
	 * Effects:  Shifts the piece 1 tile to the left
	 */
	void moveLeft();


	/**
	 * Requires: Nothing
	 * Modifies: occupiedSpaces
	 * Effects:  Shifts the piece 1 tile to the right
	 */
	void moveRight();


	/**
	 * Requires: Nothing
	 * Modifies: occupiedSpaces
	 * Effects:  Shifts the piece 1 tile down
	 */
	void moveDown();


	/**
	 * Requires: Nothing
	 * Modifies: occupiedSpaces
	 * Effects:  Rotates(tilts) the piece 90 degrees around currentVertical/currentHorizontal
	 */
	void rotate();

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns the character representing the piece
	 */
	char getPieceChar();

	/**
	 * Requires: 0 <= i <= 3
	 * Modifies: Nothing
	 * Effects:  Returns an occupiedSpace Y coord
	 */
	int getOccupiedSpaceY(int i);
	
	/**
	 * Requires: 0 <= i <= 3
	 * Modifies: Nothing
	 * Effects:  Returns an occupiedSpace X coord
	 */
	int getOccupiedSpaceX(int i);

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns currentVertical
	 */
	int getCurrentVertical();

	/**
	 * Requires: Nothing
	 * Modifies: Nothing
	 * Effects:  Returns currentHorizontal
	 */
	int getCurrentHorizontal();
};


#endif