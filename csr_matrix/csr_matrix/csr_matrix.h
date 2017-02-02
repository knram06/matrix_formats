#ifndef CSR_MATRIX
#define CSR_MATRIX

class CSRMatrix
{
private:
	int rows, cols;
	int nnz, rowPtrLen;
	int *val, *col_ind, *row_ptr;

	void initializeArrays(int r, int c, int nz);

public:
	CSRMatrix();

	// constructor that takes in filename to read and build
	// matrix from
	CSRMatrix(const char* filename);

	// print functions
	void printSparseFormat() const;
	void printMatrix() const;
};

#endif