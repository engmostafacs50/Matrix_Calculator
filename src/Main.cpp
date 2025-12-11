#include <iostream>
#include "Menu.h"
#include "Matrix.h"
#include "utility/colors.h"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "LinearSystem.h"
#include <optional>
using namespace std;
Matrix inputMatrixFromUser(const string& name)
{
    int r, c;
    cout << BOLD_YELLOW << "Enter rows for Matrix " << name << ": " << RESET;
    cin >> r;
    cout << BOLD_YELLOW << "Enter columns for Matrix " << name << ": " << RESET;
    cin >> c;

    vector<vector<double>> nums(r, vector<double>(c));

    cout << GREEN << "Enter elements for Matrix " << name << ":\n" << BLUE;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> nums[i][j];
        }
    }
    cout << RESET << endl;

    return Matrix(nums);
}
void printMatrix(const vector<vector<double>>& mat)
{
    cout << BOLD_BLUE << "\nResult Matrix:\n" << RESET;
    for (const auto& row : mat) {
        for (double val : row) {
            cout << BOLD_BLUE << val << " " << RESET;
        }
        cout << "\n";
    }
    cout << RESET;
}
Vector inputVectorFromUser(const string& name)
{
    int dim;
    cout << BOLD_YELLOW << "Enter dimension of Vector " << name << " (1, 2, or 3): " << RESET;
    cin >> dim;
    if (dim < 1 || dim > 3)
        throw runtime_error("Dimension must be 1, 2 or 3.");

    vector<double> vals(dim);
    cout << GREEN << "Enter elements for Vector " << name << ":\n" << RESET;
    for (int i = 0; i < dim; i++) {
        cin >> vals[i];
    }

    return Vector(vals);
}

