
#include "OseroGame.h"

OseroGame::OseroGame(int size)  
	: player1(std::make_unique<Human>(osero::BLACK)),
      player2(std::make_unique<Player>(osero::WHITE)), 
      board(size)  
{  
	// �R���X�g���N�^�̏��������X�g�Ń����o�ϐ���������
}
void OseroGame::start()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
}

void OseroGame::changePlayer()
{
    currentPlayerPtr = (currentPlayerPtr == player1.get()) ? player2.get() : player1.get();
}

void OseroGame::endGame()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
}

int OseroGame::checkGameOver()  
{  
    
    const int size = board.sizeOfBoard(); 
	int currentPlayer = this->currentPlayerPtr->getColor(); // ���݂̃v���C���[�̐F���擾
	int oppositePlayer = (currentPlayer == osero::BLACK) ? osero::WHITE : osero::BLACK;
	unsigned char continueFlag = 0; // ���s�t���O��������

    for (int row = 0; row < size; ++row) {  
        for (int col = 0; col < size; ++col) {  
            if (board.getCell(row,col) == osero::NONE && board.isLegalMove(row, col, currentPlayer)) {
                return 1; //�ݒu�ł��邽�ߑ��s 
            }  
            else if (board.getCell(row, col) == osero::NONE && board.isLegalMove(row, col, oppositePlayer)) {
				continueFlag = 1; // ����̎�ԂŐݒu�\�ȏꏊ�����邽�ߑ��s�t���O�𗧂Ă�
                continue;
            }
        }  
    }  
    if(continueFlag == 0) { // �ǂ�����ݒu�ł��Ȃ��ꍇ
        endGame(); //�I���������Ăяo��
        return 0; // �I��
    }
    else {
        changePlayer(); // �v���C���[�����
		return 1; // ���s
    }

}

void OseroGame::goGame()
{
    try {
        //�Ֆʏo�͏����������ɋL�q
        int row, col;
        currentPlayerPtr = this->player1.get(); // �����v���C���[��ݒ�
        while (this->checkGameOver()) {
            
            if (std::cin.fail()) {
                throw std::runtime_error("Invalid input. Please enter two integers for row and column.");
            }
            currentPlayerPtr->getMove(row, col);
			// �Ֆʂ̏�Ԃ�\�����鏈���������ɋL�q
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
