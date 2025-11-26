#include <iostream>
#include "Menu.h"
#include "utility/colors.h"
using namespace std;

void Menu::Display()  {
    cout << BOLD_CYAN << "\n=============== Matrix Calculator ===============\n" << RESET;
    cout << GREEN << "1. Add Matrices\n" << RESET;
	cout << GREEN << "2. Subtract Matrices\n" << RESET;
	cout << GREEN << "3. Scalar Multiplication\n" << RESET;
	cout << GREEN << "4. Multiply Matrices\n" << RESET;
	cout << GREEN << "5. Trace\n" << RESET;
	cout << GREEN << "6. Transpose\n" << RESET;
	cout << GREEN << "7. Determinant\n" << RESET;
	cout << GREEN << "8. Matrix Power\n" << RESET;
	/*cout << GREEN << "9. LU Factrization\n" << RESET; */
	cout << RED << "0. Exit\n" << RESET;  
    cout << BOLD_BLUE << "================================================\n" << RESET;
    cout << BOLD_WHITE << "Enter your choice: " << RESET;
}
int Menu::getOption() 
{   int choice;
    cin >> choice;
    return choice;
}
