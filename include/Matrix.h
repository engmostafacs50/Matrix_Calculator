#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "utility/Colors.h"
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstdlib> // for clear screen 
using namespace std;
class Matrix
{
private:
    
    //vector<vector<double>> matrixB;
    int rows = 0, cols = 0;
    //void inputMatrix(vector<vector<double>>& matrix, int& rows, int& cols, const string& name);

public:
    vector<vector<double>> matrix;
    Matrix(int r, int c);
    Matrix(const vector<vector<double>>& d);
    Matrix() : rows(0), cols(0), matrix{} 
    {
    }
    //=============================================================

    const vector<vector<double>>& getMAtrix() const;
    int getRows() const;
    int getCols() const;
    //=============================================================

    Matrix addition(Matrix &matrix2) ;
    Matrix subtraction(Matrix& matrix2) ;
    Matrix scalarMultiplication(double scalar) ;
    Matrix multiplication(Matrix& matrix2)  ;
    Matrix transpose()  ;
    Matrix Matrix_power(int power) ;
    pair <Matrix , Matrix> REF(); 
    pair<Matrix, Matrix> Matrix::RREF();
    pair<Matrix, Matrix> LU();
    pair<Matrix, int> MoveZeroRow(Matrix mat);
    Matrix Inverse(); 
    string SYmmetricChecking(); 
    double trace()  const;    
    double determinant() ;
    int Rank(); 
    void swapRows(Matrix& maTrix, int r1, int r2);
    bool checkPivot(Matrix& maTrix, int k);
    int findBestPivot(const Matrix& maTrix, int k);
    //=============================================================
    Matrix Identity_Matrix() {
        Matrix I = *this; 
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols;j++) 
            {
                if (i == j)
                    I.matrix[i][j] = 1;
                else                                 
                    I.matrix[i][j] = 0;
            }
        }
        return I; 
    };
    
    Matrix concatenate(const Matrix& other) const; // for linear system
};


class Vector {

private :
    int Dimensions;
    
public : 
    Vector(int dim); 
    Vector(double x, double y); // 2D vector
    Vector(double x, double y, double z); // 3D vector
    Vector(const vector<double>& v); // impotant for input from user 
    vector<double> values;
    //=============================================================
    int getdim() const; 

    Vector add(const Vector& other) const;
    Vector subtract(const Vector& other)const;
    Vector scalarMultiply(double scalar) const;
    double dot(const Vector& other) const;
    Vector cross(const Vector& other) const;
    double norm(); 

    //=============================================================
};