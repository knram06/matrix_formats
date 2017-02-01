#include "matrix.h"
#include <string>
#include <sstream>
#include <cassert>

// default constr
Matrix::Matrix() : rows(0), cols(0), mat(NULL) {};

// parsing with file handle
Matrix::Matrix(std::ifstream& inputFh, const char* filename) : rows(0), cols(0), mat(NULL)
{
	inputFh.open(filename); // assuming the file exists

	// read the rows and cols from first line
	std::string line;
	std::getline(inputFh, line);

	int r = 0, c = 0;
	std::istringstream iss;
	iss >> r;
	iss >> c;

	// initialize the 2D matrix using rows and cols
	initializeMatrix(r, c);

	// now read each line as rows into the matrix
	// ASSUMES the file is well formed!!
	for(int i = 0; i < rows; i++)
	{
		std::getline(inputFh, line);
		std::istringstream tmp;
		for(int j = 0; j < cols; j++)
			tmp >> mat[i][j];
	}

	// close the file
	inputFh.close();
}

void Matrix::initializeMatrix(int r, int c)
{
	rows = r; cols = c;

	// allocate the rows
	mat = new int*[rows];
	assert(mat != NULL);

	// allocate the row sizes (basically length is col)
	for(int i = 0; i < rows; i++)
	{
		mat[i] = new int[cols]();  // calls default constr, so all values should be 0
		assert(mat[i] != NULL);
	}
}

// TODO: define destructor

