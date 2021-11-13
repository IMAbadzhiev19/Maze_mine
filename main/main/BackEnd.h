#pragma once

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