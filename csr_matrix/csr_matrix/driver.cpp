#include <iostream>

#include "csr_matrix.h"

int main()
{
	CSRMatrix csm("exampleA.txt");
	csm.printSparseFormat();
	csm.printMatrix();

	return 0;
}
