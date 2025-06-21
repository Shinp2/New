
#include "Ai.h"


bool Ai::getMove(Board& board)
{
    osero::PlayerColor oppositColor =(this->playerColor == osero::BLACK ? osero::WHITE : osero::BLACK);

    int bestScore = -10000;
    int bestRow = -1, bestCol = -1;
    for (int row = 0; row < board.sizeOfBoard(); ++row) {
        for (int col = 0; col < board.sizeOfBoard(); ++col) {
            if (board.getCell(row,col) == osero::NONE && board.isLegalMove(row, col, this->playerColor)) {
                auto newBoard = board;

                newBoard.placeStone(row, col, playerColor);

                int score = minimax(newBoard, MAX_DEPTH - 1, true, oppositColor, this->playerColor,-10000,10000);
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
    }
    if (bestRow != -1 && bestCol != -1) {
        board.placeStone(bestRow, bestCol,playerColor);
		return true; // �œK�Ȏ�������Đ΂�u����
    }
    else {
        //�@�肪������Ȃ�����
		return false; // �肪�Ȃ��ꍇ��false��Ԃ�
    }
    
}
int Ai::minimax(Board& board, int depth, bool maximizingPlayer, int turnPlayer, int evalPlayerType, int alpha, int beta)
{
    osero::PlayerColor opponent = (turnPlayer == osero::BLACK ? osero::WHITE : osero::BLACK);
    if (depth <= 0) {
        return evaluateBoard(board,turnPlayer);
    }
    int bestScore = maximizingPlayer ? -10000 : 10000;
    bool hasMove = false;
    for (int row = 0; row < board.sizeOfBoard(); ++row) {
        for (int col = 0; col < board.sizeOfBoard(); ++col) {
            if (board.getCell(row, col) == osero::NONE && board.isLegalMove(row, col, turnPlayer)) {
                hasMove = true;
                auto newBoard = board;
                newBoard.placeStone(row, col, turnPlayer);

                int score = minimax(newBoard, depth - 1, !maximizingPlayer, opponent, evalPlayerType, alpha, beta);
                if (maximizingPlayer) {
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, bestScore);
                }
                else {
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, bestScore);
                }
                if (beta <= alpha) {
                    break; // �}����
                }
            }
        }
    }
    if (!hasMove) {
        return evaluateBoard(board,turnPlayer);
    }
    return bestScore;
}

// �Ֆʂ�]��
int Ai::evaluateBoard(Board& board,int playerType)
{
    osero::PlayerColor opponent = (playerType == osero::BLACK) ? osero::WHITE : osero::BLACK;
    int score = 0;

    // 1. �΂̐�
    int myStones = 0, oppStones = 0;
    for (int row = 0; row < board.sizeOfBoard(); ++row) {
        for (int col = 0; col < board.sizeOfBoard(); ++col) {
            int cell = board.getCell(row, col);
            if (cell == playerColor) myStones++;
            else if (cell == opponent) oppStones++;
        }
    }
    score += myStones - oppStones;

    // 2. �p�̕]��
    score += CORNER_WEIGHT * evaluateCorner(board, playerColor);
    score -= CORNER_WEIGHT * evaluateCorner(board, opponent);

    // 3. �ӂ̕]��
    score += EDGE_WEIGHT * evaluateEdge(board, playerColor);
    score -= EDGE_WEIGHT * evaluateEdge(board, opponent);

    // 4. �����̕]��
    score += CENTER_WEIGHT * evaluateCenter(board, playerColor);
    score -= CENTER_WEIGHT * evaluateCenter(board, opponent);

    return score;
}

int Ai::evaluateCorner(Board& board, int playerType) {
    int size = board.sizeOfBoard();
    int count = 0;
    // ����
    if (board.getCell(0, 0) == playerType) count++;
    // �E��
    if (board.getCell(0, size - 1) == playerType) count++;
    // ����
    if (board.getCell(size - 1, 0) == playerType) count++;
    // �E��
    if (board.getCell(size - 1, size - 1) == playerType) count++;
    return count;
}

int Ai::evaluateEdge(Board& board,int playerType) {
    int size = board.sizeOfBoard();
    int count = 0;

    // ��Ӂi����p�ƉE��p�͊܂߂Ȃ��ꍇ��+1, size-2�܂Łj
    for (int col = 1; col < size - 1; ++col) {
        if (board.getCell(0, col) == playerType) count++;
    }
    // ����
    for (int col = 1; col < size - 1; ++col) {
        if (board.getCell(size - 1, col) == playerType) count++;
    }
    // ����
    for (int row = 1; row < size - 1; ++row) {
        if (board.getCell(row, 0) == playerType) count++;
    }
    // �E��
    for (int row = 1; row < size - 1; ++row) {
        if (board.getCell(row, size - 1) == playerType) count++;
    }

    return count;
}

int Ai::evaluateCenter(Board& board, int playerType) {
    int size = board.sizeOfBoard();
    int count = 0;
    // ������4�Z����]��
    if (size % 2 == 0) { // �����T�C�Y�̏ꍇ
        for (int row = size / 2 - 1; row <= size / 2; ++row) {
            for (int col = size / 2 - 1; col <= size / 2; ++col) {
                if (board.getCell(row, col) == playerType) count++;
            }
        }
    } else { // ��T�C�Y�̏ꍇ
        int center = size / 2;
        if (board.getCell(center, center) == playerType) count++;
    }
    return count;
}

