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
        throw runtime_error("Matrix 1 row's must be equal matrix 2 colum's");
    }
    Matrix res(rows, matrix2.getCols()); // rows * cols  r2 * c2 --> rows * c2

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
    Matrix result(cols, rows); 
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.matrix[j][i] = matrix[i][j];

    return result;
}

// ========================================================

//Matrix Matrix::U_Matrix()



pair<Matrix, Matrix> Matrix::LU()
{
    if (rows != cols)
    {
        throw runtime_error("LU Factorization requires a square matrix.");
    }
    Matrix l_Matrix(rows, cols);
    Matrix u_Matrix = *this;
    for (int i = 0; i < rows; i++)
    {
        l_Matrix.matrix[i][i] = 1;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = i + 1; j < cols; j++)
        {
            l_Matrix.matrix[i][j] = 0;
        }
    }
    for (int k = 0; k < rows - 1; k++)
    {
        if (u_Matrix.matrix[k][k] == 0)
            throw runtime_error("Zero pivot encountered. Pivoting required.");

        for (int i = k + 1; i < rows; i++)
        {
            double factor = u_Matrix.matrix[i][k] / u_Matrix.matrix[k][k];
            l_Matrix.matrix[i][k] = factor;

            for (int j = k; j < rows; j++)
            {
                u_Matrix.matrix[i][j] -= factor * u_Matrix.matrix[k][j];
            }
        }
    }

    return { l_Matrix,  u_Matrix };

}
// ========================================================

 
Matrix Matrix::Matrix_power(int power)  
{
    if (rows != cols)
    {
       throw runtime_error("Matrix must be square for power operation.");
    }
    if (power < 0)
    {
        throw runtime_error("Negative powers not supported.");
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
        throw runtime_error( "Matrix must be square for trace.");
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
        throw runtime_error("Matrix must be square for determinant.");
    }
    if (rows == 2)
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    auto [L, U] = this->LU();
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
        throw runtime_error("Matrices munst be same dimensions.");
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
        throw runtime_error ("Matrices munst be same dimensions.") ;
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
