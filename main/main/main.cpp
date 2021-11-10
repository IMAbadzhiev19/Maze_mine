#include<iostream>

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

}

bool Maze::Go()
{

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

		for (unsigned short c = 0; c < columns, maze[r][c] = 'X'; c++);
	}
}

int main()
{

}