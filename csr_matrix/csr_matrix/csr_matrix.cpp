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
	row_ptr = new int[rowPtrLen];
	std::memcpy(row_ptr, &rptr[0], rowPtrLen*sizeof(int));

	input.close();
}

// preallocate relevant arrays
void CSRMatrix::initializeArrays(int r, int c, int nz)
{
	// set class attribs
	rows = r; cols = c; nnz = nz;

	val = new int[nnz];
	col_ind = new int[nnz];
}

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

// TODO: define destructor, free up alloc'ed memory
// define copy constructor, operator=


