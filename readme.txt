Author: Jerome Patrick V. Gonzalvo

Matrix/Matrices Operator User Manual

You can use this program by having one of these commands as (a) command line argument(s):

1. -help (prints the contents of this manual)

2. somefile1.txt somefile2.txt matrixoperation
where somefile1.txt and somefile2.txt each contain a well-formed matrix, and matrixoperation can be any of the following:

addition (the matrices in each file should be of the same size)
multiplication (the number of columns of the first matrix should be equal to the number of rows of the second matrix)
solveLS (the first file should contain a square matrix of order n. the second file should contain a matrix of size nx1)

3. somefile.txt unarymatrixoperation
where somefile.txt contains a matrix a well-formed matrix, and unarymatrixoperation can be any of the following:

transpose
getdeterminant (the file should contain a square matrix)
getinverse (the file should also contain a square matrix)

Notes: 
(1) The matrix files you are going to use in this program should belong in the same folder as the "main.cpp" file. You may add your own matrix files there as well.
(2) This is compiled using the cygwin gcc compiler.
(3) The matrix files should not contain any unnecessary spaces or characters.
