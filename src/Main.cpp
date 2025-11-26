#include <iostream>
#include "Menu.h"
#include "Matrix.h"

using namespace std;

void printMatrix(vector<vector<double>>& mat)
{
    cout << "\n Result Matrix: \n";
    for (const auto& row : mat)
    {
        for (int val : row)
        {
            cout << BOLD_BLUE << val << " " ;
        }
        cout << "\n";
    }
    cout << RESET;
}
int main()
{
    Menu menu;
    menu.Display();
    int op = menu.getOption();

    Matrix matrix;

    switch (op)
    {
    case 1:
    {
        cout << "Matrix Addition Selected.\n";
        auto res = matrix.addition();
        printMatrix(res);
        break;
    }

    case 2:
    {
        cout << "Matrix Subtraction Selected.\n";
        auto res = matrix.subtraction();
        printMatrix(res);
        break;
    }

    case 3:
    {
        cout << "Scalar Multiplication Selected.\n";
        auto res = matrix.scalarMultiplication();
        printMatrix(res);
        break;
    }

    case 4:
    {
        cout << "Matrix Multiplication Selected.\n";
        auto res = matrix.multiplication();
        printMatrix(res);
        break;
    }

    case 5:
    {
        cout << "Trace Selected.\n";
        auto res = matrix.trace();
        cout << "Trace = " << res << "\n";
        break;
    }

    case 6:
    {
        cout << "Transpose Selected.\n";
        auto res = matrix.transpose();
        printMatrix(res);
        break;
    }

    case 7:
    {
        cout << "Determinant Selected.\n";
        auto res = matrix.determinant();
        cout << "Determinant = " << res << "\n";
        break;
    }
    case 8:
    {
        cout << "Matrix Power Selected.\n";
        auto res = matrix.Matrix_power();
        printMatrix(res);
        break;
	}
    default:
        cout << "Invalid Option.\n";
        break;
    }

    return 0;
}
