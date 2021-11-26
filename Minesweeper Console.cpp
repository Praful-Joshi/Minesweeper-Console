#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define length 9

char intToChar(int data)
{
	if (data == 0) return '0';
	if (data == 1) return '1';
	if (data == 2) return '2';
	if (data == 3) return '3';
	if (data == 4) return '4';
	if (data == 5) return '5';
	if (data == 6) return '6';
	if (data == 7) return '7';
	if (data == 8) return '8';
}

int charToInt(char data)
{
	if (data == '0') return 0;
	if (data == '1') return 1;
	if (data == '2') return 2;
	if (data == '3') return 3;
	if (data == '4') return 4;
	if (data == '5') return 5;
	if (data == '6') return 6;
	if (data == '7') return 7;
	if (data == '8') return 8;
}

int randomNum(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}

void displayInfo()
{
	cout << endl;
	cout << "                                              WELCOME TO MINESWEEPER - CONSOLE EDITION" << endl;
	cout << endl;
	cout << "RULES: " << endl;
	cout << "1) You'll be given a 9x9 board.\n2) There are mines spread randomly across the board.\n3) A player has to enter the row and column number of the box they want to open.\n4) After opening the box, there could be a mine or a number or a blank space.\n5) The number denotes the number of mines surrounding that particular box.\n6) Number or a space means you are safe. Mine means game over.\n7) First move is always the safe one." << endl;
	cout << endl;
	cout << "LET'S BEGIN!!!" << endl;
}

class Board
{
private:
	int numBombs, inputCount = 0;
	char board[length][length];
	char visibleBoard[length][length];

public:
	vector < pair<int, int> > dug;
	vector < pair<int, int> > ::iterator it;

	Board(int numBombs)
	{
		this->numBombs = numBombs;
		this->inputCount = inputCount;
		initiateBoard();
		assignValuesToBoard();
	}

