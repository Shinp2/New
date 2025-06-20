#include "Player.h"
#include "json.hpp" 

class Human :
    public Player
{
public:
    bool getMove(Board& board) override;
      // �ǉ�: PlayerColor�^���󂯎��R���X�g���N�^
    Human(osero::PlayerColor color) : Player(color) {}
    void setLastMove(const std::pair<int, int>& move); 
private:
    std::pair<int, int> lastMove;
};
