#include <iostream>
#include <vector>

using namespace std;


void displayBoard(const vector<vector<char>>& board);
bool checkWin(const vector<vector<char>>& board, char player);
bool checkDraw(const vector<vector<char>>& board);
void switchPlayer(char& currentPlayer);

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' ')); 
    char currentPlayer = 'X';
    
        bool gameOver = false;
        while (!gameOver) {
            displayBoard(board);

            int row, col;
            cout << "Player " << currentPlayer << "'s Turn. Enter row and col between (1-3): ";
            cin >> row >> col;
            row--;
            col--;

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                cout << "Invalid move! Try again." << endl;
                continue;
            }

            board[row][col] = currentPlayer;

            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!" << endl;
                gameOver = true;
                break;
            }

            if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!" << endl;
                gameOver = true;
                break;
            }

            switchPlayer(currentPlayer);
        }

    char playAgain;
    cout << "Do you want to play Again? (Y/N): " << endl;
    cin >> playAgain;
    if (playAgain == 'Y' || playAgain == 'y')
    {
        vector<vector<char>> board(3, vector<char>(3, ' '));
        main();
    }
    else
    {
        cout << "Thank you for playing game. " << endl;
    }

    return 0;
}

void displayBoard(const vector<vector<char>>& board) {
    cout << "  1 2 3" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkWin(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || 
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

bool checkDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer(char& currentPlayer) {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}
