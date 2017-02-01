#include "matrix.h"
#include <iostream>

int main()
{
	std::ifstream input;
	Matrix A(input, "matrixA.txt");
	A.print();

	return 0;
}
