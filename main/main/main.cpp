#include<iostream>
#include<conio.h> //used for _getch()
#include<windows.h>
#include<cstdlib> //used for rand()

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

		if ((newRow >= 0) && (newRow < rows) && (newCol >= 0) && (newCol < columns) && (maze[newRow][newCol] == ' '))
		{
			maze[currentRow][currentColumn] = ' ';
			currentRow = newRow;
			currentColumn = newCol;
			maze[currentRow][currentColumn] = '*';
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
	maze[0][0] = '*';

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
	const char space = ' ';
	short newRow, newColumn;
	unsigned short r = 0, c = 0, cycles = 0, neighbour;

	bool possible;

	maze[0][0] = space;

	srand(time(NULL));
	do
	{
		cycles = 0;
		do
		{
			possible = true;

			if (cycles <= rows * columns)
			{
				newRow = r;
				newColumn = c;
				cycles++;
			}
			else 
			{
				do
				{
					newRow = rand() % rows;
					newColumn = rand() % columns;
				} while (maze[newRow][newColumn] != space);

				r = newRow;
				c = newColumn;
				cycles = 0;
			}

			neighbour = rand() % 4;

			switch(neighbour)
			{
			case 0: newColumn--; break;

			case 1: newColumn++; break;

			case 2: newRow--; break;

			case 3: newRow++; break;
			}

			if ((newRow < 0) || (newRow >= rows) || (newColumn < 0) || (newColumn >= columns))
				possible = false;
			else
				if (maze[newRow][newColumn] == space)
					possible = false;
				else
				{
					neighbour = 0;

					if ((newRow > 0) && (maze[newRow - 1][newColumn] == space))
						neighbour++;

					if ((newRow < rows - 1) && (maze[newRow + 1][newColumn] == space))
						neighbour++;

					if ((newColumn > 0) && (maze[newRow][newColumn - 1] == space))
						neighbour++;

					if ((newColumn < columns - 1) && (maze[newRow][newColumn + 1] == space))
						neighbour++;

					if (neighbour > 1)
						possible = false;
				}

		} while (!possible);

		r = newRow;
		c = newColumn;
		maze[newRow][newColumn] = space;

	} while (!((r == rows - 1) && (c == columns - 1)));
}

void gotoXY(int x, int y)
{
	COORD coords;
	coords.X = x;
	coords.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}

void displayMenu()
{
	system("cls");

	char key;
	int y = 2, choice = 0;

	bool flag = true;

	gotoXY(5, 0); std::cout << "MAZE MENU";
	gotoXY(3, 2); std::cout << "->";

	while (flag == true)
	{
		gotoXY(5, 2); std::cout << "Maze game";
		gotoXY(5, 3); std::cout << "Guide";
		gotoXY(5, 4); std::cout << "Quit\n";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && y != 4)
		{
			gotoXY(3, y); std::cout << "  ";
			y++;
			gotoXY(3, y); std::cout << "->";
			choice++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 2)
		{
			gotoXY(3, y); std::cout << "  ";
			y--;
			gotoXY(3, y); std::cout << "->";
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

				system("cls");

				std::cout << "\nThe game has ended" << std::endl;
				flag = false;

			} break;
			case 1:
			{
				std::cout << "In maintenance" << std::endl;
				flag = false;
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