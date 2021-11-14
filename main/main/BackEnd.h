#pragma once

class Maze
{
public:

	Maze(short row, short col);
	void Show();
	bool Go();

private:

	void GenerateQuestion();
	bool Init();
	short GetKeyCode();
	void GeneratePath();
	void DirectDig();
	char** maze;
	unsigned short rows, columns;
	short currentRow, currentColumn;
	const char label = ' ';
};