#include<iostream>
using namespace std;

char board[3][3];

static void InitializeBoard()
{
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            board[i][j] = ' ';
        }
    }
}

static void DisplayBoard()
{
    cout << "  1 2 3" << endl;
    for (int i = 0;i < 3;i++)
    {
        cout << i + 1 << " ";
        for (int j = 0;j < 3;j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

static bool IsValidMove(int row, int col)
{
    if (row < 0 || row >= 3 || col < 0 || col >= 3)
    {
        return false;
    }
    return board[row][col] == ' ';
}

static bool IsGameOver()
{
    for (int i = 0;i < 3;i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return true;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return true;
        }
    }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return true;
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return true;
    }

    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

static void GetPlayerMove(char player, int& row, int& col)
{
    cout << "Player " << player << "'s Turn. Enter row and col between (1-3): " << endl;
    cin >> row >> col;
    row--;
    col--;
}

static void MakeMove(char player, int row, int col)
{
    board[row][col] = player;
}

int main()
{
    char currentPlayer = 'X';
    int row, col;
    InitializeBoard();

    while (true)
    {
        DisplayBoard();
        GetPlayerMove(currentPlayer, row, col);
        if (IsValidMove(row, col))
        {
            MakeMove(currentPlayer, row, col);
            if (IsGameOver())
            {
                DisplayBoard();
                cout << "Player " << currentPlayer << " wins." << endl;
                break;
            }
            else if (IsGameOver() && !IsValidMove(row, col))
            {
                DisplayBoard();
                cout << " It's a Draw." << endl;
                break;
            }
            currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
        }
        else
        {
            cout << "Invalid Move! Try Again." << endl;
        }
    }

    char playAgain;
    cout << "Do you want to play Again? (Y/N): " << endl;
    cin >> playAgain;
    if (playAgain == 'Y' || playAgain == 'y')
    {
        InitializeBoard();
        main();
    }
    else
    {
        cout << "Thank you for playing game. " << endl;
    }
    return 0;
}
