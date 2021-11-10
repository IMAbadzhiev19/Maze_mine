#include<iostream>
#include<conio.h>

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