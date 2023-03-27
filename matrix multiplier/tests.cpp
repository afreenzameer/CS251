#include <iostream>
#include <fstream>
#include <string>
#include "mymatrix.h"

using namespace std;

// checks to see if default constructor is creating a 4x4
bool default_constructor_test1()
{
  mymatrix<int> M;

  if (M.size() == 16)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// checks to see if parameterized constructor is creating a rxc value
bool parameterized_constructor_test1()
{
  mymatrix<int> M(7, 8);

  if (M.size() == 56)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// checks to see if parameterized constructor throws exception when row size equals 0
bool exception_parameterized_constructor_test2()
{
  try
  {
    mymatrix<int> M1(0, 6);

    cout << "parameterized constructor test failed: "
         << "row size 0 matrix did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}
// checks copy constructor by calling matrix multtiply operator
bool copy_constructor_test1()
{
  mymatrix<int> M;
  mymatrix<int> M1;
  mymatrix<int> M2;
  M1.at(2, 2) = 3;
  M2.at(2, 2) = 7;
  M = M1 * M2;

  if (M.at(2, 2) == 21)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// checks if numrows returns proper value
bool numrow_test1()
{

  mymatrix<int> M;

  if (M.numrows() == 4)
  {
    return true;
  }
  else
  {
    return false;
  }
}
// check if numcols of default constructor returns 4
bool numcols_test1()
{

  mymatrix<int> M;

  if (M.numcols(0) == 4)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// check if numcols throws exception if row is out of bounds
bool exception_numcols_test2()
{
  try
  {
    mymatrix<int> M1(2, 3);
    M1.numcols(7);
    cout << "matrix numcols test failed: "
         << "out of bounds row did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

// checks if default constructors matrix has a size of 16
bool size_test1()
{
  mymatrix<int> M;
  if (M.size() == 16)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// grow a matrix with 8 rows and 9 columns and check if size is 72
bool grow_test1()
{

  mymatrix<int> M;
  M.grow(8, 9);
  if (M.size() == 72)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// check if all values in the newly grown function are equal to 0
bool grow_test2()
{
  mymatrix<int> M;
  M.grow(8, 9);
  for (int i = 0; i < M.numrows(); i++)
  {
    for (int j = 0; j < M.numcols(0); j++)
    {
      if (M(i, j) == 0)
      {

        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

// check if grow function throws exception when row is out of bounds
bool exception_grow_test3()
{
  try
  {
    mymatrix<int> M;
    M.grow(0, 20);
    cout << "matrix grow test failed: "
         << "out of bounds row did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

// check if grow cols works by growing the column and seeing if the size is correct
bool growcols_test1()
{

  mymatrix<int> M;
  M.growcols(2, 9);
  if (M.size() == 21)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// call the at function and see if it is equal to 0
bool at_test1()
{

  mymatrix<int> M;

  if (M.at(2, 2) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// call the at function and set it equal to 5, then call it again to  check if the value  updated
bool at_test2()
{

  mymatrix<int> M;
  M.at(2, 2) = 5;
  if (M.at(2, 2) == 5)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// see if exception is thrown when row is out of bounds
bool exception_at_test2()
{
  try
  {
    mymatrix<int> M;
    M.at(50, 1);
    cout << "matrix at test failed: "
         << "out of bounds row did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

// see if exception is thrown when column is out of bounds
bool exception_at_test3()
{
  try
  {
    mymatrix<int> M;
    M.at(1, 15) = 9;
    cout << "matrix at test failed: "
         << "out of bounds column did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

// call the op function and see if it is equal to 0
bool op_test1()
{

  mymatrix<int> M;
  if (M(2, 2) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// call the op function and set it equal to 5, then call it again to  check if the value  updated
bool op_test2()
{

  mymatrix<int> M;
  M(2, 2) = 5;
  if (M(2, 2) == 5)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// see if exception is thrown when column is out of bounds
bool exception_op_test3()
{
  try
  {
    mymatrix<int> M;
    M(1, 15) = 9;
    cout << "matrix at test failed: "
         << "out of bounds column did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

// set every value of the matrix to 5, multiply the matrix by 5 and see if every value is equal to 25
bool scalar_test1()
{
  mymatrix<int> M;
  mymatrix<int> M1;
  for (int i = 0; i < M.numrows(); i++)
  {
    for (int j = 0; j < M.numcols(0); j++)
    {
      M.at(i, j) = 5;
    }
  }

  M1 = M * 5;
  for (int i = 0; i < M1.numrows(); i++)
  {
    for (int j = 0; j < M1.numcols(0); j++)
    {
      if (M1.at(i, j) == 25)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

// set different values of the matrix to some numbers, multiply the matrix by 5 and see if every value is equal to the correct multiple of 5
bool scalar_test2()
{
  mymatrix<int> M;
  mymatrix<int> M1;
  M(2, 2) = 5;
  M(0, 0) = 3;
  M(1, 2) = 4;
  M(3, 3) = 1;
  M1 = M * 5;
  if (M1(2, 2) == 25 && M1(0, 0) == 15 && M1(1, 2) == 20 && M1(3, 3) == 5 && M1(0, 1) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
//set two values of M1 and M2 equal to 7 and check if tthe corresponding value equals 49
bool matrix_mult_test1()
{
  mymatrix<int> M;
  mymatrix<int> M1;
  mymatrix<int> M2;
  M1.at(2, 2) = 7;
  M2.at(2, 2) = 7;
  M = M1 * M2;

  if (M.at(2, 2) == 49)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//set every value of M1 to 2, set every value of M2 equal to 3, check if every value of M equal 24
bool matrix_mult_test2()
{
  mymatrix<int> M;
  mymatrix<int> M1;
  mymatrix<int> M2;
  for (int i = 0; i < M1.numrows(); i++)
  {
    for (int j = 0; j < M1.numcols(0); j++)
    {
      M1.at(i, j) = 2;
    }
  }
  for (int i = 0; i < M2.numrows(); i++)
  {
    for (int j = 0; j < M2.numcols(0); j++)
    {
      M2.at(i, j) = 3;
    }
  }
  M = M1 * M2;

  for (int i = 0; i < M.numrows(); i++)
  {
    for (int j = 0; j < M.numcols(0); j++)
    {
      if (M.at(i, j) == 24)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

//check if an exception is thrown if matrix is jagged by growing cols then multiplying
bool exception_matrix_mult_test3()
{
  try
  {
    mymatrix<int> M1;
    mymatrix<int> M2;

    M1.growcols(3, 16);

    mymatrix<int> result;

    result = M1 * M2;

    cout << "matrix multiply test failed: "
         << "jagged matrix did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

//grow two matrices into mismatched sizes and check if it throws an exception
bool exception_matrix_mult_test4()
{
  try
  {
    mymatrix<int> M1;
    mymatrix<int> M2;

    M1.grow(5, 16);
    M2.grow(7, 4);
    mymatrix<int> result;

    result = M1 * M2;

    cout << "matrix multiply test failed: "
         << "size mismatched matrices did not throw exception"
         << endl;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

int main()
{
  int passed = 0;
  int failed = 0;

  if (default_constructor_test1())
  {
    passed++;
  }
  else
  {
    cout << "default_constructor_test1 failed" << endl;
    failed++;
  }

  if (parameterized_constructor_test1())
  {
    passed++;
  }
  else
  {
    cout << "parameterized_constructor_test1 failed" << endl;
    failed++;
  }

  if (copy_constructor_test1())
  {
    passed++;
  }
  else
  {
    cout << "copy_constructor_test1 failed" << endl;
    failed++;
  }

  if (numrow_test1())
  {
    passed++;
  }
  else
  {
    cout << "numrow_test1 failed" << endl;
    failed++;
  }

  if (numcols_test1())
    passed++;
  else
  {
    cout << "numcol_test1 failed" << endl;
    failed++;
  }

  if (exception_numcols_test2())
    passed++;
  else
  {
    cout << "exception_numcols_test2 failed" << endl;
    failed++;
  }

  if (size_test1())
  {
    passed++;
  }
  else
  {
    cout << "size_test1 failed" << endl;
    failed++;
  }
  if (grow_test1())
  {
    passed++;
  }
  else
  {
    cout << "grow_test1 failed" << endl;
    failed++;
  }
  if (grow_test2())
  {
    passed++;
  }
  else
  {
    cout << "grow_test2 failed" << endl;
    failed++;
  }
  if (growcols_test1())
  {
    passed++;
  }
  else
  {
    cout << "growcols_test1 failed" << endl;
    failed++;
  }
  if (at_test1())
  {
    passed++;
  }
  else
  {
    cout << "at_test1 failed" << endl;
    failed++;
  }
  if (at_test2())
  {
    passed++;
  }
  else
  {
    cout << "at_test2 failed" << endl;
    failed++;
  }

  if (exception_at_test2())
  {
    passed++;
  }
  else
  {
    cout << "exception_at_test2 failed" << endl;
    failed++;
  }

  if (exception_at_test3())
  {
    passed++;
  }
  else
  {
    cout << "exception_at_test3 failed" << endl;
    failed++;
  }

  if (op_test1())
  {
    passed++;
  }
  else
  {
    cout << "op_test1 failed" << endl;
    failed++;
  }
  if (op_test2())
  {
    passed++;
  }
  else
  {
    cout << "op_test2 failed" << endl;
    failed++;
  }

  if (exception_op_test3())
  {
    passed++;
  }
  else
  {
    cout << "exception_op_test3 failed" << endl;
    failed++;
  }
  if (scalar_test1())
  {
    passed++;
  }
  else
  {
    cout << "scalar_test1 failed" << endl;
    failed++;
  }

  if (scalar_test2())
  {
    passed++;
  }
  else
  {
    cout << "scalar_test2 failed" << endl;
    failed++;
  }
  if (matrix_mult_test1())
  {
    passed++;
  }
  else
  {
    cout << "matrix_mult_test1 failed" << endl;
    failed++;
  }

  if (matrix_mult_test2())
  {
    passed++;
  }
  else
  {
    cout << "matrix_mult_test2 failed" << endl;
    failed++;
  }

  if (exception_matrix_mult_test3())
  {
    passed++;
  }
  else
  {
    cout << "exception_matrix_mult_test3 failed" << endl;
    failed++;
  }

  if (exception_matrix_mult_test4())
  {
    passed++;
  }
  else
  {
    cout << "exception_matrix_mult_test4 failed" << endl;
    failed++;
  }

  if (exception_grow_test3())
  {
    passed++;
  }
  else
  {
    cout << "exception_grow_test3 failed" << endl;
    failed++;
  }

  if (exception_parameterized_constructor_test2())
  {
    passed++;
  }
  else
  {
    cout << "exception_parameterized_constructor_test2 failed" << endl;
    failed++;
  }
//prints the resulting number of test cases which passed and failed
  cout << "Tests passed: "
       << passed
       << endl;
  cout << "Tests failed: "
       << failed
       << endl;
  return 0;
}
