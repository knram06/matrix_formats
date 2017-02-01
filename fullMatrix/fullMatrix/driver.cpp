#include "matrix.h"
#include <iostream>

int main()
{
	std::ifstream input;
	Matrix A(input, "matrixA.txt");
	A.print();

	Matrix B(input, "matrixB.txt");
	B.print();

	std::cout << "Multiplying the two matrix..." << std::endl;
	// check the multiplied matrix
	(A.mult(B)).print();

	return 0;
}
