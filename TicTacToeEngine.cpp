#include <wx/wx.h>
#include "TicTacToeEngine.h"


char board[3][3] =
{
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' '
};


void initializeBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}


char checkWinner() {

    for(int i = 0; i < 3; i++) {
        if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    for(int j = 0; j < 3; j++) {
        if(board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return board[0][j];
        }
    }

    if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }

    if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    return ' ';

}


bool isDraw() {

    if(checkWinner() != ' ') {
        return false;
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                return false;
            }
        }
    }

    return true;

}


vector<pair<int, int>> getAvailableMoves() {

    vector<pair<int, int>> moves;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                moves.push_back({i, j});
            }
        }
    }

    return moves;

}

int minimax(char player) {

    if(checkWinner() == 'x') {
        return 10;
    }

    if(checkWinner() == 'o') {
        return -10;
    }

    if(isDraw()) {
        return 0;
    }

    vector<pair<int, int>> moves = getAvailableMoves();
    int bestScore;

    if(player == 'x') {

        bestScore = -1000;
        for(auto const& move : moves) {

            board[move.first][move.second] = player;

            int score = minimax('o');

            board[move.first][move.second] = ' ';

            bestScore = max(bestScore, score);

        }

    }

    else {

        bestScore = 100;
        for(auto const& move : moves) {

            board[move.first][move.second] = player;

            int score = minimax('x');

            board[move.first][move.second] = ' ';

            bestScore = min(bestScore, score);

        }

    }

    return bestScore;

}


Move findBestMove(char ai) {

    int bestScore;
    Move bestmove;
    bestmove.row = -1;
    bestmove.col = -1;

    if(ai == 'x') {
        bestScore = -1000;
    }
    else {
        bestScore = 1000;
    }

    vector<pair<int, int>> moves = getAvailableMoves();
    for(auto const& move : moves) {

        board[move.first][move.second] = ai;

        char human = (ai == 'x') ? 'o' : 'x';

        int moveScore = minimax(human);

        board[move.first][move.second] = ' ';


        if(ai == 'x') {
            if(moveScore > bestScore) {
                bestScore = moveScore;
                bestmove.row = move.first;
                bestmove.col = move.second;
            }
        }
        else if(ai == 'o') {
            if(moveScore < bestScore) {
                bestScore = moveScore;
                bestmove.row = move.first;
                bestmove.col = move.second;
            }
        }

    }

    return bestmove;

}

