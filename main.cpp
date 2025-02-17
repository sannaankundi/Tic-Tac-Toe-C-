#include <iostream>
#include <limits>
using namespace std;

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}};

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;
    return false;
}

int evaluate() {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'O') return +10;
            else if (board[row][0] == 'X') return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'O') return +10;
            else if (board[0][col] == 'X') return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return +10;
        else if (board[0][0] == 'X') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return +10;
        else if (board[0][2] == 'X') return -10;
    }
    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();
    if (score == 10 || score == -10)
        return score;
    if (!isMovesLeft())
        return 0;
    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'O';
                    best = max(best, minimax(false));
                    board[i][j] = backup;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'X';
                    best = min(best, minimax(true));
                    board[i][j] = backup;
                }
            }
        }
        return best;
    }
}

void findBestMove() {
    int bestVal = -1000;
    int bestMoveRow = -1, bestMoveCol = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = backup;
                if (moveVal > bestVal) {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[bestMoveRow][bestMoveCol] = 'O';
}

void playerMove() {
    int move;
    cout << "Enter your move (1-9): ";
    cin >> move;
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = 'X';
    } else {
        cout << "Invalid move! Try again.\n";
        playerMove();
    }
}

int main() {
    cout << "Tic-Tac-Toe: You (X) vs AI (O)\n";
    printBoard();
    while (isMovesLeft()) {
        playerMove();
        printBoard();
        if (evaluate() == -10) {
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft()) break;
        cout << "AI is making a move...\n";
        findBestMove();
        printBoard();
        if (evaluate() == 10) {
            cout << "AI wins!\n";
            break;
        }
    }
    if (evaluate() == 0) cout << "It's a draw!\n";
    return 0;
}
