#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;



// Print board
void printBoard(int board[3][3]) {
	cout << "\n";

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			
			char symbol = ' ';

			if (board[row][col] == 1)
				symbol = 'X';
			else if (board[row][col] == 2)
				symbol = 'O';
			cout << " " << symbol << " ";

			if (col < 2)
				cout << "|";
		}

		cout << "\n";

		if (row < 2) {
			cout << "---+---+---\n";
		}
	}

	cout << "\n";
}



// Player move
bool playerMove(int board[3][3]) {

	int row;
	int col;

	cout << "Enter your move: ";
	cin >> row >> col;

	if (row < 1 || row>3 || col < 1 || col>3) {
		cout << "\nEnter valid row and column.\n";
		return false;
	}

	row--;
	col--;

	if (board[row][col] == 0) {

		board[row][col] = 1; // Set spot to marked by the player
		return true;
	}
	else {
		cout << "\nInvalid move.\n";
		return false;
	}
}



// Enemy move
bool enemyMove(int board[3][3]) {

	cout << "Enemy move:\n";

	int chance = rand() % 100;

	if (chance < 70) {

		// Check rows
		for (int row = 0; row < 3; row++) {

			int playerMarks = 0;
			int emptyCol = -1;

			for (int col = 0; col < 3; col++) {
				if (board[row][col] == 1)
					playerMarks++;
				else if (board[row][col] == 0)
					emptyCol = col;
			}

			if (playerMarks == 2 && emptyCol != -1) {
				board[row][emptyCol] = 2;
				return true;
			}
		}

		// Check columns
		for (int col = 0; col < 3; col++) {

			int playerMarks = 0;
			int emptyRow = -1;

			for (int row = 0; row < 3; row++) {
				if (board[row][col] == 1)
					playerMarks++;
				else if (board[row][col] == 0)
					emptyRow = row;
			}

			if (playerMarks == 2 && emptyRow != -1) {
					board[emptyRow][col] = 2;
					return true;
			}
		}

		// Check diagonal 1

		int playerMarks = 0;
		int emptyIndex = -1;

		for (int i = 0; i < 3; i++) {
			if (board[i][i] == 1)
				playerMarks++;
			else if (board[i][i] == 0)
				emptyIndex = i;
		}
		
		if(playerMarks==2&&emptyIndex!=-1){
			board[emptyIndex][emptyIndex] = 2;
			return true;
		}

		// Check diagonal 2

		playerMarks = 0;
		emptyIndex = -1;

		for (int i = 0; i < 3; i++) {

			int col = 2-i;
			if (board[i][col] == 1)
				playerMarks++;
			else if (board[i][col] == 0)
				emptyIndex = i;
		}

		if (playerMarks == 2 && emptyIndex != -1) {
			board[emptyIndex][2 - emptyIndex] = 2;
			return true;
		}
	}

	// If no threat make a random move

	while (true) {
		int row = rand() % 3;
		int col = rand() % 3;

		if (board[row][col] == 0) {
			board[row][col] = 2;
			return true;
		}
	}
}



// Check Winner
int checkWinner(int board[3][3]) {

	// Check rows
	for (int row = 0; row < 3; row++) {
		if (board[row][0] != 0 &&
			board[row][0] == board[row][1] &&
			board[row][0] == board[row][2]) {

			return board[row][0];
		}
	}

	// Check columns
	for (int col = 0; col < 3; col++) {
		if (board[0][col] != 0 &&
			board[0][col] == board[1][col] &&
			board[0][col] == board[2][col]) {

			return board[0][col];
		}
	}

	// Check diagonal 1
	if (board[0][0] != 0 &&
		board[0][0] == board[1][1] &&
		board[0][0] == board[2][2]) {

		return board[0][0];
	}

	// Check diagonal 2
	if (board[0][2] != 0 &&
		board[0][2] == board[1][1] &&
		board[0][2] == board[2][0]) {

		return board[0][2];
	}

	return 0;
}



// Check for tie
bool checkTie(int board[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row][col] == 0)
				return false;
		}
	}
	return true;
}



// Game over screen
void gameOver(int winner, bool& isGameOver, int board[3][3], int& turn) {

	isGameOver = true;

	if (winner == 1)
		cout << "\nYou won the game!";
	else if (winner == 2)
		cout << "\nThe enemy won the game!";
	else if (winner == 3)
		cout << "\nThe game ends in a tie!";

	string input;

	cout << "\nPress enter to start a new game"; // Start a new game
	cin.ignore(1000, '\n');
	cin.get();

	// Reset game
	isGameOver = false;
	turn = 1;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			board[row][col] = 0;
		}
	}
	printBoard(board);
}



// Main
int main() {

	srand(time(0));

	bool isGameOver = false;
	int turn = 1;

	int board[3][3] = { 0 };

	cout << "Welcome to play TicTacToe!\n";
	cout << "Enter the row and column for your move (For example: 1 3)\n";

	printBoard(board);

	while (!isGameOver) {

		bool wasMoveSuccessful=false;

		if (turn == 1) {
			wasMoveSuccessful = playerMove(board); // Player move
		}
		else {
			wasMoveSuccessful = enemyMove(board); // Enemy move
		}

		if (wasMoveSuccessful == true) { // If move was successful print board
			printBoard(board);
		}

		int winner = checkWinner(board); // Check if theres a winner

		if (winner != 0) {
			gameOver(winner, isGameOver, board, turn);
			continue;
		}
		else if (checkTie(board) == true){
			gameOver(3, isGameOver, board, turn);
			continue;
		}

		if (wasMoveSuccessful == true) { // If move was successful change turn
			if (turn == 1)
				turn = 2;
			else
				turn = 1;
		}
	}
}