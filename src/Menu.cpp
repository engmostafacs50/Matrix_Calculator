#include <iostream>
#include "Menu.h"
#include "utility/colors.h"
using namespace std;

void Menu::DisplayMain() {
    cout << BOLD_CYAN << "\n==============================\n";
    cout << "          Main Menu            \n";
    cout << "=====================================\n" << RESET;

    cout << GREEN << "1. Matrix Operations\n" << RESET;
    cout << GREEN << "2. Linear Systems\n" << RESET;
    cout << GREEN << "3. Vector Operations\n" << RESET;
    cout << RED << "0. Exit\n" << RESET;

    cout << BOLD_BLUE << "================================================\n" << RESET;
    cout << BOLD_WHITE << "Enter your choice: " << RESET;
}

void Menu::DisplayMatrixMenu() {
    cout << BOLD_BLUE << "\n--- Matrix Operations ---\n" << RESET;
    cout << "1. Add Matrices\n";
    cout << "2. Subtract Matrices\n";
    cout << "3. Scalar Multiplication\n";
    cout << "4. Multiply Matrices\n";
    cout << "5. Trace\n";
    cout << "6. Transpose\n";
    cout << "7. Determinant\n";
    cout << "8. Matrix Power\n";
    cout << "9. LU Factorization\n";
    cout << "10. REF\n";
    cout << "11. RREF\n";
    cout << "12. Rank of matrix\n";
    cout << "13. Inverse of matrix\n";
    cout << "14. Symmetric check\n";
    cout << "0. Back to Main Menu\n";
}

void Menu::DisplayLinearMenu() {
    cout << BOLD_BLUE << "\n--- Linear Systems ---\n" << RESET;
    cout << "1. Homogenous System \n";
    cout << "2. Non Homogenous System \n";
    cout << "0. Back to Main Menu\n";
}

void Menu::DisplayVectorMenu() {
    cout << BOLD_BLUE << "\n--- Vector Operations ---\n" << RESET;
    cout << "1. Vector Addition\n";
    cout << "2. Vector Subtraction\n"; 
    cout << "3. Dot Product\n";
    cout << "4. Cross Product\n";
    cout << "5. Scalar Multiplication\n";
    cout << "6. Norm or Magnitude\n";
    cout << "0. Back to Main Menu\n";
}

int Menu::getOption() {
    int choice;
    cin >> choice;
    return choice;
}