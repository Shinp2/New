
#include "Player.h"
class Ai :
    public Player
{
protected:
    // �~�j�}�b�N�X�@�̐[������
    const int MAX_DEPTH = 5; // �[����5�ɐݒ�
    // �]���֐��̏d��
    const int CORNER_WEIGHT = 1000;
    const int EDGE_WEIGHT = 500;
    const int CENTER_WEIGHT = 300;
    // �Ֆʂ̕]���֐�
    int evaluateCorner(const Board& board, int playerType);
    int evaluateEdge(const Board& board, int playerType);
	int evaluateCenter(const Board& board, int playerType);
public:
    Ai(int color) : Player(color) {}; // �R���X�g���N�^��ǉ�
    bool getMove(Board& board) override; // �C��: ���N���X�̊֐��V�O�l�`���Ɉ�v������
    int minimax(int depth, bool maximizingPlayer, int turnPlayer, int evalPlayerType);
    // �Ֆʂ�]��
    int evaluateBoard(int playerType);
}; 
