#include<iostream>
#include<conio.h> //used for _getch()
#include<windows.h>
#include<cstdlib> //used for rand()
#include<iomanip>

#include "FrontEnd.h"
#include "BackEnd.h"

Maze::Maze(short row, short col) : rows(row), columns(col), currentRow(0), currentColumn(0), maze(nullptr)
{
	if (!Init()) {
		std::cout << "Failed" << std::endl;
		system("pause");
		exit(1);
	}
}

void Maze::Show()
{
	system("cls");
	const char fence = 'O';

	for (unsigned short i = 0; i < columns + 2; i++)
	{
		std::cout << fence;
	}

	std::cout << std::endl;

	for (unsigned short r = 0; r < rows; r++)
	{
		for (unsigned short left = 0; left < 1; left++)
			std::cout << fence;

		for (unsigned short c = 0; c < columns; c++)
			std::cout << maze[r][c];

		for (unsigned short right = 0; right < 1; right++)
			std::cout << fence;

		std::cout << std::endl;
	}

	for (unsigned short i = 0; i < columns + 2; i++)
	{
		std::cout << fence;
	}
}

bool Maze::Go()
{
	unsigned int moves = 0;
	short code, newRow, newCol;

	do
	{
		newRow = currentRow;
		newCol = currentColumn;

		code = GetKeyCode();

		switch (code)
		{
		case 72: newRow--; break;
		case 75: newCol--; break;
		case 77: newCol++; break;
		case 80: newRow++; break;
		default: Beep(500, 250); break;
		}

		if ((newRow >= 0) && (newRow < rows) && (newCol >= 0) && (newCol < columns) && ((maze[newRow][newCol] == ' ') || maze[newRow][newCol] == 'F'))
		{
			maze[currentRow][currentColumn] = ' ';
			currentRow = newRow;
			currentColumn = newCol;
			maze[currentRow][currentColumn] = character;

			Show();

			moves++;
			std::cout << "\n\nMoves: " << moves;
		}

	} while ((currentRow != rows - 1) || (currentColumn != columns - 1));

	return false;
}

bool Maze::Init()
{
	maze = new char* [rows];
	if (!maze)
		return false;
	for (unsigned short r = 0; r < rows; r++)
	{
		maze[r] = new char[columns];
		if (!maze[r])
			return false;

		for (unsigned short c = 0; c < columns; maze[r][c] = 'X', c++);
	}

	GeneratePath();

	maze[0][0] = character;
	maze[rows - 1][columns - 1] = 'F';

	Show();

	return true;
}

short Maze::GetKeyCode()
{
	short keyCode;
	keyCode = _getch();

	if ((keyCode == 0) || keyCode == 224)
		keyCode = _getch();

	return keyCode;
}

void Maze::GeneratePath()
{
	const char label = ' ';
	short nr, nc;
	unsigned short r = 0, c = 0, cycles, nb;
	bool possible;
	maze[0][0] = label;
	srand(time(NULL));
	do
	{
		cycles = 0;
		do
		{
			possible = true;
			if (cycles < rows * columns)
			{
				nr = r;
				nc = c;
				cycles++;
			}
			else // cycles is to big
			{
				// we need to find random cycle in maze, that contains symbol from const label
				do
				{
					nr = rand() % rows; // now nr contains value between 0 and rows
					nc = rand() % columns; // now nc contains value between 0 and columns
				} while (maze[nr][nc] != label);
				r = nr;
				c = nc;
				cycles = 0;
			}
			nb = rand();
			nb = nb % 4;
			switch (nb)
			{
			case 0:nc--;
				break;
			case 1:nc++;
				break;
			case 2:nr--;
				break;
			case 3:nr++;
				break;
			} // switch
			if ((nr < 0) || (nr >= rows) || (nc < 0) || (nc >= columns))
				possible = false;
			else
				if (maze[nr][nc] == label)
					possible = false;
				else
				{
					nb = 0;
					if ((nr > 0) && (maze[nr - 1][nc] == label))
						nb++;
					if ((nr < rows - 1) && (maze[nr + 1][nc] == label))
						nb++;
					if ((nc > 0) && (maze[nr][nc - 1] == label))
						nb++;
					if ((nc < columns - 1) && (maze[nr][nc + 1] == label))
						nb++;
					if (nb > 1)
						possible = false;
				}
		} while (!possible);
		r = nr;
		c = nc;
		maze[r][c] = label;
	} while (!((r == rows - 1) && (c == columns - 1)));
}