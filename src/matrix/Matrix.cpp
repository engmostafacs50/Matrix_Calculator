////////////////////////////////////////////////////////////////////

#include "Matrix.h"


// ========================================================
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    matrix.assign(r, vector<double>(c, 0));
}
//========================================================
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
// =======================================================
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
void Matrix::swapRows(Matrix& maTrix, int r1, int r2)
{
    swap(maTrix.matrix[r1], maTrix.matrix[r2]);
}

//===========================================================================
bool Matrix::checkPivot(Matrix& maTrix, int k)
{
   return fabs(maTrix.matrix[k][k]) < 1e-12;
 
}

//======================================================================
int Matrix::findBestPivot(const Matrix& maTrix, int k)
{
    int bestRows = k;
    double bestPivot = abs(maTrix.matrix[k][k]);
    for (int i = k + 1; i < maTrix.getRows(); i++)
    {
        if (abs(maTrix.matrix[i][k]) > bestPivot)
        {
            bestRows = i;
            bestPivot = abs(maTrix.matrix[i][k]);
        }
    }
    return bestRows;
}

//=====================================================
pair<Matrix ,int> Matrix::MoveZeroRow(Matrix mat)
{
    int currentRow = 0;
    int r = 0;
    vector<vector<double>> newMatrix(rows, vector<double>(cols, 0));
    for (int i = 0; i < rows; i++)
    {
        bool ZeroRow = true;
        for (int j = 0; j < cols; j++)
        {
            if (fabs(mat.matrix[i][j]) > 1e-12)
            {
               ZeroRow = false;
               
                break;
            }
        }

        if (!ZeroRow)
        {
            newMatrix[currentRow] = mat.matrix[i];
            currentRow++;
            r++;
        }
    }
    mat.matrix = newMatrix;
    return {mat , r};
    
}
//===================================
Matrix Matrix::Inverse()
{
    auto result = this->RREF();
    double det = this->determinant(); 
    if (det == 0)
    {
        throw runtime_error("This matrix is singular and doesn't have an inverse");

    }
    Matrix Inverse_matrix = result.second;
    return Inverse_matrix;
}
//=====================================
string Matrix::SYmmetricChecking()
{
    Matrix A_t = this->transpose();
    Matrix mat = *this;
    if (rows != cols)
        throw runtime_error("must input square matrix");
    if (A_t.matrix == mat.matrix)
        return "Matrix is Symmetric"; 
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat.matrix[i][j] *= -1; 
        }
    }
    if(A_t.matrix == mat.matrix)
        return "Matrix is Skew Symmetric";

    return "No Symmetric and no Skew symmetric"; 
}

//==============================================
pair<Matrix, Matrix> Matrix::RREF()
{
    Matrix mat = this->REF().first;
    Matrix I_Matrix = this->REF().second;

    for (int i = rows - 1; i >= 0; i--)
    {
        int pivotColumn = -1;
        for (int j = 0; j < cols; j++)
        {
            if (fabs(mat.matrix[i][j]) > 1e-12)
            {
                pivotColumn = j;
                break;
            }
        }
        if (pivotColumn == -1) 
            continue;

        double PivotValue = mat.matrix[i][pivotColumn];
        for (int c = 0; c < cols; c++)
        {
            mat.matrix[i][c] /= PivotValue;
            I_Matrix.matrix[i][c] /= PivotValue;
        }
        for (int k = i - 1; k >= 0; k--)
        {
            double factor = mat.matrix[k][pivotColumn];
            for (int m = 0; m < cols; m++)
            {
                mat.matrix[k][m] -= factor * mat.matrix[i][m];
                I_Matrix.matrix[k][m] -= factor * I_Matrix.matrix[i][m];
            }
        }
    }
    return { mat, I_Matrix };
}

//========================================================
pair<Matrix, Matrix> Matrix::REF()
{
    Matrix mat = *this;
    Matrix I_Matrix = this->Identity_Matrix();
    int currentRow = 0;

    for (int k = 0; k < cols && currentRow < rows; k++)
    {
        if (checkPivot(mat, currentRow))
        {
            int bestRow = findBestPivot(mat, currentRow);
            if (bestRow != currentRow)
            {
                swapRows(mat, currentRow, bestRow);
                swapRows(I_Matrix, currentRow, bestRow);
            }
        }

        if (fabs(mat.matrix[currentRow][k]) < 1e-12)
            continue;

        for (int i = currentRow + 1; i < rows; i++)
        {
            double factor = mat.matrix[i][k] / mat.matrix[currentRow][k];
            for (int j = k; j < cols; j++)
            {
                mat.matrix[i][j] -= factor * mat.matrix[currentRow][j];
            }
            for (int j = 0; j < cols; j++)
            {
                I_Matrix.matrix[i][j] -= factor * I_Matrix.matrix[currentRow][j];
            }
        }
        currentRow++;
    }

    auto result = MoveZeroRow(mat);
    auto I = MoveZeroRow(I_Matrix);
    I_Matrix = I.first;
    mat = result.first;

    return { mat , I_Matrix };
}

