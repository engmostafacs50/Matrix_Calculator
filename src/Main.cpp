#include <iostream>
#include "Menu.h"
#include "Matrix.h"
#include "utility/colors.h"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "LinearSystem.h"
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
    while (true)   
    {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        Menu menu;
        menu.Display();
        int op = menu.getOption();

        if (op == 0) {
            cout << GREEN << "Exiting program...\n" << RESET;
            break;
        }

        Matrix A, B;

        try {
            switch (op) 
            {

            case 1:
                A = inputMatrixFromUser("A");
                B = inputMatrixFromUser("B");
                printMatrix(A.addition(B).getMAtrix());
                break;

            case 2:
               A = inputMatrixFromUser("A");
                B = inputMatrixFromUser("B");
                printMatrix(A.subtraction(B).getMAtrix());
                break;

            case 3: {
                A = inputMatrixFromUser("A");
                double scalar;
                cout << "Enter scalar: ";
                cin >> scalar;
                printMatrix(A.scalarMultiplication(scalar).getMAtrix());
                break;
            }

            case 4:
                A = inputMatrixFromUser("A");
                B = inputMatrixFromUser("B");
                printMatrix(A.multiplication(B).getMAtrix());
                break;

            case 5:
                A = inputMatrixFromUser("A");
                cout << "Trace = " << A.trace() << "\n";
                break;

            case 6:
                A = inputMatrixFromUser("A");
                printMatrix(A.transpose().getMAtrix());
                break;

            case 7:
                A = inputMatrixFromUser("A");
                cout << "Determinant = " << A.determinant() << "\n";
                break;

            case 8: {
                A = inputMatrixFromUser("A");
                int p;
                cout << "Enter power: ";
                cin >> p;
                printMatrix(A.Matrix_power(p).getMAtrix());
                break;
            }

            case 9: {
                A = inputMatrixFromUser("A");
                auto [L, U] = A.LU();
                cout << BOLD_GREEN << "\nL Matrix:\n" << RESET;
                printMatrix(L.getMAtrix());
                cout << BOLD_GREEN << "\nU Matrix:\n" << RESET;
                printMatrix(U.getMAtrix());
                break;
            }
            case 10: {
                A = inputMatrixFromUser("A");
                printMatrix(A.REF().first.getMAtrix());
                break; 
            }
            case 11 : 
            {
                A = inputMatrixFromUser("A");
                printMatrix(A.RREF().first.getMAtrix());
                break; 
            }
            case 12 :
            {
                A = inputMatrixFromUser("A");
                cout << "Rank = " << A.Rank(); 
                break; 
            }
            case 13: {
                A = inputMatrixFromUser("A");
                printMatrix(A.Inverse().getMAtrix()); 
                break; 
            }
            case 14: {
                int eq, var;
                cout << "Enter number of equations: ";
                cin >> eq;
                cout << "Enter number of variables: ";
                cin >> var;

                Homogenous_System H(eq, var);

                H.input_from_user();
                H.Solve();

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