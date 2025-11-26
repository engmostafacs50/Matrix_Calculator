#include "Matrix.h"

void Matrix::inputMatrix(vector<vector<double>>& matrix, int& rows, int& cols, const string& name)
{
    cout << BOLD_YELLOW << "Enter number of rows for " << name << ": " << RESET;
    cin >> rows;

    cout << BOLD_YELLOW << "Enter number of columns for " << name << ": " << RESET;
    cin >> cols;

    matrix.assign(rows, vector<double>(cols));

    cout << BOLD_YELLOW << "Enter elements of " << name << ":\n" << RESET;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            std::cin >> matrix[i][j];
}

vector<vector<double>> Matrix::addition()
{
    inputMatrix(matrixA, rowsA, colsA, "Matrix A");
    inputMatrix(matrixB, rowsB, colsB, "Matrix B");

    if (rowsA != rowsB || colsA != colsB)
    {
        cout << RED << "Error: Dimensions must be equal.\n" << RESET;
        return {};
    }

    vector<vector<double>> result(rowsA, vector<double>(colsA));

    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsA; ++j)
        {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }

    return result;
}

vector<vector<double>> Matrix::subtraction()
{
    inputMatrix(matrixA, rowsA, colsA, "Matrix A");
    inputMatrix(matrixB, rowsB, colsB, "Matrix B");

    if (rowsA != rowsB || colsA != colsB)
    {
        cout << RED << "Error: Dimensions must br equal.\n" << RESET;
        return {};
    }

    vector<vector<double>> result(rowsA,vector<double>(colsA));

    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsA; ++j)
            result[i][j] = matrixA[i][j] - matrixB[i][j];

    return result;
}

vector<vector<double>> Matrix::scalarMultiplication()
{
    inputMatrix(matrixA, rowsA, colsA, "Matrix A");

    cout << BOLD_YELLOW << "Enter scalar value: " << RESET;
    int scalar;
    cin >> scalar;

    vector<vector<double>> result(rowsA, vector<double>(colsA));

    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsA; ++j)
            result[i][j] = matrixA[i][j] * scalar;

    return result;
}

vector<vector<double>> Matrix::multiplication()
{
    inputMatrix(matrixA, rowsA, colsA, "Matrix A");
    inputMatrix(matrixB, rowsB, colsB, "Matrix B");

    if (colsA != rowsB)
    {
        std::cout << RED << "Error: Columns of A must equal rows of B.\n" << RESET;
        return {};
    }

    vector<vector<double>> result(rowsA, vector<double>(colsB, 0));

    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsB; ++j)
            for (int k = 0; k < colsA; ++k)
                result[i][j] += matrixA[i][k] * matrixB[k][j];

    return result;
}

double Matrix::trace()
{
    inputMatrix(matrixA, rowsA, colsA, "Matrix A");

    if (rowsA != colsA)
    {
        std::cout << RED << "Error: Matrix must be square.\n" << RESET;
        return 0;
    }

    long long sum = 0;
    for (int i = 0; i < rowsA; ++i)
        sum += matrixA[i][i];

    return sum;
}

vector<vector<double>> Matrix::transpose()
{
    inputMatrix(matrixA, rowsA, colsA, "Matrix A");

    vector<vector<double>> result(colsA, vector<double>(rowsA));

    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsA; ++j)
            result[j][i] = matrixA[i][j];

    return result;
}

double Matrix::determinant()
{
    inputMatrix(matrixA, rowsA, colsA, "Matrix A");

    if (rowsA != colsA)
    {
        cout << RED << "Error: Matrix must be square.\n" << RESET;
        return 0;
    }

    if (rowsA == 2)
    {
        double det =(matrixA[0][0] * matrixA[1][1]) -(matrixA[0][1] * matrixA[1][0]);
        return det;
    }
}
