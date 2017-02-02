#include <iostream>

#include "csr_matrix.h"

int main()
{
	CSRMatrix csm("exampleA.txt");
	csm.printSparseFormat();

	return 0;
}