void printVector(const Vector& v)
{
    cout << BOLD_BLUE << "Result Vector: " << RESET;
    cout << "( ";
    for (int i = 0; i < v.getdim(); i++)
    {
        cout << v.values[i] << " ";
    }
    cout << ")";
}
void clearScreen()
{
    cout << "\nPress ENTER to continue..." << RESET;
    cin.ignore();
    cin.get();
    system("CLS");
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Menu menu;

    while (true) {
        menu.DisplayMain();
        int section = menu.getOption();

        if (section == 0) {
            cout << GREEN << "Exiting program...\n" << RESET;
            break;
        }

        try {
            if (section == 1) {
                // Matrix Operations
                while (true) {
                    menu.DisplayMatrixMenu();
                    int op = menu.getOption();
                    if (op == 0) break;

                    Matrix A, B;
                    switch (op) {
                    case 1: {
                        A = inputMatrixFromUser("A");
                        B = inputMatrixFromUser("B");
                        printMatrix(A.addition(B).getMAtrix());
                        clearScreen();
                        break;
                    }
                    case 2: {
                        A = inputMatrixFromUser("A");
                        B = inputMatrixFromUser("B");
                        printMatrix(A.subtraction(B).getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    
                    case 3: 
                    {
                        A = inputMatrixFromUser("A"); 
                        double scalar;
                        cout << "Enter scalar: "; cin >> scalar;
                        printMatrix(A.scalarMultiplication(scalar).getMAtrix()); 
                        clearScreen();
                        break;
                    }
                       
                   
                    case 4:{
                        A = inputMatrixFromUser("A");
                        B = inputMatrixFromUser("B");
                        printMatrix(A.multiplication(B).getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    case 5: {
                        A = inputMatrixFromUser("A");
                        cout << "Trace = " << A.trace() << "\n";
                        break;
                    }
                    case 6: {
                        A = inputMatrixFromUser("A");
                        printMatrix(A.transpose().getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    case 7: {
                        A = inputMatrixFromUser("A");
                        cout << "Determinant = " << A.determinant() << "\n";
                        clearScreen();
                        break;
                    }
                    case 8: 
                    {
                        A = inputMatrixFromUser("A"); int p;
                        cout << "Enter power: "; cin >> p;
                        printMatrix(A.Matrix_power(p).getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    case 9:
                    {
                        A = inputMatrixFromUser("A"); auto [L, U] = A.LU();
                        cout << "L Matrix:\n"; printMatrix(L.getMAtrix());
                        cout << "U Matrix:\n";printMatrix(U.getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    case 10: 
                    {
                        A = inputMatrixFromUser("A");
                        printMatrix(A.REF().first.getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    case 11:
                    {
                        A =inputMatrixFromUser("A");
                        printMatrix(A.RREF().first.getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    case 12:
                    {
                        A = inputMatrixFromUser("A");
                        cout << "Rank = " << A.Rank(); 
                        clearScreen();
                        break;
                    }
                    case 13: 
                    {
                        A = inputMatrixFromUser("A");
                        printMatrix(A.Inverse().getMAtrix()); 
                        clearScreen();
                        break;
                    }
                    case 14: 
                    {
                        A = inputMatrixFromUser("A");
                        cout << A.SYmmetricChecking(); 
                        clearScreen();
                        break;
                    }
                    default:
                    {
                        cout << RED << "Invalid Option\n" << RESET;
                    }
                    }
                }
            }
            else if (section == 2) {
                // Linear Systems
                while (true) {
                    menu.DisplayLinearMenu();
                    int op = menu.getOption();
                    if (op == 0) break;

                    int eq, var;
                    cout << "Enter number of equations: "; cin >> eq;
                    cout << "Enter number of variables: "; cin >> var;

                    if (op == 1) {
                        Homogenous_System H(eq, var);
                        H.input_from_user();
                        H.Solve();
                        clearScreen();
                    }
                    else if (op == 2) {
                        Non_Homogenous_System N_H(eq, var);
                        N_H.input_from_user();
                        N_H.Solve();
                        clearScreen();
                    }
                    else {
                        cout << RED << "Invalid Option\n" << RESET;
                    }
                }
            }
            else if (section == 3) {
                // Vector Operations
                while (true) {
                    menu.DisplayVectorMenu();
                    int op = menu.getOption();
                    switch (op) 
                    {
                        case 0: 
                        {
                            break; 
                        }
                        case 1:
                        {
                            Vector A = inputVectorFromUser("A"); 
                            Vector B = inputVectorFromUser("B"); 
                            printVector(A.add(B));
                            clearScreen();
                            break;
                        }
                        case 2:
                        {
                            Vector A = inputVectorFromUser("A");
                            Vector B = inputVectorFromUser("B");
                            printVector(A.subtract(B));
                            clearScreen();
                            break;
                        }
                        case 3:
                        {
                            Vector A = inputVectorFromUser("A");
                            Vector B = inputVectorFromUser("B");
                            cout << "A . B = " << A.dot(B);
                            clearScreen();
                            break;
                        }
                        case 4 : 
                        {
                            Vector A = inputVectorFromUser("A");
                            Vector B = inputVectorFromUser("B");
                            printVector(A.cross(B)); 
                            clearScreen();
                            break; 
                        }
                        case 5 : 
                        {
                            Vector A = inputVectorFromUser("A");
                            cout << YELLOW << "Enter scalar : " << RESET; 
                            double scalar; cin >> scalar;
                            Vector Res = A.scalarMultiply(scalar); 
                            printVector(Res);
                            clearScreen();
                            break; 
                        }
                        case 6:
                        {
                            Vector A = inputVectorFromUser("A");
                            cout << "| A | = " << A.norm(); 
                            clearScreen();
                            break;
                        }
                    }
                    
                }
            }
            else {
                cout << RED << "Invalid Section\n" << RESET;
            }
        }
        catch (const exception& e) {
            cout << RED << "Error: " << e.what() << "\n" << RESET;
        }

        cout << BOLD_YELLOW << "\nPress ENTER to continue..." << RESET;
        cin.ignore();
        cin.get();
    }

    return 0;
}