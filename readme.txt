Author: Jerome Patrick V. Gonzalvo

Matrix Calculator User Manual

You can use this program by having one of these commands as (a) command line argument(s):

1. -help (prints the contents of this manual)

2. somefile1.txt somefile2.txt matrixoperation
where somefile1.txt and somefile2.txt each contain a well-formed matrix, and matrixoperation can be any of the following:

addition (the matrices in each file should be of the same size)
multiplication (the number of columns of the first matrix should be equal to the number of rows of the second matrix)

(the first file should contain a square matrix of order n. the second file should contain a matrix of size nx1)
solveLS
inverseSolveLS
adjInverseSolveLS

3. somefile.txt unarymatrixoperation
where somefile.txt contains a matrix a well-formed matrix, and unarymatrixoperation can be any of the following:

transpose

(the file should contain a square matrix for these operations)
getdeterminant
getinverse
adjgetinverse

Note:
(1) The matrix files you are going to use in this program should belong in the same folder as the "main.cpp" file. You may add your own matrix files to the folder.
(2) It is assumed that each the files to be used in this program contain a well-formed matrix. Other than that, the file should not contain any unnecessary spaces.
(3) This is compiled using Cygwin GCC Compiler.
