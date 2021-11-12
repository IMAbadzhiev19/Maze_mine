#include<iostream>
#include<conio.h> //used for _getch()
#include<windows.h>
#include<cstdlib> //used for rand()
#include<iomanip>
#include<string>

char character = char(1);

class Maze
{
public:

	Maze(short row, short col);
	void Show();
	bool Go();

private:

	bool Init();
	short GetKeyCode();
	void GeneratePath();
	char** maze;
	unsigned short rows, columns;
	short currentRow, currentColumn;
};

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

void gotoXY(int x, int y)
{
	COORD coords;
	coords.X = x;
	coords.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}

void characterOptions()
{
	system("cls");

	std::cout << "*-------------------------------------------------------------------------------------*" << std::endl;
	std::cout << ":                                                                                     :" << std::endl;
	std::cout << ":  _______  __   __  _______  ______    _______  _______  _______  _______  ______    :" << std::endl;
	std::cout << ": |       ||  | |  ||   _   ||    _ |  |   _   ||       ||       ||       ||    _ |   :" << std::endl;
	std::cout << ": |       ||  |_|  ||  |_|  ||   | ||  |  |_|  ||       ||_     _||    ___||   | ||   :" << std::endl;
	std::cout << ": |       ||       ||       ||   |_||_ |       ||       |  |   |  |   |___ |   |_||_  :" << std::endl;
	std::cout << ": |      _||       ||       ||    __  ||       ||      _|  |   |  |    ___||    __  | :" << std::endl;
	std::cout << ": |     |_ |   _   ||   _   ||   |  | ||   _   ||     |_   |   |  |   |___ |   |  | | :" << std::endl;
	std::cout << ": |_______||__| |__||__| |__||___|  |_||__| |__||_______|  |___|  |_______||___|  |_| :" << std::endl;
	std::cout << ":                                                                                     :" << std::endl;
	std::cout << ":                                                                                     :" << std::endl;
	std::cout << "*-------------------------------------------------------------------------------------*" << std::endl;

	bool here = true;
	int y = 13, choice = 0;

	while (here == true)
	{
		gotoXY(37, 13); std::cout << "Character";
		gotoXY(37, 14); std::cout << "First: " << char(1);
		gotoXY(37, 15); std::cout << "Second: " << char(2);
		gotoXY(37, 16); std::cout << "Third: " << char(3);
		gotoXY(37, 17); std::cout << "Fourth: " << char(4);

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 17)
		{
			gotoXY(34, y); std::cout << "  ";
			y++;
			gotoXY(34, y); std::cout << "-> ";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 13)
		{
			gotoXY(34, y); std::cout << "  ";
			y--;
			gotoXY(34, y); std::cout << "-> ";
			choice--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");

			switch (choice)
			{
			case 0:
			{
				character = char(1);
				here = false;
			} break;
			case 1:
			{
				character = char(2);
				here = false;
			} break;
			case 2:
			{
				character = char(3);
				here = false;
			} break;
			case 3:
			{
				character = char(3);
				here = false;
			} break;
			} //switch
		}
	}
}

void colorOptions()
{
	system("cls");

	bool here1 = true;
	int y = 2, choice = 0;

	while (here1 == true)
	{
		gotoXY(5, 0); std::cout << "Colors";
		gotoXY(5, 2); std::cout << "Red";
		gotoXY(5, 3); std::cout << "Green";
		gotoXY(5, 4); std::cout << "Aqua";
		gotoXY(5, 5); std::cout << "Purple";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 5)
		{
			gotoXY(2, y); std::cout << "  ";
			y++;
			gotoXY(2, y); std::cout << "-> ";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 2)
		{
			gotoXY(2, y); std::cout << "  ";
			y--;
			gotoXY(2, y); std::cout << "-> ";
			choice--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");

			switch (choice)
			{
			case 0:
			{
				system("color 4");
				here1 = false;
			} break;
			case 1:
			{
				system("color 2");
				here1 = false;
			} break;
			case 2:
			{
				system("color 3");
				here1 = false;
			} break;
			case 3:
			{
				system("color 5");
				here1 = false;
			} break;
			} //switch
		}
	}
}

void gameOptions()
{
	system("cls");

	bool here2 = true;
	int y = 2, choice = 0;

	while (here2 == true)
	{
		gotoXY(5, 0); std::cout << "Options";
		gotoXY(5, 2); std::cout << "Characters";
		gotoXY(5, 3); std::cout << "Colors";
		gotoXY(5, 4); std::cout << "Back\n";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 4)
		{
			gotoXY(2, y); std::cout << "  ";
			y++;
			gotoXY(2, y); std::cout << "-> ";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 2)
		{
			gotoXY(2, y); std::cout << "  ";
			y--;
			gotoXY(2, y); std::cout << "-> ";
			choice--;
			continue;
		}


		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");

			switch (choice)
			{
			case 0:
			{
				characterOptions();
			} break;
			case 1:
			{
				colorOptions();
			} break;
			case 2:
			{
				here2 = false;
			} break;
			} //switch
		}
	}
}

void displayMenu()
{
	system("cls");
	int y = 2, choice = 0;

	bool flag = true;

	while (flag == true)
	{
		gotoXY(5, 0); std::cout << "MAZE MENU";
		gotoXY(5, 2); std::cout << "Maze game";
		gotoXY(5, 3); std::cout << "Settings";
		gotoXY(5, 4); std::cout << "Quit\n";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 4)
		{
			gotoXY(2, y); std::cout << "  ";
			y++;
			gotoXY(2, y); std::cout << "->";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 2)
		{
			gotoXY(2, y); std::cout << "  ";
			y--;
			gotoXY(2, y); std::cout << "->";
			choice--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");

			switch (choice)
			{
			case 0:
			{
				int rows, columns;

				std::cout << "Enter the height of the maze: "; std::cin >> rows;
				std::cout << "Enter the width of the maze: "; std::cin >> columns;

				Maze maze(rows, columns);
				maze.Go();

				std::cout << std::endl << std::setw(65) << "The game has ended" << std::endl;
				flag = false;

			} break;
			case 1:
			{
				gameOptions();
			} break;
			case 2:
			{
				std::cout << "You have successfully exited" << std::endl;
				flag = false;
			} break;
			} //switch
		}
	}

	exit(0);
}

int main()
{
	displayMenu();
}