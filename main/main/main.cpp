#include<iostream>
#include<conio.h> //used for _getch()
#include<windows.h>

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
	for (unsigned short r = 0; r < rows; r++)
	{
		for (unsigned short c = 0; c < columns; c++)
			std::cout << maze[r][c];

		std::cout << std::endl;
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
		}
		else
			Beep(500, 250);

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

	maze[0][0] = '*';
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

int main()
{
	Maze m(10, 30);
	m.Show();
}