
#include "Player.h"
class Ai :
    public Player
{
public:
    std::pair<int, int> getMove(const Board& board) override;
    int minimax(int depth, bool maximizingPlayer, int turnPlayer, int evalPlayerType);
    // �Ֆʂ�]��
    int evaluateBoard(int playerType);
};
