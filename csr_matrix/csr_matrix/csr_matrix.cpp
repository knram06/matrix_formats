#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "csr_matrix.h"

// default contructor
CSRMatrix::CSRMatrix() : rows(0), cols(0), nnz(0), rowPtrLen(0), col_ind(NULL), val(NULL), row_ptr(NULL) {};

// constructor that takes in filename
// file is expected to have 1st line as (row, col, nnz)
// and followed by 'row' lines with 'col' values, space separated, in dense form
// Parses this and stores in CSR form
CSRMatrix::CSRMatrix(const char* filename)
{
	// assume filename is not NULL
	std::ifstream input(filename);  // opens for reading by default
	std::string line;

	std::getline(input, line);
	std::istringstream iss(line);

	// obtain the rows, cols, nnz
	iss >> rows;
	iss >> cols;
	iss >> nnz;

	// preallocate arrays based on nnz
	initializeArrays(rows, cols, nnz);

	// now read in rest of lines and form the CSR matrix
	// use a vector to build up row_ptr, since we don't know
	// before hand, what the size would be
	std::vector<int> rptr;
	int k = 0;

	for(int i = 0; i < rows; i++)
	{
		bool foundFirstNZ = false; // marker when 1st nz in a row is found
		std::getline(input, line);

		std::istringstream tmp(line);
		int num;
		int j = 0;
		while(tmp >> num)
		{
			if(num) // i.e. not 0
			{
				// check if this is the 1st nz for that row
				if(!foundFirstNZ)
				{
					rptr.push_back(k);
					foundFirstNZ = true; // set marker so that subseq does not trigger overwrite
				}

				col_ind[k] = j;
				val[k] = num;
				k++;
			} // if check for whether num exists
			j++;

		} // end of while
	} // end of for loop across rows

	// ensure some simple conditions are satisfied
	assert(k == nnz);

	// fill in the last entry in rptr
	rptr.push_back(nnz);

	// fill in row_ptr array related members and memcpy from vector
	rowPtrLen = rptr.size();
	row_ptr = new int[rowPtrLen]();
	std::copy(rptr.begin(), rptr.end(), row_ptr);

	input.close();
}

// preallocate relevant arrays
void CSRMatrix::initializeArrays(int r, int c, int nz)
{
	// set class attribs
	rows = r; cols = c; nnz = nz;

	val = new int[nnz]();
	col_ind = new int[nnz]();
}

// Copy Constructor
CSRMatrix::CSRMatrix(const CSRMatrix& csm)
{
	rows = csm.rows;
	cols = csm.rows;
	nnz  = csm.nnz;
	rowPtrLen = csm.rowPtrLen;

	// alloc memory
	initializeArrays(rows, cols, nnz);
	// copy over values
	std::copy(csm.val,     csm.val + nnz,     val);
	std::copy(csm.col_ind, csm.col_ind + nnz, col_ind);

	// alloc the rowPtr
	row_ptr = new int[rowPtrLen];
	std::copy(csm.row_ptr, csm.row_ptr + rowPtrLen, row_ptr);
}

// equality operator - using copy-and-swap idiom
// IMPORTANT - using pass-by-value to generate copy ON THE FLY
/*
CSRMatrix& CSRMatrix::operator=(const CSRMatrix csm)
{
	swap(*this, csm);
	return (*this);
}
*/

void CSRMatrix::printSparseFormat() const
{
	// print values
	std::cout << "val : ";
	for(int j = 0; j < nnz; j++)
		std::cout << val[j] << " ";
	std::cout << std::endl;

	// print cols
	std::cout << "col_ind : ";
	for(int j = 0; j < nnz; j++)
		std::cout << col_ind[j] << " ";
	std::cout << std::endl;

	// print rowPtr
	std::cout << "row_ptr : ";
	for(int j = 0; j < rowPtrLen; j++)
		std::cout << row_ptr[j] << " ";
	std::cout << std::endl;
}

// print the sparse matrix in dense form
void CSRMatrix::printMatrix() const
{
	std::cout << "rows: " << rows << ", cols: " << cols << std::endl;

	int k = 0;
	for(int i = 0; i < rowPtrLen-1; i++)
	{
		int startCol = 0;
		for(int j = row_ptr[i]; j < row_ptr[i+1]; j++)
		{
			while(startCol != col_ind[j])
			{
				std::cout << 0 << " ";
				startCol++;
			}
			std::cout << val[k] << " ";
			k++; startCol++;
		} // end of for loop in j, across cols in a row

		// print 0s for remaining length
		while(startCol <= (cols-1))
		{
			std::cout << 0 << " ";
			startCol++;
		} // end of while
		std::cout << std::endl;
	}
}

// destructor
CSRMatrix::~CSRMatrix()
{
	// free up allocated memory
	delete [] val;
	delete [] col_ind;
	delete [] row_ptr;
}



