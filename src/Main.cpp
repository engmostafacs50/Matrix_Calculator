#include <iostream>
#include "Menu.h"
#include "Matrix.h"
#include "utility/colors.h"
using namespace std;

Matrix inputMatrixFromUser(const string& name) {
    int r, c;
    cout << BOLD_YELLOW <<  "Enter rows for Matrix " << name << ": " << RESET;
    cin >> r;
    cout << BOLD_YELLOW << "Enter columns for Matrix " << name << ": " << RESET;
    cin >> c;

    vector<vector<double>> nums(r, vector<double>(c));

    cout << GREEN << "Enter elements for Matrix " << name << ":\n" << BLUE ;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> nums[i][j];
        }
    }
    cout << RESET << endl; 

    return Matrix(nums);
}


void printMatrix(const vector<vector<double>>& mat) {
    cout << BOLD_BLUE << "\nResult Matrix:\n" << RESET;
    for (const auto& row : mat) 
    {
        for (double val : row)
        {
            cout << BOLD_BLUE << val << " " << RESET;
        }

        cout << "\n";
    }

    cout << RESET;
}


int main()
{
    while (true)   // LOOP start
    {
        Menu menu;
        menu.Display();
        int op = menu.getOption();

        if (op == 0) {
            cout << GREEN << "Exiting program...\n" << RESET;
            break;
        }

        Matrix A, B;
        bool needSecond = (op == 1 || op == 2 || op == 4);

        A = inputMatrixFromUser("A");
        if (needSecond)
            B = inputMatrixFromUser("B");

        try {
            switch (op) {

            case 1:
                printMatrix(A.addition(B).getMAtrix());
                break;

            case 2:
                printMatrix(A.subtraction(B).getMAtrix());
                break;

            case 3: {
                double scalar;
                cout << "Enter scalar: ";
                cin >> scalar;
                printMatrix(A.scalarMultiplication(scalar).getMAtrix());
                break;
            }

            case 4:
                printMatrix(A.multiplication(B).getMAtrix());
                break;

            case 5:
                cout << "Trace = " << A.trace() << "\n";
                break;

            case 6:
                printMatrix(A.transpose().getMAtrix());
                break;

            case 7:
                cout << "Determinant = " << A.determinant() << "\n";
                break;

            case 8: {
                int p;
                cout << "Enter power: ";
                cin >> p;
                printMatrix(A.Matrix_power(p).getMAtrix());
                break;
            }

            case 9: {
                auto [L, U] = A.LU();
                cout << BOLD_GREEN << "\nL Matrix:\n" << RESET;
                printMatrix(L.getMAtrix());
                cout << BOLD_GREEN << "\nU Matrix:\n" << RESET;
                printMatrix(U.getMAtrix());
                break;
            }

            default:
                cout << RED << "Invalid Option\n" << RESET;
            }

        }
        catch (const exception& e) {
            cout << RED << "Error: " << e.what() << "\n" << RESET;
        }

        cout << BOLD_YELLOW << "\nPress ENTER to continue..." << RESET;
        cin.ignore();
        cin.get();     
    }

    return 0;
}


