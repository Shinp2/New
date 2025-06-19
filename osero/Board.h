#pragma once
#include "common.h"
class Board
{
protected:
	std::vector<std::vector<int>> board;
	const int size;
public:
	bool isLegalMove(int x, int y, int color);
	// �΂�u���A���Ԃ��������s��
	void placeStone(int row, int col, int color);
	std::vector<std::pair<int, int>> getLegalMoves(int color);
	int countStones(int color);
	// �Ֆʂ��N���A����
	void clear();
	void flipDisks(int row, int col, int playerType);
	int getCell(int row, int col);
	void setCell(int row, int col, int color);
};

