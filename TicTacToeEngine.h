#pragma once

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

extern char board[3][3];

struct Move {
    int row;
    int col;
};

extern int player;

void initializeBoard();
char checkWinner();
bool isDraw();
vector<pair<int, int>> getAvailableMoves();
int minimax(char player);
Move findBestMove(char ai);
//void winOrdraw(int row, int col, int currentPlayer);
//void aiMove(int row, int col);
//void calculate();



