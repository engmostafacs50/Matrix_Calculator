#include "LinearSystem.h"


/*
			Non Homogenous System
1) Rank[A|B]

2)
If Rank[A|B] != Rank [A] --> No solution

If Rank[A|B] = Rank[A] -> there are two cases in this case

case one --> number of variables = Rank[A] -> Unique Solution
case two --> number of variables > Rank[A] -> Infinity Solution
*/

// =============================================================

/*
			  Homogenous System

1) Rank[A] -> thaere are Two Cases in  this case

case one --> (Rank[A] = number of variables) -> trial solution
case one --> (Rank[A] < number of variables) -> Infinity Solution
*/


Linear_System::Linear_System(int N_Eq, int N_Var) :
	N_Variables(N_Var) ,
	N_Equations(N_Eq) , 
	A(N_Eq, N_Var) , 
	B(N_Eq,1) {}


Homogenous_System::Homogenous_System(int N_Eq, int N_Var)
	: Linear_System(N_Eq, N_Var) {
}

void Homogenous_System::input_from_user()
{ 
	cout << "\n==============================================\n";
	cout << "Enter coefficients of A (Homogeneous System) : " ;
	cout << "\n==============================================\n";
	for (int i = 0; i < N_Equations; i++)
	{
		cout << "Eq" << i + 1 << ": ";
		for (int j = 0; j < N_Variables; j++)
		{
			cin >> A.matrix[i][j];
		}
	}
}

void Homogenous_System::Solve()
{
	A = A.RREF().first;
	if (A.Rank() == N_Variables)
	{
		cout << CYAN <<"\nThis Linear has Tivial Solution --> X = 0 , ..\n" << RESET;
	}
	else if (A.Rank() < N_Variables)
	{
		cout << CYAN << "\nThis Linear has Infinity Solutions\n" << RESET;
	}
	for (int i = 0; i < N_Equations; i++)
	{
		for (int j = 0; j < N_Variables; j++)
		{
			cout << A.matrix[i][j] << " " ;
		}
		cout << endl; 
	}
}


Non_Homogenous_System::Non_Homogenous_System(int N_Eq, int N_Var)
	: Linear_System(N_Eq, N_Var){}

void Non_Homogenous_System::input_from_user()
{
	cout << "\n==============================================\n";
	cout << "Enter coefficients of A (Non Homogeneous System) : ";
	cout << "\n==============================================\n";
	for (int i = 0; i < N_Equations; i++)
	{
		cout << "Eq" << i + 1 << ": ";
		for (int j = 0; j < N_Variables; j++)
		{
			cin >> A.matrix[i][j];
		}
		cout << "\n enter number after = : "; 
		cin >> B.matrix[i][0] ;
	}
}

void Non_Homogenous_System::Solve()
{
	Matrix A__B = A.concatenate(B); 
	A__B = A__B.RREF().first; 
	cout << "A | B : \n\n "; 
	for (int i = 0; i < A__B.getRows(); i++)
	{
		for (int j = 0; j < A__B.getCols(); j++)
		{
			cout << A__B.matrix[i][j] <<" ";
		}
		cout << endl; 
	}
	cout << "\n ======================\n"; 
	if (A__B.Rank() != A.Rank())
	{
		cout << RED << "This Linear System don't have solution \n" << RESET; 
	}
	else if (A__B.Rank() == A.Rank())
	{
		if (A.Rank() < N_Variables)
		{
			cout << CYAN << "\nThis Linear has Infinity Solutions\n" << RESET;
		}
		else
		{
			cout << CYAN << "\nThis Linear has Unique Solution : \n" << RESET;
			// Finding This Solution 
			for (int i = 0; i < A__B.getRows();i++)
			{
				cout << "X" << i+1 << " = " << A__B.matrix[i][A__B.getCols() - 1] << endl ;
 			}
		}
	}
	cout << "Rank(A|B) ->" << A__B.Rank() << " Rank(A) ->" << A.Rank() << endl;
}
