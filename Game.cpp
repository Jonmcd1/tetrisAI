#include <string>
#include <iostream>
#include "Game.h"

using namespace std;

/***** MAJOR GAME FUNCTIONS ******/
Game::Game() {
	generateRandomPiece();
	heldPiece.newPiece((rand()) % 6);
	putPieceOnBoard();
	//printBoard();
}


void Game::gameTick(int isAI, int isHyp, char AIMove) {
	userMove(isAI, AIMove);
	if (isHyp == 0) {
		if (lost) {
			cout << endl << "Game Over!" << endl << endl;
		}
		else {
			printBoard();
		}
	}

	return;
}


/****** MOVING THE PIECE ******/
void Game::userMove(int isAI, char AIMove) {
	//cout << "Enter move(l, r, d, t, s, or empty): ";
	string move;
	if (isAI == 0) {
		getline(cin, move);
	}
	else {
		move = AIMove;
		//cout << AIMove << endl;
	}
	
	takePieceOffBoard();
	// Program response to user move
	// FIXME
	moveEnded = false;
	if (move == "l") {
		if (checkSideCollision(-1)) {
			//cout << "Invalid move!" << endl;
			moveValid = false;
		}
		else {
			currPiece.moveLeft();
			moveValid = true;
		}
	}
	else if (move == "r") {
		if (checkSideCollision(1)) {
			//cout << "Invalid move!" << endl;
			moveValid = false;
		}
		else {
			currPiece.moveRight();
			moveValid = true;
		}
	}
	else if (move == "d") {
		if (checkBottomCollision()) {
			movingDone();
			// FIXME
			moveEnded = true;
			return;
		}
		else {
			currPiece.moveDown();
		}
	}
	else if (move == "t") {
		if (checkRotateCollision()) {
			//cout << "Invalid move!" << endl;
			moveValid = false;
		}
		else {
			currPiece.rotate();
			moveValid = true;
		}
	}
	else if (move == "s" && currPiece.getCurrentVertical() == 1) {
		Piece temp = currPiece;
		currPiece = heldPiece;
		heldPiece = temp;
	}
	
	// Passive down move that happens every tick
	if (move != "s") {
		if (!checkBottomCollision()) {
			currPiece.moveDown();
		}
		else {
			movingDone();
			// FIXME
			moveEnded = true;
			return;
		}
	}
	putPieceOnBoard();
	rowsJustCleared = 0;
	return;
}


void Game::takePieceOffBoard() {
	for (int i = 0; i < PIECE_SIZE; i++) {
		int currTileX = currPiece.getOccupiedSpaceX(i);
		int currTileY = currPiece.getOccupiedSpaceY(i);
		gameBoard[currTileY][currTileX] = 0;
	}

	return;
}


void Game::putPieceOnBoard() {
	for (int i = 0; i < PIECE_SIZE; i++) {
		int currTileX = currPiece.getOccupiedSpaceX(i);
		int currTileY = currPiece.getOccupiedSpaceY(i);
		gameBoard[currTileY][currTileX] = 1;
	}

	return;
}


/****** COLLISION CHECKS ******/
bool Game::checkBottomCollision() {
	for (int i = 0; i < PIECE_SIZE; i++) {
		int downTileX = currPiece.getOccupiedSpaceX(i);
		int downTileY = currPiece.getOccupiedSpaceY(i) + 1;

		// Checking if the piece's tile would go off the board
		if (downTileY >= BOARD_HEIGHT) {
			return true;
		}
		// Checking if the piece's tile would move to an occupied tile
		if (gameBoard[downTileY][downTileX] != 0) {
			return true;
		}
	}

	// No collision if nothing's detected
	return false;
}


bool Game::checkSideCollision(int move) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		int sideTileX = currPiece.getOccupiedSpaceX(i) + move;
		int sideTileY = currPiece.getOccupiedSpaceY(i);

		// Checking if the piece's tile would go off the board
		if (sideTileX >= BOARD_WIDTH || sideTileX < 0) {
			return true;
		}
		// Checking if the piece's tile would move to an occupied tile
		if (gameBoard[sideTileY][sideTileX] != 0) {
			return true;
		}
	}

	// No collision if nothing's detected
	return false;
}

bool Game::checkRotateCollision() {
	int pieceCurrVert = currPiece.getCurrentVertical();
	int pieceCurrHoriz = currPiece.getCurrentHorizontal();
	for (int i = 0; i < PIECE_SIZE; i++) {
		// Rotating the tile clockwise 90 degrees about the piece's current Horiz/Vert
		int rotateTileX = pieceCurrHoriz + pieceCurrVert - currPiece.getOccupiedSpaceY(i);
		int rotateTileY = pieceCurrVert + currPiece.getOccupiedSpaceX(i) - pieceCurrHoriz;

		// Checking if the piece's tile would go off the board
		if (rotateTileX >= BOARD_WIDTH || rotateTileX < 0 || rotateTileY >= BOARD_HEIGHT) {
			return true;
		}
		// Checking if the piece's tile would move to an occupied tile
		if (gameBoard[rotateTileY][rotateTileX] != 0) {
			return true;
		}
	}

	// No collision if nothing's detected
	return false;
}


