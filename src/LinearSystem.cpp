#include "LinearSystem.h"

Linear_System::Linear_System(int N_Eq, int N_Var) : N_Variables(N_Var) , N_Equations(N_Eq) ,A(N_Var , N_Eq){}

int Linear_System::Get_N_Variables() const
{
	return N_Variables;
}

int Linear_System::Get_N_Equations() const
{
	return N_Equations;
}

int Linear_System::Rank_A()
{
	A = A.RREF().first;
	return A.Rank(); 
}

int Linear_System::Rank_A__B()
{
	Matrix A__B = A.concatenate(B);
	A__B=A__B.RREF().first;
	return A__B.Rank(); 
}


Homogenous_System::Homogenous_System(int N_Eq, int N_Var)
	: Linear_System(N_Eq, N_Var)
{}

void Homogenous_System::input_from_user()
{ 
	cout << "\n==============================================\n";
	cout << "Enter coefficients of A (Homogeneous System) : ";
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
	if (Rank_A() == N_Variables)
	{
		cout << CYAN <<"\nThis Linear has Tivial Solution --> X = 0 , ..\n" << RESET;
	}
	else if (Rank_A() < N_Variables)
	{
		cout << CYAN << "\nThis Linear has Infinity Solutions\n" << RESET;
	}
	//for (int i = 0; i < N_Variables; i++)
	//{
	//	for (int j = 0; j < N_Equations; j++)
	//	{
	//		cout << A.matrix[i][j] << " " ;
	//	}
	//	cout << endl; 
	//}
}
