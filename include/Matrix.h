#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "utility/Colors.h"
#include<utility>
#include<algorithm>

using namespace std;
class Matrix
{
private:
    vector<vector<double>> matrix;
    //vector<vector<double>> matrixB;
    int rows = 0, cols = 0;
    //void inputMatrix(vector<vector<double>>& matrix, int& rows, int& cols, const string& name);

public:
    
    Matrix(int r, int c);
    Matrix(const vector<vector<double>>& d);
    Matrix() : rows(0), cols(0), matrix{} 
    {
    }


    const vector<vector<double>>& getMAtrix() const;
    int getRows() const;
    int getCols() const;


    Matrix addition(Matrix &matrix2) ;
    Matrix subtraction(Matrix& matrix2) ;
    Matrix scalarMultiplication(double scalar) ;
    Matrix multiplication(Matrix& matrix2)  ;
    Matrix transpose()  ;
    Matrix Matrix_power(int power) ;
    Matrix REF(); 
    Matrix RREF();
    pair<Matrix, Matrix> LU();
    pair<Matrix, int> MoveZeroRow(Matrix mat);
    double trace()  const;    
    double determinant() ;
    int Rank(); 
    void swapRows(Matrix& maTrix, int r1, int r2);
    bool checkPivot(Matrix& maTrix, int k);
    int findBestPivot(const Matrix& maTrix, int k);
    
};
