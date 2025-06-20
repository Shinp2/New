#include "OseroGame.h"
#include "JsonIO.h"

int main(int argc,char** argv) {
	int flag = 0; // �t���O�ϐ��̏�����
	if (argc > 1) {
		if (argv[1] == "--flip") {
			flag = 1; // �t���O�𗧂Ă�
		}else if(argv[1] == "--json") {
			flag = 2; // json�`���Ŏ󂯎��t���O�𗧂Ă�
		} else if (argv[1] == "--help") {
			// �w���v���b�Z�[�W��\��
			std::cout << "Usage: osero [options]\n"
					  << "Options:\n"
					  << "  --flip   : Flip the board with json form\n"
					  << "  --json   : Run with json form\n"
					  << "  --help   : Show this help message\n";
			return 0;
	}
	// json�`���Ŏ󂯎�����ꍇ
	JsonIO json;
	OseroGame game(json);
	if (flag == 1) {
		game.sendJsonForm();
	}else if (flag == 2) {
		game.singleRun();
		game.sendJsonForm();
	}

	return 0;
}