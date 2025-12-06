#pragma once
#include<iostream>
#include"Matrix.h"
using namespace std;

/*
			Non Homogenous System
1) Rank[A|B]

2)
If Rank[A|B] != Rank [A] --> No solution

If Rank[A|B] = Rank[A] -> there are two cases in this case 

case one --> number of variables = Rank[A] -> Unique Solution
case two --> number of variables > Rank[A] -> Infinity Solution
*/

/*
			Homogenous System 

1) Rank[A] -> thaere are Two Cases in  this case

case one --> (Rank[A] = number of variables) -> trial solution
case one --> (Rank[A] < number of variables) -> Infinity Solution
*/
