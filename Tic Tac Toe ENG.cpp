#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

// Representing a game state
struct node
{
	char board[3][3];
	char player1;
	char ai;
};

// Create the board game mechanic
void inboard (char board[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)	
		board[i][j] = '.';
}

// Display board game mechanic
void print(char board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		cout << endl;
		for (int j = 0; j < 3; j++)
		{
			cout << " ";
			cout << board[i][j];
		}
	}
	cout << endl << endl;
}

// Ongoing game mechanic
char check(char board[3][3])
{
		if (board[0][0] != '.' && (board[0][0] == board[0][1] && board[0][0] == board[0][2] ||
		board[0][0] == board[1][0] && board[0][0] == board[2][0] ||
		board[0][0] == board[1][1] && board[0][0] == board[2][2]))
		return board[0][0];

	
	if (board[1][1] != '.' && (board[1][1] == board[1][0] && board[1][1] == board[1][2] ||
		board[1][1] == board[0][1] && board[1][1] == board[2][1] ||
		board[1][1] == board[2][0] && board[1][1] == board[0][2]))
		return board[1][1];

	
	if (board[2][2] != '.' && (board[2][2] == board[0][2] && board[2][2] == board[1][2] ||
		board[2][2] == board[2][0] && board[2][2] == board[2][1]))
		return board[2][2];
	return 0;
}

int score(char board[3][3], char player1, char player2)
{
	int bestmove = -9999;
	int movescore = 0;
	if(check(board) == player1)
		return 1000;
	else if (check(board) == player2)
		return 1000;
	for(int r = 0; r < 3; r++)
		for(int c = 0; c < 3; c++)
		if(board[r][c] == '.')
		{
			board[r][c] = player1;
			movescore = -(score(board, player2, player1));
			board[r][c] = '.';
			if(movescore >= bestmove)
				bestmove = movescore;
		}
	if(bestmove == -9999 || bestmove == 0)
		return 0;
	else if(bestmove < 0)
		return ++bestmove;
	else if(bestmove > 0)
		return --bestmove;
}

// Display score and next steps AI
int pickmove(char board[3][3], char player1, char player2)
{
	int bestmove = -9999;
	int bestrow = -9999;
	int bestcol = -9999;
	int movescore = 0;
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			if (board[r][c] == '.')
			{
				board[r][c] = player1;
				movescore = -(score(board, player2, player1));
				board[r][c] = '.';
				if (movescore >= bestmove)
				{
					bestmove = movescore;
					bestrow = r;
					bestcol = c;
				}
			}
	return (10 * bestrow + bestcol);
}

//Display player commands
void placement(char board[3][3], char player)
{
	while(1)
	{
		string r, c;
		int row = 0, col = 0;
		while (1)
		{
			cout << "Choice the row: ";
			cin >> r;
			row = atoi(r.c_str());
			if (row >= 1 && row <= 3)
				break;
			cout << "Error. This Command Not Exist. Choice numers between 1 and 3.\n";		
		}
		while(1)
		{
			cout << "Choice the column: ";
			cin >> c;
			col = atoi(c.c_str());
			if ( col >= 1 && row <= 3)
				break;
			cout << "Error. This Command Not Exist. Choice numers between 1 and 3.\n";
		}
		if (board[row-1][col-1] == '.')
		{
			board[row-1][col-1] = player;
			break;
		}
		else
		cout << "Location already occupied. Try again\n\n";
	}
}

// Inictiation CPU markers
char aichoice (char player1)
{
	char ai;
	cout << "New Game\n";
	if (player1 == 'x' || player1 == 'X')
		ai = 'o';
	else
		ai = 'x';
	return ai;
}

// Initiation Player markers
char playerchoice (string s)
{
	while(1)
	{
		string choice;
		cout << s << ": Choice your symbol, want you play (Press any letter or number key)\n";
		cin >> choice;
		if(choice.size() > 1)
		{
			cout << "Error. This Command Not Exist. Try again\n";
			continue;
		}
		cout << endl;
		return choice[0];
	}
}

// Game Mechanic: Display information about Win/Lose or Draw
void play (char board[3][3], char player1, char ai)
{
	int moves = 0;
	while (moves < 9)
	{
		placement(board, player1);
		moves++;
		print(board);
		if (check(board))
		{
			cout << player1 << "Player Win!\n\n";
			return;
		}
		if (moves == 9)
		{
			cout << "Draw\n\n";
			break;
		}
		int nmove = pickmove(board, ai, player1);
		int row = nmove / 10;
		int col = nmove % 10;
		board[row][col] = ai;
		moves++;
		print(board);
		if (check(board))
		{
			cout << ai << "AI Wins\n\n";
			return;
		}
	}
}

int main()
{
	node game;
	game.player1 = playerchoice("Dear Player");
	game.ai = aichoice(game.player1);
	char x;
	while(1)
	{
		inboard(game.board);
		print(game.board);
		play(game.board, game.player1, game.ai);
		cout << "If you want to play again, press 'y' (to quit the game, press other key)";
		cin >> x;
		if (x != 'y')
		{
			cout << "\n";
			return 0;
		}
	}
}
