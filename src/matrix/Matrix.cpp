#include "Matrix.h"
#include <stdexcept>
//void Matrix::inputMatrix(vector<vector<double>>& matrix, int& rows, int& cols, const string& name)
//{
//    cout << BOLD_YELLOW << "Enter number of rows for " << name << ": " << RESET;
//    cin >> rows;
//
//    cout << BOLD_YELLOW << "Enter number of columns for " << name << ": " << RESET;
//    cin >> cols;
//
//    matrix.assign(rows, vector<double>(cols));
//
//    cout << BOLD_YELLOW << "Enter elements of " << name << ":\n" << RESET;
//
//    for (int i = 0; i < rows; ++i)
//        for (int j = 0; j < cols; ++j)
//            std::cin >> matrix[i][j];
//}

// ========================================================
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    matrix.assign(r, vector<double>(c, 0));
}


Matrix::Matrix(const vector<vector<double>>& mat) {
    matrix = mat;
    rows = mat.size();                              // important for input from user 
    cols = mat[0].size();    
}

// ========================================================
const vector<vector<double>>& Matrix::getMAtrix() const
{
    return matrix;
}

// ========================================================
int Matrix::getRows() const
{
    return rows;
}
// ========================================================
int Matrix::getCols() const
{
    return cols;
}

// ========================================================

Matrix Matrix::scalarMultiplication(double scalar) 
{
    Matrix res(rows , cols); 
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    return res;
}

// ========================================================

Matrix Matrix::multiplication(Matrix& matrix2) 
{
    if (cols != matrix2.getRows())
    {
        cout << "Matrix 1 row's must be equal matrix 2 colum's";
    }
    Matrix res(rows, matrix2.getRows());

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < matrix2.getCols(); j++)
        {
            for (int k = 0; k < matrix2.getRows();k++)
            {
                res.matrix[i][j] += matrix[i][k] * matrix2.matrix[k][j];
            }
        }
    }

    return res; 
}

// ========================================================

Matrix Matrix::transpose() 
{
    Matrix result(rows, cols); 
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.matrix[j][i] = matrix[i][j];

    return result;
}

// ========================================================

Matrix Matrix::LU_Factorization() 
{
    Matrix U_Matrix = *this;
    for (int k = 0; k < rows - 1;k++)
    {
        for (int i = k + 1; i < rows; i++)
        {
            double factor = U_Matrix.matrix[i][k] / U_Matrix.matrix[k][k];
            for (int j = k; j < rows;j++)
            {
                U_Matrix.matrix[i][j] = (U_Matrix.matrix[i][j]) - (factor * U_Matrix.matrix[k][j]);
            }
        }
    }
    return U_Matrix;
}

// ========================================================

 
Matrix Matrix::Matrix_power(int power)  
{
    if (rows != cols)
    {
        cout << RED << "Matrix must be square for power operation." << RESET;    
    }
    if (power < 0)
    {
        cout << RED << "Negative powers not supported." << RESET; 
    }

    Matrix result(rows, cols);
    
    if (power == 0)
    {
        for (int i = 0; i < rows; i++)
        {
            result.matrix[i][i] = 1;
        }
        return result;
    } 
    if (power == 1)
    {
        return *this;
    }

    Matrix base = *this;
    for (int i = 0; i < power; i++)
    {
        result = result.multiplication(base);
    }

    return result;
}


// ========================================================


double Matrix::trace() const
{
    if (rows != cols)
        cout << RED << "Matrix must be square for trace." << RESET; 
    double sum = 0;
    for (int i = 0; i < rows; i++)
    {
        sum += matrix[i][i];
    }
    return sum;
}

//=============================================================

double Matrix::determinant() 
{
    if (rows != cols)
    {
        cout << RED << "Matrix must be square for determinant." << RESET;
    }
    if (rows == 2)
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    Matrix U = this->LU_Factorization();
    double det = 1;
    for (int i = 0; i < rows; i++)
    {
        det *= U.matrix[i][i];
    }
    return det;
}

//=======================================================================

Matrix Matrix::addition(Matrix& matrix2) 
{
    Matrix res(rows , cols); 
    if (rows != matrix2.getRows() || cols != matrix2.getCols())
    {
        cout << RED << "Matrices munst be same dimensions." << RESET;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
           res.matrix[i][j] = matrix[i][j] + matrix2.matrix[i][j];
        }
    }
    return res; 
}

// ================================================================

Matrix Matrix::subtraction(Matrix& matrix2)
{
    Matrix res(rows, cols);
    if (rows != matrix2.getRows() || cols != matrix2.getCols())
    {
        cout << RED << "Matrices munst be same dimensions." << RESET;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res.matrix[i][j] = matrix[i][j] - matrix2.matrix[i][j];
        }
    }
    return res;
}