//=========================================
int counter = 0;
pair<Matrix, Matrix> Matrix::LU()
{
    if (rows != cols)
    {
        throw runtime_error("LU Factorization requires a square matrix.");
    }
    Matrix l_Matrix(rows, cols);
    l_Matrix = this->Identity_Matrix();
    Matrix u_Matrix = *this;
    for (int k = 0; k < rows - 1; k++)
    {
        if (checkPivot(u_Matrix , k))
        {
            int bestRow = findBestPivot(u_Matrix, k);
            if (bestRow != k)
            {
                swapRows(u_Matrix, k, bestRow);
                counter++;
                for (int j = 0; j < k; j++)
                     swap(l_Matrix.matrix[k][j], l_Matrix.matrix[bestRow][j]);

            }
        }
        if (u_Matrix.matrix[k][k] == 0)
        {
            throw runtime_error("Pivot remains zero after pivoting. Matrix is singular.");
        }
        for (int i = k + 1; i < rows; i++)
        {
            double factor = u_Matrix.matrix[i][k] / u_Matrix.matrix[k][k];
            l_Matrix.matrix[i][k] = factor;

            for (int j = k; j < cols; j++)
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
    if (counter % 2 == 1)
        det = -1;
    for (int i = 0; i < rows; i++)
    {
        det *= U.matrix[i][i];
    }
    return det;
}

// =============================================
int Matrix::Rank()
{
    Matrix mat = this->RREF().first; 
    auto res = MoveZeroRow(mat);
    int Rank = res.second;
    return Rank;
}

//=====================================================================
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
//=============================================================
Matrix Matrix::concatenate(const Matrix& other) const
{
    if (this->rows != other.rows) {
        throw runtime_error("Cannot concatenate: row size mismatch.");
    }

    Matrix result(this->rows, this->cols + other.cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = this->matrix[i][j]; // coffecient of Variables
        }
        for (int j = 0; j < other.cols; j++) {
            result.matrix[i][cols + j] = other.matrix[i][j]; // numbers after (=)
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////

Vector::Vector(int dim)
{
    if (dim <= 3 && dim >= 1)
    {
        Dimensions = dim;
        values = vector<double>(dim, 0.0); 
    }
    else
    {
        throw invalid_argument("Dimentions should be in intreval [1 , 3]");
    }
}

Vector::Vector(double x, double y)
{
    Dimensions = 2;
    values = { x , y };
}

Vector::Vector(double x, double y, double z)
{
    Dimensions = 3;
    values = { x , y , z };
}
Vector::Vector(const vector<double>& v)
{
    if (v.size() < 1 || v.size() > 3)
        throw invalid_argument("Vector size must be 1, 2 or 3.");

    Dimensions = v.size();
    values = v;
}

int Vector::getdim() const
{
    return Dimensions;
}


// operations 

Vector Vector::add(const Vector& other) const
{
    Vector Res(this->Dimensions); 
    if (this->Dimensions != other.Dimensions)
        throw runtime_error("Dimensions must be equal."); 
    for (int i = 0; i < this->Dimensions;i++)
    {
        Res.values[i] = this->values[i] + other.values[i];
    }
    return Res; 
}

Vector Vector::subtract(const Vector& other) const
{
    Vector Res(this->Dimensions);
    if (this->Dimensions != other.Dimensions)
        throw runtime_error("Dimensions must be equal.");
    for (int i = 0; i < this->Dimensions;i++)
    {
        Res.values[i] = this->values[i] - other.values[i];
    }
    return Res;
}

Vector Vector::scalarMultiply(double scalar) const
{
    Vector Res(this->Dimensions);

    for (int i = 0; i < this->Dimensions; i++)
        Res.values[i] = scalar * this->values[i] ; 

    return Res;
}

double Vector::dot(const Vector& other) const
{
    double Res = 0;
    if (this->Dimensions != other.Dimensions)
        throw runtime_error("Dimensions must be equal.");

    for (int i = 0; i < this->Dimensions;i++)
    {
        Res += (this->values[i] * other.values[i]);
    }

    return Res; 
}

Vector Vector::cross(const Vector& other) const
{
    if (this->Dimensions != other.Dimensions)
        throw runtime_error("Dimensions must be equal.");

    if (this->Dimensions < 3)
        throw runtime_error("Dimensions must be equal three.");

   Vector Res(this->Dimensions); 

   Res.values[0] = (this->values[1] * other.values[2]) - (this->values[2] * other.values[1]); 
   Res.values[1] = ((this->values[0] * other.values[2]) - (this->values[2] * other.values[0])) * -1 ;
   Res.values[2] = (this->values[0] * other.values[1]) - (this->values[1] * other.values[0]);

   return Res; 
}

double Vector::norm()
{
    double Squared_sum = 0; 
    for (int i = 0; i < this->Dimensions; i++)
        Squared_sum += pow(this->values[i], 2); 

    return sqrt(Squared_sum);
}