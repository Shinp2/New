#pragma once
#include "common.h"
#include "Ai.h"
#include "Human.h"
#include "Board.h"
#include "JsonIO.h"
#include <memory>

class OseroGame
{
private:
	osero::GameState gameState = osero::GameState::RUNNING;
protected:
	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	Player* currentPlayerPtr;
	std::unique_ptr<Board> board;
	JsonIO jsonIO;
	void changePlayer();
	void endGame();
public:
	OseroGame(int size);
	OseroGame(std::unique_ptr<Board> boardPtr);

	int checkGameOver();
	void start();
	void goGame();
	bool loadFromJsonForm();
};
