#pragma once
#include<iostream>
#include"Matrix.h"
#include "utility/Colors.h"
using namespace std;

class Linear_System {
protected:
    int N_Variables;
    int N_Equations;
    Matrix A;
    Matrix B;

public:
    Linear_System(int N_Eq, int N_Var);
    virtual ~Linear_System() = default;
    virtual void input_from_user() = 0;
    virtual void Solve() = 0;
};

class Homogenous_System : public Linear_System {
public:
    Homogenous_System(int N_Eq, int N_Var);

    void input_from_user() override;
    void Solve() override;
};

class Non_Homogenous_System : public Linear_System {
public:
    Non_Homogenous_System(int N_Eq, int N_Var);

    void input_from_user() override;
    void Solve() override;
};

