#include "OseroGame.h"
#include "JsonIO.h"

int main(int argc,char** argv) {
	// json�`���Ŏ󂯎�����ꍇ
	JsonIO json;
	OseroGame game(json);
	game.singleRun();
	game.sendJsonForm();
	return 0;
}