	void initiateBoard()
	{
		//inititalize board with blank spaces
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				board[i][j] = ' ';
			}
		}

		//planting the bombs at random locations
		int bombsPlanted = 0;
		while (bombsPlanted < numBombs)
		{
			int loc = randomNum(0, (length * length - 1));
			int row = loc / length;
			int col = loc % length;

			if (board[row][col] == '*')
			{
				continue;
			}

			board[row][col] = '*';
			bombsPlanted++;
		}
	}

	void assignValuesToBoard()
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (board[i][j] == '*')
				{
					continue;
				}
				board[i][j] = getNumNeighboringBombs(i, j);
			}
		}
	}

	char getNumNeighboringBombs(int r, int c)
	{
		int bombCount = 0;

		if (r == 0 && c != 0 && c != 8)
		{
			for (int i = r; i <= r + 1; i++)
			{
				for (int j = c - 1; j <= c + 1; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else if (r == 8 && c != 0 && c != 8)
		{
			for (int i = r - 1; i <= r; i++)
			{
				for (int j = c - 1; j <= c + 1; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else if (c == 0 && r != 0 && r != 8)
		{
			for (int i = r - 1; i <= r + 1; i++)
			{
				for (int j = c; j <= c + 1; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else if (c == 8 && r != 0 && r != 8)
		{
			for (int i = r - 1; i <= r + 1; i++)
			{
				for (int j = c - 1; j <= c; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else if (r == 0 && c == 0)
		{
			for (int i = r; i <= r + 1; i++)
			{
				for (int j = c; j <= c + 1; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else if (r == 0 && c == 8)
		{
			for (int i = r; i <= r + 1; i++)
			{
				for (int j = c - 1; j <= c; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else if (r == 8 && c == 0)
		{
			for (int i = r - 1; i <= r; i++)
			{
				for (int j = c; j <= c + 1; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else if (r == 8 && c == 8)
		{
			for (int i = r - 1; i <= r; i++)
			{
				for (int j = c - 1; j <= c; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}
		else
		{
			for (int i = r - 1; i <= r + 1; i++)
			{
				for (int j = c - 1; j <= c + 1; j++)
				{
					if (i == r && j == c)
					{
						//original location, don't check
						continue;
					}
					if (board[i][j] == '*')
					{
						bombCount++;
					}
				}
			}
		}

		return intToChar(bombCount);
	}

	bool dig(int r, int c)
	{
		dug.push_back(make_pair(r, c));

		if (board[r][c] == '*')
			return false;
		else if (charToInt(board[r][c]) > 0)
			return true;
		else if (board[r][c] == ' ')
		{
			if (r == 0 && c != 0 && c != 8)
			{
				for (int i = r; i <= r + 1; i++)
				{
					for (int j = c - 1; j <= c + 1; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else if (r == 8 && c != 0 && c != 8)
			{
				for (int i = r - 1; i <= r; i++)
				{
					for (int j = c - 1; j <= c + 1; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else if (c == 0 && r != 0 && r != 8)
			{
				for (int i = r - 1; i <= r + 1; i++)
				{
					for (int j = c; j <= c + 1; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else if (c == 8 && r != 0 && r != 8)
			{
				for (int i = r - 1; i <= r + 1; i++)
				{
					for (int j = c - 1; j <= c; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else if (r == 0 && c == 0)
			{
				for (int i = r; i <= r + 1; i++)
				{
					for (int j = c; j <= c + 1; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else if (r == 0 && c == 8)
			{
				for (int i = r; i <= r + 1; i++)
				{
					for (int j = c - 1; j <= c; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else if (r == 8 && c == 0)
			{
				for (int i = r - 1; i <= r; i++)
				{
					for (int j = c; j <= c + 1; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else if (r == 8 && c == 8)
			{
				for (int i = r - 1; i <= r; i++)
				{
					for (int j = c - 1; j <= c; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
			else
			{
				for (int i = r - 1; i <= r + 1; i++)
				{
					for (int j = c - 1; j <= c + 1; j++)
					{
						if (find(dug.begin(), dug.end(), make_pair(r, c)) != dug.end())
						{
							continue; //dont dig where you've already dug
						}
						dig(r, c);
					}
				}
			}
		}

		return true;
	}

	void displayVisibleBoard()
	{
		//initialize visible board with blank spaces
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				visibleBoard[i][j] = ' ';
			}
		}
		//check dug spots
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (find(dug.begin(), dug.end(), make_pair(i, j)) != dug.end())
				{
					visibleBoard[i][j] = board[i][j];
				}
				else
				{
					visibleBoard[i][j] = ' ';
				}
			}
		}
		//display visible board
		printVisibleBoard();
	}

	void displayBoard()
	{
		cout << endl;
		cout << "   1 2 3 4 5 6 7 8 9" << endl;
		cout << "  -------------------" << endl;
		for (int i = 0; i < length; i++)
		{
			cout << i + 1 << " ";
			for (int j = 0; j < length; j++)
			{
				cout << "|" << board[i][j];
			}
			cout << "|" << endl;
			cout << "  -------------------" << endl;
		}
		cout << endl;
	}

	void printVisibleBoard()
	{
		cout << endl;
		cout << "   1 2 3 4 5 6 7 8 9" << endl;
		cout << "  -------------------" << endl;
		for (int i = 0; i < length; i++)
		{
			cout << i + 1 << " ";
			for (int j = 0; j < length; j++)
			{
				cout << "|" << visibleBoard[i][j];
			}
			cout << "|" << endl;
			cout << "  -------------------" << endl;
		}
		cout << endl;
	}
};

void play(int numBombs)
{
	int inputCount = 0;
	int r, c;
	bool safe = true;

	Board* mineBoard = new Board(numBombs);

	displayInfo();

	while (mineBoard->dug.size() < (length * length - numBombs))
	{
		mineBoard->displayVisibleBoard();
		input:
		cout << "Where do you want to dig? Enter row and column number: ";
		cin >> r >> c;

		if (r < 1 || r > 9 || c < 1 || c > 9)
		{
			cout << "Enter valid position: ";
			goto input;
		}

		if (inputCount < 1)
		{
			safe = mineBoard->dig(r - 1, c - 1);
			
			while (!safe)
			{
				mineBoard->initiateBoard();
				mineBoard->assignValuesToBoard();
				safe = mineBoard->dig(r - 1, c - 1);
			}
		}
		else
		{
			safe = mineBoard->dig(r - 1, c - 1);

			if (!safe)
			{
				mineBoard->displayVisibleBoard();
				cout << "Game over!" << endl;
				break;
			}
		}
		inputCount++;
	}

	if (safe)
	{
		cout << "You won!!" << endl;
	}
}

int main() {
	srand((time(NULL)));
	int numBombs = 10;
	play(numBombs);
}