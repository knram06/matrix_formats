#ifndef CSR_MATRIX
#define CSR_MATRIX

#include <algorithm>
#include <vector>

class CSRMatrix
{
private:
	int rows, cols;
	//int nnz, rowPtrLen;
	//int *val, *col_ind, *row_ptr;
	std::vector<double> val;
	std::vector<int> col_ind, row_ptr;

	void initializeArrays(int r, int c, int nz);

public:
	CSRMatrix();

	// constructor that takes in filename to read and build
	// matrix from
	CSRMatrix(std:string& filename);

	// copy constructor
	CSRMatrix(const CSRMatrix& csm);

	// operators
	CSRMatrix& CSRMatrix::operator=(CSRMatrix csm)
	{
	    swap(*this, csm);
	    return (*this);
    }

	// for copy-and-swap idiom
	void swap(CSRMatrix& a, CSRMatrix& b)
	{
		using std::swap;

		// swap members
		swap(a.rows, b.rows);
		swap(a.cols, b.cols);
		swap(a.nnz,  b.nnz);
		swap(a.rowPtrLen, b.rowPtrLen);

		// swap array pointers
		swap(a.val, b.val);
		swap(a.col_ind, b.col_ind);
		swap(a.row_ptr, b.row_ptr);
	}

	// access functions
	int getElement(int row, int col) const;

	// matrix funcs
	CSRMatrix mult(const CSRMatrix& b);
	std::vector<int> mult(const std::vector<int>& v);
	//CSRMatrix transpose() const;

	// print functions
	void printSparseFormat() const;
	void printMatrix() const;

	// destructor
	~CSRMatrix();
};

#endif