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


int main() {
    Menu menu;
    menu.Display();
    int op = menu.getOption();

    Matrix A, B;
    bool needSecond = (op == 1 || op == 2 || op == 4);
    A = inputMatrixFromUser("Matrix A");
    if (needSecond)
        B = inputMatrixFromUser("MAtrix B");

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

        case 9:
            printMatrix(A.LU_Factorization().getMAtrix());
            break;

        default:
            cout << "Invalid Option\n";
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}

