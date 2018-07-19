#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void assign_parts(int &counter, const std::string ans, const char guess, const std::vector<char> pieces, std::vector<char> &place, std::vector<char> &secret);
bool check_win(const std::string ans, std::vector<char> secret);
std::string cpu_word();
void draw_board(const std::vector<char> b, const std::vector<char> bank);
int drive_game(int resp);
void make_guess(const std::string ans, char &guess, std::vector<char>& secret);
std::string pick_word();
bool play_again();


/* ASCII HANGMAN
			O
		   \|/
		    |
			^
    ___    / \
*/

int main()
{
	do
	{
		std::cout << "			 _												";
		std::cout << "			| |												";
		std::cout << "			| |__     __ _ _ __   __ _ _ __ ___   __ _ _ __   \n";
		std::cout << "			| '_ \\  / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\  \n";
		std::cout << "			| | | |(_| | | | | (_| | | | | | | (_| | | | | \n";
		std::cout << "			|_| |_|\\__,__|_| |_|\\___,|_| |_| |_|\\__ _|_| |_| \n";
		std::cout << "				      	     __/ |						\n";
		std::cout << "				            |___ /						\n\n\n\n\n\n";
		std::cout << std::endl;
		std::cout << "				(1) Play with 2 players" << std::endl;
		std::cout << "				(2) Play against computer " << std::endl;
		std::cout << "				(3) Quit game " << std::endl;
		int resp;
		std::cin >> resp;
		switch (resp)
		{
			case 1:
				do
				{
					drive_game(resp);
				} while (play_again());
				break;

			case 2:
				do
				{
					drive_game(resp);
				} while (play_again());
				break;

			case 3:
				std::cout << "Goodbye" << std::endl;
				return 0;

			default:
				do
				{
					drive_game(resp);
				} while (play_again());
				break;
		}
	} while (1);


	getchar();
}

// pre: an int counter to lower if correct, a string answer and char guess to assign values to the placeholder vector, and two vectors which hold the pieces
// post: none
void assign_parts(int &counter, const std::string ans, const char guess, const std::vector<char> pieces, std::vector<char> &place, std::vector<char> &secret)
{

	bool correct = false;
	for (std::size_t i = 0; i < ans.length(); ++i)
	{
		if (ans[i] == guess)
		{
			secret[i] = guess;
			correct = true;
		}
	}

	if (!correct)
	{
		place[counter] = pieces[counter];
	}
	else
	{
		counter--;
	}
}

// pre: a string answer and a vector placeholder
// post: a boolean whether or not the answer == the placeholder
bool check_win(const std::string ans, std::vector<char> secret)
{
	for (std::size_t i = 0; i < secret.size(); i++)
	{
		if (ans[i] != secret[i])
		{
			return false;
		}
	}
	return true;
}

// Truthfully just a random word generator
// pre: none
// post: the string answer from the cpu dictionary
std::string cpu_word()
{
	std::ifstream input;
	std::string filename = "dictionary.txt";
	input.open(filename);
	if (input.fail())
	{
		std::cout << "Could not open dictionary file! " << std::endl;
		return " ";
	}

	std::vector<std::string> dict;
	std::string word;
	while (getline(input, word))
	{
		dict.push_back(word);
	}

	srand(time(NULL));
	int index = rand() % dict.size();

	return dict[index];

}

// pre: a vector to draw the board, and a vector letter bank
// post: none
void draw_board(const std::vector<char> b, const std::vector<char> bank)
{
	system("cls");
	std::cout << "HANGMAN! Guess the word to save the drawing!\n" << std::endl;
	std::cout << "			        T-------+ \n";
	std::cout << "				|       | \n";
	std::cout << "				|       + ";
	std::cout << "		LETTER BANK: [";
	for (auto e : bank)
	{
		std::cout << e << " ";
	}
	std::cout << "] \n";
	std::cout << "				|       " << b[0] << std::endl;
	std::cout << "		 O___           |      " << b[2] << b[1] << b[3] << std::endl;
	std::cout << "		/|		|       " << b[1] << std::endl;
	std::cout << "		 ^              |       " << b[4] << std::endl;
	std::cout << "		/ \\	        |      " << b[5] << " " << b[6] << std::endl;
	std::cout << "	+----------------------------------------------+ \n";
	std::cout << "        |      _         __             _              | \n";    
	std::cout << "	| |_| /_\\  |\\ | | _   /\\  /\\   /_\\  |\\ |       | \n";
	std::cout << "	| | |/   \\ | \\| |__| /  \\/  \\ /   \\ | \\|       | \n";
	std::cout << "	|                                              +--------+ \n";
	std::cout << "	|_________Make a single letter guess!___________________| \n\n";

}

// this function will drive most of the game
// pre: Whether or not we will play the cpu
// post: the outcome of the game (0 if win, 1 if loss <- from the guesser's standpoint)
int drive_game(int resp)
{
	std::vector<char> pieces = { 'O' , '|' , '\\' , '/', '^', '/', '\\' };
	std::vector<char> place = { ' ',' ',' ',' ',' ',' ',' '};
	std::vector<char> secret, bank;
	system("cls");

	std::string ans = " ";
	if(resp == 2)
		ans = cpu_word();
	else
	{
		ans = pick_word();
	}

	for (std::size_t i = 0; i < ans.length(); ++i)
	{
		secret.push_back('_');
	}

	bool correct = false;
	char guess = ' ';
	int counter = 0;
	do
	{
		draw_board(place, bank);
		make_guess(ans, guess, secret);
		bank.push_back(guess);
		assign_parts(counter, ans, guess, pieces, place, secret);
		++counter;
		if (check_win(ans, secret)) counter = 10; // 10 to break the loop and to return a win
	} while (counter < 7);
	
	draw_board(place, bank);
	if (counter == 10)
	{
		std::cout << "		Congrats! You win!\nYou correctly guessed: " << ans << std::endl;
		return 0;
	} 
	std::cout << "		Sorry, you lost... the word was: " << ans << std::endl;
	return 1;
}

// pre: a string answer, and a placeholder vector for the guesser
// post: a boolean whether or not the guess was correct
void make_guess(const std::string ans, char &guess, std::vector<char>& secret)
{
	std::cout << "Note: The word is " << ans.length() << " characters long." << std::endl;
	std::cout << "			";
	for (auto e : secret)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	bool acceptable = false;

	std::cin >> guess;
}

// pre: none
// post: a string that holds the answer
std::string pick_word()
{
	std::vector<std::string> cats = { "PEOPLE", "PLACES", "FOOD", "THINGS TO DO", "MOVIE", "TECHNOLOGY" };
	srand(time(NULL));
	int index = rand() % (cats.size());
	std::cout << "Enter a secret word: " << std::endl;
	std::cout << "If you'd like, please keep in mind the \"" << cats[index] << "\" category when choosing!" << std::endl;

	std::string secret = "";
	std::cin >> secret;
	return secret;
}

// pre: none
// post: a bool if they would like to play again
bool play_again()
{
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