/****** NEW PIECE ******/
void Game::movingDone() {
	putPieceOnBoard();
	clearFinishedRows();
	generateRandomPiece();

	return;
}


void Game::generateRandomPiece() {
	currPiece.newPiece((rand() / 4) % 6);
	checkLoss();

	return;
}


/****** BOARD UTILITIES ******/
void Game::printBoard() {
	cout << endl;
	cout << "Held Piece: " << heldPiece.getPieceChar();

	cout << endl;
	for (int i = 0; i < BOARD_WIDTH + 2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < BOARD_HEIGHT; i++) {

		cout << "#";
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (gameBoard[i][j] == 0) {
				cout << "-";
			}
			else {
				cout << "@";
			}
		}
		cout << "#" << endl;
	}

	for (int i = 0; i < BOARD_WIDTH + 2; i++) {
		cout << "#";
	}
	cout << endl << "Score: " << userScore << endl;

	return;
}


void Game::clearFinishedRows() {
	// Finding the finished rows, if any
	int finishedRows[BOARD_HEIGHT] = {0};
	int finishedRowCount = 0;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		bool rowIsFinished = true;
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (gameBoard[i][j] == 0) {
				rowIsFinished = false;
			}
		}
		if (rowIsFinished == true) {
			finishedRows[finishedRowCount] = i;
			finishedRowCount++;
		}
	}

	// For each row
	for (int i = (BOARD_HEIGHT - 1); i >= 0; i--) {
		// Finding how many completed rows are below the current row
		int completedRowsBelow = 0;
		for (int j = 0; j < finishedRowCount; j++) {
			if (i < finishedRows[j]) {
				completedRowsBelow++;
			}
		}

		// Shifting the row down if necessary
		if (completedRowsBelow != 0) {
			for (int j = 0; j < BOARD_WIDTH; j++) {
				gameBoard[i + completedRowsBelow][j] = gameBoard[i][j];
				gameBoard[i][j] = 0;
			}
		}

	}

	// Add to the score
	addScore(finishedRowCount);
	rowsJustCleared = finishedRowCount;

	return;
}


void Game::checkLoss() {
	for (int i = 0; i < PIECE_SIZE; i++) {
		int tileX = currPiece.getOccupiedSpaceX(i);
		int tileY = currPiece.getOccupiedSpaceY(i);

		// Checking if the piece's tile is on an occupied tile
		if (gameBoard[tileY][tileX] != 0) {
			lost = true;
		}
	}
	putPieceOnBoard();
	return;
}


void Game::clear() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			gameBoard[i][j] = 0;
		}
	}
	return;
}


/****** SCORE ******/
void Game::addScore(int rowsCleared) {
	userScore += 100 * rowsCleared * rowsCleared;
}


/****** SETTERS ******/
void Game::setGame(Game game) {
	setPiece(game.getPiece());

	setHeldPiece(game.getHeldPiece());

	int gameBoardTemp[BOARD_HEIGHT][BOARD_WIDTH];
	game.assignGameBoard(gameBoardTemp);
	setGameBoard(gameBoardTemp);

	setUserScore(game.getUserScore());

	setIsLost(game.getIsLost());

	setRowsJustCleared(game.getRowsJustCleared());

	setMoveEnded(game.getMoveEnded());

	setMoveValid(game.getMoveValid());
	return;
}

void Game::setPiece(Piece piece) {
	currPiece = piece;
	return;
}

void Game::setHeldPiece(Piece piece) {
	heldPiece = piece;
	return;
}

void Game::setGameBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			gameBoard[i][j] = board[i][j];
		}
	}
	return;
}

void Game::setUserScore(int score) {
	userScore = score;
	return;
}

void Game::setIsLost(bool lossVal) {
	lost = lossVal;
	return;
}

void Game::setRowsJustCleared(int rowCount) {
	rowsJustCleared = rowCount;
	return;
}

void Game::setMoveEnded(bool ended) {
	moveEnded = ended;
	return;
}

void Game::setMoveValid(bool valid) {
	moveValid = valid;
	return;
}


/****** GETTERS ******/
Piece Game::getPiece() {
	return currPiece;
}

Piece Game::getHeldPiece() {
	return heldPiece;
}

void Game::assignGameBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			board[i][j] = gameBoard[i][j];
		}
	}
	return;
}

int Game::getUserScore() {
	return userScore;
}

bool Game::getIsLost() {
	return lost;
}

int Game::getRowsJustCleared() {
	return rowsJustCleared;
}

bool Game::getMoveEnded() {
	return moveEnded;
}

bool Game::getMoveValid() {
	return moveValid;
}