/*mymatrix.h*/


/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

// Author: Afreen Zameer
// Project overview: This program creates a matrix multiplier which takes in several commands. First, there are three constructors which create different matrices. The first is the default constructor which creates a 4 by 4 matrix of the default values of whatever type is put into the matrix, 0 for int, 0.0 for double and so on. The second constructor is a parameterized constructor, which allows for the creation of a matrix of default values with a specified row and column value. Finally there is the copy constructor which copies the values of a matrix into a new matrix. There are additional functions which return the number of rows and the number of columns of a specified row in the matrix. It does so  by accessing private values. There is then a growcols function which allows the user to grow the number of columns at a specified row to whatever value the user gives. The grow function is similar in that it grows both the number of rows and the number of columns using the format matrixName(rowSize, columnSize). The at and op function allows the user to access and modify the value at a specified row and column. The matrix multiplier function multiplies the matrices  and returns a result  matrix by multiplying each row of the first matrix by each column  of the second matrix, then  adding the values  together in the corresponding result matrix position. Finally, the output function  allows the user to see each element of the matrix specified.
#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template <typename T>
class mymatrix
{
private:
  struct ROW
  {
    T *Cols;     // dynamic array of column elements
    int NumCols; // total # of columns (0..NumCols-1)
  };

  ROW *Rows;   // dynamic array of ROWs
  int NumRows; // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:

  // Called automatically by C++ to construct a 4x4 matrix.  All
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4]; // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4]; // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{}; // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows,
  // where each row has C columns. All elements are initialized to
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");
    Rows = new ROW[R]; // an array with R ROW structs:
    NumRows = R;

    // initialize each row to have C columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C]; // an array with C elements of type T:
      Rows[r].NumCols = C;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{}; // default value for type T:
      }
    }
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a
  // copy of an existing matrix.  Example: this occurs when passing
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  
  mymatrix(const mymatrix<T> &other)
  {
    this->Rows = new ROW[other.numrows()];
    this->NumRows = other.NumRows; // set "this" numrows to "other" numrows

    //loop through the number of rows and sets "this" cols to "other" cols
    for (int r = 0; r < other.NumRows; ++r)
    {
      this->Rows[r].Cols = new T[other.Rows[r].NumCols]; 
      this->Rows[r].NumCols = other.Rows[r].NumCols;

      for (int c = 0; c < other.Rows[r].NumCols; ++c)
      {
        this->Rows[r].Cols[c] = other.Rows[r].Cols[c]; 
      }
    }
  }

  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {

    return NumRows;
  }

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    //throws exception if the number of columns given is less than 0 or greater than the number of rows in the matrix
    if (r < 0 || r >= NumRows)
    {
      throw invalid_argument("mymatrix::numcols: row");
    }
    return Rows[r].NumCols;
  }

  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    
    if (Rows[r].NumCols < C)
    {

      int newSize = C;
      T *temp = new T[newSize]; // create a temp value of the size of the amount of columns wanted
      for (int i = 0; i < newSize; i++)
      {
        //if the numcols is less than the new number of columns set temp equal to rows at r and cols at i
        if (i < Rows[r].NumCols)
        {
          temp[i] = Rows[r].Cols[i];
        }
        else
        {
          temp[i] = T{}; // otherwise set temp to the default value for size newSize
        }
      }
      Rows[r].NumCols = C;
      Rows[r].Cols = temp; 
    }
  }

  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  //
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  //
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");

    //case 1: if R is less than the number of rows simply grow the columns. 
    if (R < NumRows)
    {
      for (int i = 0; i < NumRows; i++)
      {
        growcols(i, C);
      }
    }
    //case2: R is greater than NumRows. In this case, rows and columns must be grown.
    else
    {
      //point the new matrix to the old matrix, then delete Rows
      ROW *temp = new ROW[R];

      for (int i = 0; i < NumRows; i++)
      {

        temp[i].Cols = Rows[i].Cols;
        temp[i].NumCols = Rows[i].NumCols;
      }
      delete[] Rows;
      Rows = temp;
      for (int t = NumRows; t < R; t++)
      {
        Rows[t].Cols = new T[C];
        Rows[t].NumCols = C;
        for(int h = 0; h < Rows[t].NumCols ; h++ ){
          Rows[t].Cols[h] = T{};
        }
      }

      NumRows = R;
      //grow cols in the else block
      for (int p = 0; p < R; p++)
      {
        growcols(p, C);
      }
      
    }
  }

  // size: Returns the total # of elements in the matrix.
  int size() const
  {
    // add all the NumCols of each row to counter, then return counter
    int counter = 0;
    for (int i = 0; i < NumRows; i++)
    {
      counter = counter + Rows[i].NumCols;
    }
    return counter;
  }

  // at: Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  T &at(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    return Rows[r].Cols[c];
  }
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T &operator()(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //

  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result(*this);
    // loop through rows and columns and multiply each matrix value by the scalar value
    for (int i = 0; i < result.numrows(); ++i)
    {
      for (int j = 0; j < result.numcols(i); ++j)
      {
        result(i, j) = result(i, j) * scalar;
      }
    }
    return result;
  }

  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T> &other)
  {
    //check "this" matrix if number  of columns in row 0 is equal to the number of columns in every other row 
    for (int i = 0; i < NumRows; i++)
    {
      int numberOfCols = Rows[0].NumCols; 
      if (numberOfCols != Rows[i].NumCols)
      {
        throw runtime_error("mymatrix::*: this not rectangular");
      }
    }

    //check "other" matrix if number  of columns in row 0 is equal to the number of columns in every other row
    for (int j = 0; j < NumRows; j++)
    {
      int numberOfCols = other.numcols(0);
      if (numberOfCols != other.numcols(j))
      {
        throw runtime_error("mymatrix::*: other not rectangular");
      }
    }
    // check to make sure "this" numcols equals "other" numrows
    if (numcols(0) != other.numrows())
    {
      throw runtime_error("mymatrix::*: size mismatch");
    }

    // three nested for loops, the first loops through the rows, the second loops through the columns, the third multiplies the Rows[i].Cols[k] by other.Rows[k].Cols[j]. 
    mymatrix<T> result(this->numrows(), other.numcols(0));
    for (int i = 0; i < numrows(); ++i)
    {
      for (int j = 0; j < other.numcols(i); ++j)
      {
        T sum = 0;
        for (int k = 0; k < other.numrows(); ++k)
        {
          sum += Rows[i].Cols[k] * other.Rows[k].Cols[j];
        }
        result.Rows[i].Cols[j] = sum;
      }
    }
    return result;
  }

  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }
};
