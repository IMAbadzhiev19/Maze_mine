#include<iostream>
#include<conio.h> //used for _getch()
#include<windows.h>
#include<cstdlib> //used for rand()
#include<iomanip>

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

	bool here = true;
	int y = 14, choice = 0;

	while (here == true)
	{
		gotoXY(0, 0); std::cout << "*-------------------------------------------------------------------------------------*" << std::endl;
		gotoXY(0, 1); std::cout << ":                                                                                     :" << std::endl;
		gotoXY(0, 2); std::cout << ":  _______  __   __  _______  ______    _______  _______  _______  _______  ______    :" << std::endl;
		gotoXY(0, 3); std::cout << ": |       ||  | |  ||   _   ||    _ |  |   _   ||       ||       ||       ||    _ |   :" << std::endl;
		gotoXY(0, 4); std::cout << ": |       ||  |_|  ||  |_|  ||   | ||  |  |_|  ||       ||_     _||    ___||   | ||   :" << std::endl;
		gotoXY(0, 5); std::cout << ": |       ||       ||       ||   |_||_ |       ||       |  |   |  |   |___ |   |_||_  :" << std::endl;
		gotoXY(0, 6); std::cout << ": |      _||       ||       ||    __  ||       ||      _|  |   |  |    ___||    __  | :" << std::endl;
		gotoXY(0, 7); std::cout << ": |     |_ |   _   ||   _   ||   |  | ||   _   ||     |_   |   |  |   |___ |   |  | | :" << std::endl;
		gotoXY(0, 8); std::cout << ": |_______||__| |__||__| |__||___|  |_||__| |__||_______|  |___|  |_______||___|  |_| :" << std::endl;
		gotoXY(0, 9); std::cout << ":                                                                                     :" << std::endl;
		gotoXY(0, 10); std::cout << ":                                                                                     :" << std::endl;
		gotoXY(0, 11); std::cout << "*-------------------------------------------------------------------------------------*" << std::endl;

		gotoXY(37, 14); std::cout << "First: " << char(1);
		gotoXY(37, 15); std::cout << "Second: " << char(2);
		gotoXY(37, 16); std::cout << "Third: " << char(5);
		gotoXY(37, 17); std::cout << "Fourth: " << char(6);

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 17)
		{
			gotoXY(34, y); std::cout << "  ";
			y++;
			gotoXY(34, y); std::cout << "-> ";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 14)
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
	int y = 14, choice = 0;

	while (here1 == true)
	{
		gotoXY(0, 0); std::cout << "*---------------------------------------------------------*" << std::endl;
		gotoXY(0, 1); std::cout << ":                                                         :" << std::endl;
		gotoXY(0, 2); std::cout << ":  _______  _______  ___      _______  ______    _______  :" << std::endl;
		gotoXY(0, 3); std::cout << ": |       ||       ||   |    |       ||    _ |  |       | :" << std::endl;
		gotoXY(0, 4); std::cout << ": |       ||   _   ||   |    |   _   ||   | ||  |  _____| :" << std::endl;
		gotoXY(0, 5); std::cout << ": |       ||  | |  ||   |    |  | |  ||   |_||_ | |_____  :" << std::endl;
		gotoXY(0, 6); std::cout << ": |      _||  |_|  ||   |___ |  |_|  ||    __  ||_____  | :" << std::endl;
		gotoXY(0, 7); std::cout << ": |     |_ |       ||       ||       ||   |  | | _____| | :" << std::endl;
		gotoXY(0, 8); std::cout << ": |_______||_______||_______||_______||___|  |_||_______| :" << std::endl;
		gotoXY(0, 9); std::cout << ":                                                         :" << std::endl;
		gotoXY(0, 10); std::cout << ":                                                         :" << std::endl;
		gotoXY(0, 11); std::cout << "*---------------------------------------------------------*" << std::endl;

		gotoXY(25, 14); std::cout << "Red";
		gotoXY(25, 15); std::cout << "Green";
		gotoXY(25, 16); std::cout << "Aqua";
		gotoXY(25, 17); std::cout << "Purple";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 17)
		{
			gotoXY(22, y); std::cout << "  ";
			y++;
			gotoXY(22, y); std::cout << "-> ";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 14)
		{
			gotoXY(22, y); std::cout << "  ";
			y--;
			gotoXY(22, y); std::cout << "-> ";
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

void mazeDifficulties()
{
	system("cls");

	bool here1 = true;
	int y = 14, choice = 0;

	while (here1 == true)
	{
		gotoXY(0, 0); std::cout << "*--------------------------------------------------------------------------------------*" << std::endl;
		gotoXY(0, 1); std::cout << ":                                                                                      :" << std::endl;
		gotoXY(0, 2); std::cout << ":  ______   ___   _______  _______  ___   _______  __   __  ___      _______  __   __  :" << std::endl;
		gotoXY(0, 3); std::cout << ": |      | |   | |       ||       ||   | |       ||  | |  ||   |    |       ||  | |  | :" << std::endl;
		gotoXY(0, 4); std::cout << ": |  _    ||   | |    ___||    ___||   | |       ||  | |  ||   |    |_     _||  |_|  | :" << std::endl;
		gotoXY(0, 5); std::cout << ": | | |   ||   | |   |___ |   |___ |   | |       ||  |_|  ||   |      |   |  |       | :" << std::endl;
		gotoXY(0, 6); std::cout << ": | |_|   ||   | |    ___||    ___||   | |      _||       ||   |___   |   |  |_     _| :" << std::endl;
		gotoXY(0, 7); std::cout << ": |       ||   | |   |    |   |    |   | |     |_ |       ||       |  |   |    |   |   :" << std::endl;
		gotoXY(0, 8); std::cout << ": |______| |___| |___|    |___|    |___| |_______||_______||_______|  |___|    |___|   :" << std::endl;
		gotoXY(0, 9); std::cout << ":                                                                                      :" << std::endl;
		gotoXY(0, 10);std::cout << ":                                                                                      :" << std::endl;
		gotoXY(0, 11); std::cout << "*--------------------------------------------------------------------------------------*" << std::endl;

		gotoXY(33, 14); std::cout << "Easy";
		gotoXY(33, 15); std::cout << "Medium";
		gotoXY(33, 16); std::cout << "Hard";
		gotoXY(33, 17); std::cout << "Impossible";
		gotoXY(33, 18); std::cout << "Custom";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 18)
		{
			gotoXY(30, y); std::cout << "  ";
			y++;
			gotoXY(30, y); std::cout << "-> ";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 14)
		{
			gotoXY(30, y); std::cout << "  ";
			y--;
			gotoXY(30, y); std::cout << "-> ";
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
				Maze easy_maze(10, 20);
				easy_maze.Go();

				Sleep(1000);
				system("cls");

				std::cout << std::endl << "*-----------------------------------------------------------*" << std::endl;
				std::cout << "|  __   __  _______  __   __    _     _  ___   __    _  __  |" << std::endl;
				std::cout << "| |  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |" << std::endl;
				std::cout << "| |  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |" << std::endl;
				std::cout << "| |       ||  | |  ||  |_|  |  |       ||   | |       ||  | |" << std::endl;
				std::cout << "| |_     _||  |_|  ||       |  |       ||   | |  _    ||__| |" << std::endl;
				std::cout << "|   |   |  |       ||       |  |   _   ||   | | | |   | __  |" << std::endl;
				std::cout << "|   |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |" << std::endl;
				std::cout << "*-----------------------------------------------------------*" << std::endl;

				Sleep(2000);
				system("cls");

				here1 = false;

			} break;
			case 1:
			{
				Maze medium_maze(20, 30);
				medium_maze.Go();

				Sleep(1000);
				system("cls");

				std::cout << std::endl << "*-----------------------------------------------------------*" << std::endl;
				std::cout << "|  __   __  _______  __   __    _     _  ___   __    _  __  |" << std::endl;
				std::cout << "| |  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |" << std::endl;
				std::cout << "| |  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |" << std::endl;
				std::cout << "| |       ||  | |  ||  |_|  |  |       ||   | |       ||  | |" << std::endl;
				std::cout << "| |_     _||  |_|  ||       |  |       ||   | |  _    ||__| |" << std::endl;
				std::cout << "|   |   |  |       ||       |  |   _   ||   | | | |   | __  |" << std::endl;
				std::cout << "|   |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |" << std::endl;
				std::cout << "*-----------------------------------------------------------*" << std::endl;

				Sleep(2000);
				system("cls");

				here1 = false;
			} break;
			case 2:
			{
				Maze hard_maze(20, 40);
				hard_maze.Go();

				Sleep(1000);
				system("cls");

				std::cout << std::endl << "*-----------------------------------------------------------*" << std::endl;
				std::cout << "|  __   __  _______  __   __    _     _  ___   __    _  __  |" << std::endl;
				std::cout << "| |  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |" << std::endl;
				std::cout << "| |  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |" << std::endl;
				std::cout << "| |       ||  | |  ||  |_|  |  |       ||   | |       ||  | |" << std::endl;
				std::cout << "| |_     _||  |_|  ||       |  |       ||   | |  _    ||__| |" << std::endl;
				std::cout << "|   |   |  |       ||       |  |   _   ||   | | | |   | __  |" << std::endl;
				std::cout << "|   |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |" << std::endl;
				std::cout << "*-----------------------------------------------------------*" << std::endl;

				Sleep(2000);
				system("cls");

				here1 = false;
			} break;
			case 3:
			{
				Maze impossible_maze(25, 90);
				impossible_maze.Go();

				Sleep(1000);
				system("cls");

				std::cout << std::endl << "*-----------------------------------------------------------*" << std::endl;
				std::cout << "|  __   __  _______  __   __    _     _  ___   __    _  __  |" << std::endl;
				std::cout << "| |  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |" << std::endl;
				std::cout << "| |  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |" << std::endl;
				std::cout << "| |       ||  | |  ||  |_|  |  |       ||   | |       ||  | |" << std::endl;
				std::cout << "| |_     _||  |_|  ||       |  |       ||   | |  _    ||__| |" << std::endl;
				std::cout << "|   |   |  |       ||       |  |   _   ||   | | | |   | __  |" << std::endl;
				std::cout << "|   |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |" << std::endl;
				std::cout << "*-----------------------------------------------------------*" << std::endl;

				Sleep(2000);
				system("cls");

				here1 = false;

			} break;
			case 4:
			{
				int rows, columns;

				while (true)
				{
					std::cout << "Enter the height of the maze: "; std::cin >> rows;
					std::cout << "Enter the width of the maze: "; std::cin >> columns;

					if (rows >= 0 && columns >= 0)
						break;
					else
						system("cls");
				}

				Maze maze(rows, columns);
				maze.Go();

				Sleep(1000);
				system("cls");

				std::cout << std::endl << "*-----------------------------------------------------------*" << std::endl;
				std::cout << "|  __   __  _______  __   __    _     _  ___   __    _  __  |" << std::endl;
				std::cout << "| |  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |" << std::endl;
				std::cout << "| |  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |" << std::endl;
				std::cout << "| |       ||  | |  ||  |_|  |  |       ||   | |       ||  | |" << std::endl;
				std::cout << "| |_     _||  |_|  ||       |  |       ||   | |  _    ||__| |" << std::endl;
				std::cout << "|   |   |  |       ||       |  |   _   ||   | | | |   | __  |" << std::endl;
				std::cout << "|   |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |" << std::endl;
				std::cout << "*-----------------------------------------------------------*" << std::endl;

				Sleep(2000);
				system("cls");

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
	int y = 14, choice = 0;

	while (here2 == true)
	{
		gotoXY(0, 0); std::cout << "*--------------------------------------------------------------*" << std::endl;
		gotoXY(0, 1); std::cout << ":                                                              :" << std::endl;
		gotoXY(0, 2); std::cout << ":  _______  _______  _______  ___   _______  __    _  _______  :" << std::endl;
		gotoXY(0, 3); std::cout << ": |       ||       ||       ||   | |       ||  |  | ||       | :" << std::endl;
		gotoXY(0, 4); std::cout << ": |   _   ||    _  ||_     _||   | |   _   ||   |_| ||  _____| :" << std::endl;
		gotoXY(0, 5); std::cout << ": |  | |  ||   |_| |  |   |  |   | |  | |  ||       || |_____  :" << std::endl;
		gotoXY(0, 6); std::cout << ": |  |_|  ||    ___|  |   |  |   | |  |_|  ||  _    ||_____  | :" << std::endl;
		gotoXY(0, 7); std::cout << ": |       ||   |      |   |  |   | |       || | |   | _____| | :" << std::endl;
		gotoXY(0, 8); std::cout << ": |_______||___|      |___|  |___| |_______||_|  |__||_______| :" << std::endl;
		gotoXY(0, 9); std::cout << ":                                                              :" << std::endl;
		gotoXY(0, 10); std::cout << ":                                                              :" << std::endl;
		gotoXY(0, 11); std::cout << "*--------------------------------------------------------------*" << std::endl;

		gotoXY(25, 14); std::cout << "Characters";
		gotoXY(25, 15); std::cout << "Colors";
		gotoXY(25, 16); std::cout << "Back\n";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 16)
		{
			gotoXY(22, y); std::cout << "  ";
			y++;
			gotoXY(22, y); std::cout << "-> ";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 14)
		{
			gotoXY(22, y); std::cout << "  ";
			y--;
			gotoXY(22, y); std::cout << "-> ";
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
	int y = 13, choice = 0;

	bool flag = true;

	while (flag == true)
	{
		gotoXY(0, 0); std::cout << "*--------------------------------------*" << std::endl;
		gotoXY(0, 1); std::cout << ":                                      :" << std::endl;
		gotoXY(0, 2); std::cout << ":  __   __  _______  _______  _______  :" << std::endl;
		gotoXY(0, 3); std::cout << ": |  |_|  ||   _   ||       ||       | :" << std::endl;
		gotoXY(0, 4); std::cout << ": |       ||  |_|  ||____   ||    ___| :" << std::endl;
		gotoXY(0, 5); std::cout << ": |       ||       | ____|  ||   |___  :" << std::endl;
		gotoXY(0, 6); std::cout << ": |       ||       || ______||    ___| :" << std::endl;
		gotoXY(0, 7); std::cout << ": | ||_|| ||   _   || |_____ |   |___  :" << std::endl;
		gotoXY(0, 8); std::cout << ": |_|   |_||__| |__||_______||_______| :" << std::endl;
		gotoXY(0, 9); std::cout << ":                                      :" << std::endl;
		gotoXY(0, 10); std::cout << ":                                      :" << std::endl;
		gotoXY(0, 11); std::cout << "*--------------------------------------*" << std::endl;

		gotoXY(15, 13); std::cout << "Maze game";
		gotoXY(15, 14); std::cout << "Settings";
		gotoXY(15, 15); std::cout << "Quit\n";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 15)
		{
			gotoXY(12, y); std::cout << "  ";
			y++;
			gotoXY(12, y); std::cout << "->";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 13)
		{
			gotoXY(12, y); std::cout << "  ";
			y--;
			gotoXY(12, y); std::cout << "->";
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
				mazeDifficulties();
				continue;

			} break;
			case 1:
			{
				gameOptions();
			} break;
			case 2:
			{
				std::cout << "You have successfully exited" << std::endl;
				exit(0);
			} break;
			} //switch
		}
	}

}

int main()
{
	displayMenu();
}