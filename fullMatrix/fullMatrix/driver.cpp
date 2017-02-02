#include "matrix.h"
#include <iostream>

int main()
{
	Matrix A("matrixA.txt");
	A.print();

	Matrix B("matrixB.txt");
	B.print();

	std::cout << "Multiplying the two matrix..." << std::endl;
	// check the multiplied matrix
	(A.mult(B)).print();

	return 0;
}
