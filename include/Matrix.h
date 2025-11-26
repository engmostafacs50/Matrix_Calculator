#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "utility/Colors.h"
using namespace std;
class Matrix
{
private:
    vector<vector<double>> matrixA;
    vector<vector<double>> matrixB;
    int rowsA = 0, colsA = 0;
    int rowsB = 0, colsB = 0;
    void inputMatrix(vector<vector<double>>& matrix, int& rows, int& cols, const string& name);

public:
    vector<vector<double>> addition();
    vector<vector<double>> subtraction();
    vector<vector<double>> scalarMultiplication();
    vector<vector<double>> multiplication();
    vector<vector<double>> transpose();
    vector<vector<double>> LU_Factorization(); 
    vector<vector<double>> Matrix_power() ; 

     
    double trace();    
    double determinant();
};
