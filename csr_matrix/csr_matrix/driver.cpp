#include <iostream>

#include "csr_matrix.h"

int main()
{
	CSRMatrix csm("exampleA.txt");
	csm.printSparseFormat();
	csm.printMatrix();

	CSRMatrix c;
	c = csm;
	std::cout << "c is" << std::endl;
	c.printMatrix();

	std::cout << "csm is" << std::endl;
	csm.printMatrix();
	return 0;
}
