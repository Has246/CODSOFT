#include<iostream>
using namespace std;

class Calculator {
private:

    double num1;
    double num2;

public:

   void Set_Detail()
    {

        cout << "Enter First Number: ";
        cin >> num1;
        cout << "Enter Second Number: ";
        cin >> num2;
    }

    double Add_Number()const
    {
        return num1 + num2;
    }

    double Subtract_Number()const
    {
        return num1 - num2;
    }

    double Multiply_Number()const
    {
        return num1 * num2;
    }

    double Division()const {
        if (num2 == 0) {
            cout << "Error: Cannot divide by zero." << endl;
            return 0;
        }
        return num1 / num2;
    }
};

int main()
{
    Calculator obj{};
    double Add, Subtract, Multiply, Division;
    int choice;
    do
    {
        cout << "\n1. Addition. " << endl;
        cout << "2. Subtraction. " << endl;
        cout << "3. Multiplication. " << endl;
        cout << "4. Division. " << endl;
        cout << "5. Exit. " << endl;

        cout << "Enter your choice: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            obj.Set_Detail();
            Add = obj.Add_Number();
            cout << "The Addition of two numbers is: " << Add << endl;
            break;
        case 2:
            obj.Set_Detail();
            Subtract = obj.Subtract_Number();
            cout << "The Subtraction of two numbers is: " << Subtract << endl;
            break;
        case 3:
            obj.Set_Detail();
            Multiply = obj.Multiply_Number();
            cout << "The Multiplication of two numbers is: " << Multiply << endl;
            break;
        case 4:
            obj.Set_Detail();
            Division = obj.Division();
            cout << "The division of two numbers is: " << Division << endl;
            break;
        case 5:
            cout << "Thank You. ";
            break;
        default:
            cout << "Invalid Choice. ";
        }
    } while (choice != 5);
}