#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>

int check_win(const int player, std::vector<char> &board, int &counter);
void create_board(const std::vector<char> board);
int drive_game(int &player);
int manage_turn(int &player, std::vector<char> &board);
bool manage_win(const int player, const int result);

int main()
{
	int player = 1;
	int result = 0;

	// The game will loop as long as the user wants to play
	do
	{
		player = 1;
		result = drive_game(player);
		
	} while (manage_win(player, result));

	getchar();
	return 0;
}


// pre:  a const int player to print the winner and a const int result to say what happened
// post: a boolean to decide whether or not the user wants to play again
bool manage_win(const int player, const int result)
{
	if (result == -1)
	{
		std::cout << "Sorry, there was no winner :( " << std::endl;
	}
	else if(result == 1)
	{
		std::cout << "Congrats Player " << player << ", you win!" << std::endl;
	}

	std::cout << "Would you like to play again? (Y/N)" << std::endl;
	std::string ans;
	std::cin >> ans;

	if (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES" || ans == "Yes")
	{
		return true;
	}
	else
	{
		std::cout << "Goodbye. Thanks for playing!" << std::endl;
	}

	return false;
}

// pre: this function takes in an int value (0 or 1)
// post: returns whether it is first player's ( identified as 0) or second player's (identified as 1) turn
int manage_turn(int &player, std::vector<char> &board)
{
	bool acceptable = false;
	int index = 0;

	char marker = 'X';
	if (player == 2)
	{
		marker = 'O';
	}

	std::cout << "Player " << player << ", Place an '" << marker << "'" << std::endl;
	do
	{
		int input;
		std::cin >> input; 
		index = input;
		if ((board[input] != 'X' && board[input] != 'O') && (input >= 0 && input <= 8))
		{
			acceptable = true;
			break;
		}

		std::cout << "That was not an acceptable input!" << std::endl;
		
	} while (!acceptable);
		
	board[index] = marker;
	player = (player % 2) + 1;
	return (player);
}

// pre: takes a vector board of chars and a const int to manage the player turn
// post: returns the outcome of the game (1-winner  0-in progress  -1-no winner)
int check_win(const int player, std::vector<char> &board, int &counter)
{
	std::cout << "WOAHH" << std::endl;
	if (board[0] == board[1] && board[1] == board[2]) // Top row 
	{
		return 1;
	}

	else if (board[3] == board[4] && board[3] == board[5]) // Mid row 
	{
		return 1;
	}

	else if (board[6] == board[7] && board[6] == board[8]) // Bot row 
	{
		return 1;
	}

	else if (board[0] == board[3] && board[0] == board[6]) // Left col 
	{
		return 1;
	}

	else if (board[1] == board[4] && board[1] == board[7]) // Mid col 
	{
		return 1;
	}

	else if (board[2] == board[5] && board[2] == board[8]) // Right col 
	{
		return 1;
	}

	else if (board[0] == board[4] && board[0] == board[8]) //    \ diag
	{
		return 1;
	}

	else if (board[2] == board[4] && board[2] == board[6]) //    /  diag
	{
		return 1;
	}

	else
	{
		if(++counter == 9)
		{
			return -1; // Game over -> no winner	
		}

		return 0; // Game in progress
	}
}

// pre: a vector to create the board
// post: none
void create_board(const std::vector<char> board)
{
	system("cls");
	std::cout << "TIC-TAC-TOE, winner is 3 in a row!" << std::endl;

	std::cout << "Player 1 (X)  -  Player 2 (O)\n\n" << std::endl;

	std::cout << "     |     |     " << std::endl;
	std::cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << std::endl;

	std::cout << "_____|_____|_____" << std::endl;
	std::cout << "     |     |     " << std::endl;

	std::cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << std::endl;

	std::cout << "_____|_____|_____" << std::endl;
	std::cout << "     |     |     " << std::endl;

	std::cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << std::endl;

	std::cout << "     |     |     " << std::endl << std::endl;
}

// This function drives the game for the most part
// pre: an int to manage the player turn
// post: an int to reveal the outcome of the game
int drive_game(int &player)
{
	
	std::vector<char> board = { '0','1','2','3','4','5','6','7','8' };
	int counter = 0;
	int result = 0;
	do
	{
		create_board(board);
		manage_turn(player, board);
		result = check_win(player, board, counter);
	} while (result==0);

	create_board(board);
	return result;
}