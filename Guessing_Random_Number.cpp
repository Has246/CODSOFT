#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

int main()
{
    srand(time(0));

    int Random_Number;
    int Guess = 0; // Initialize Guess
    int Attempts = 0;

    Random_Number = rand() % 100 + 1;

    cout << "***Welcome To The Guessing World***" << endl << endl;

    do
    {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        cout << "Attempt " << Attempts + 1 << endl;
        cout << "Enter the Guess Number between (1 and 100): ";
        cin >> Guess;
        Attempts++;

        if (cin.fail() || Guess < 1 || Guess > 100)
        {
            cout << "Invalid input! Please enter a number between 1 and 100." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (Guess < Random_Number)
        {
            cout << "Too Low! Try Again: " << endl;
        }
        else if (Guess > Random_Number)
        {
            cout << "Too High! Try Again: " << endl;
        }
        else
        {
            cout << "Congratulations! You guessed right in " << Attempts << " attempts!." << endl;
        }
    } while (Guess != Random_Number);

    return 0;
}
