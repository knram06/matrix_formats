#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <cstring>

#include "matrix.h"


// default constr
Matrix::Matrix() : rows(0), cols(0), mat(NULL) {};

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
	initializeMatrix(r, c);
}

// parsing with file handle
Matrix::Matrix(std::ifstream& inputFh, const char* filename) : rows(0), cols(0), mat(NULL)
{
	inputFh.open(filename); // assuming the file exists

	// read the rows and cols from first line
	std::string line;
	std::getline(inputFh, line);

	int r = 0, c = 0;
	std::istringstream iss(line);
	iss >> r;
	iss >> c;

	// initialize the 2D matrix using rows and cols
	initializeMatrix(r, c);

	// now read each line as rows into the matrix
	// ASSUMES the file is well formed!!
	for(int i = 0; i < rows; i++)
	{
		std::getline(inputFh, line);
		std::istringstream tmp(line);
		for(int j = 0; j < cols; j++)
			tmp >> mat[i][j];
	}

	// close the file
	inputFh.close();
}

// copy constructor
Matrix::Matrix(const Matrix& m)
{
	// allocate the matrix
	initializeMatrix(m.rows, m.cols);

	// copy over elements
	for(int i = 0; i < rows; i++)
		std::memcpy(mat[i], m.mat[i], sizeof(int)*cols);

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

void Matrix::print() const
{
	std::cout << "Rows: " << rows << ", cols: " << cols << std::endl;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
			std::cout << mat[i][j] << " ";
		std::cout << std::endl;
	}
}

// Multiplication function
Matrix Matrix::mult(const Matrix& b)
{
	// ensure that cols on left matches rows on right
	assert(cols == b.rows);

	Matrix ret(rows, b.cols);
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < b.cols; j++)
		{
			int sum = 0;
			for(int k = 0; k < cols; k++)
				sum += mat[i][k] * b.mat[k][j];

			// fill in the value
			ret.mat[i][j] = sum;
		}
	}

	return ret;
}

// define destructor
Matrix::~Matrix()
{
	// free the rowise allocations first
	for(int i = 0; i < rows; i++)
		delete [] mat[i];
	// free the row pointers
	delete [] mat;
}
