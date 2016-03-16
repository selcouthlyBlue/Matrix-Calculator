#ifndef LINEARSYSTEMSOLVER_H_INCLUDED
#define LINEARSYSTEMSOLVER_H_INCLUDED

#include <cmath>
#include <thread>
#include <mutex>

bool isSquareMatrix(Matrix matrix)
{
    return matrix.getNumRows() == matrix.getNumColumns();
}

bool hasDeterminant(Matrix matrix)
{
    return isSquareMatrix(matrix);
}

bool isSolvable(Matrix coefficientMatrix, Matrix constantMatrix)
{
    return coefficientMatrix.getNumRows() == constantMatrix.getNumRows();
}

/**
 * @brief This function returns the Row-Echelon-Form (REF) of a matrix
 * @param matrix The matrix to be turned into its REF
 * @param isRREF If false, the function will return the REF of the matrix. Otherwise, the function will return the Reduced-REF of the matrix.
 * @return Returns the REF or RREF of a matrix
 */
Matrix getREF(Matrix matrix, bool isRREF)
{
    Matrix REFmatrix;
    int k = 0;
    unsigned int i = 0;
    while(i < matrix.getNumRows())
    {
        if(matrix.getElement(i,k) == 0)
        {
            for(unsigned int j = i + 1; j < matrix.getNumRows(); j++)
            {
                if(matrix.getElement(j,k) != 0)
                {
                    matrix.swapRows(i, j);
                }
                break;
            }
        }
        if(matrix.getElement(i,k) != 0)
        {
            matrix.multiplyScalarToRow(i, 1/matrix.getElement(i,k));
            if(isRREF)
            {
                for(int j = i - 1; j >= 0; j--)
                {
                    float scalar = matrix.getElement(j,k);
                    for(unsigned int l = k; l < matrix.getNumColumns(); l++)
                    {
                        matrix.addScalarToElement(j,l, scalar * -matrix.getElement(i,l));
                    }
                }
            }
            for(unsigned int j = i + 1; j < matrix.getNumRows(); j++)
            {
                float scalar = matrix.getElement(j,k);
                for(unsigned int l = k; l < matrix.getNumColumns(); l++)
                {
                    matrix.addScalarToElement(j,l,  scalar * -matrix.getElement(i,l));
                }
            }
        }
        REFmatrix.addColumn(matrix.getColumn(k));
        k++;
        i++;
    }
    while(i < matrix.getNumColumns())
    {
        REFmatrix.addColumn(matrix.getColumn(i));
        i++;
    }
    return REFmatrix;
}

/**
 * @brief This function returns the determinant of a matrix through the use of cofactor expansion about the first column
 * @param matrix The matrix
 * @return Returns the determinant of the matrix
 */
float getDeterminant(Matrix matrix)
{
    float determinant;
    if(matrix.getNumRows() == 1 && matrix.getNumColumns() == 1)
        return matrix.getElement(0,0);
    for(unsigned int i = 0; i < matrix.getNumRows(); i++)
    {
        determinant += matrix.getElement(i,0) * pow(-1, i) * getDeterminant(matrix.getMinor(i,0));
    }
    return determinant;
}

/**
 * @brief This function returns the determinant of a matrix through the use of cofactor expansion about a row or a column
 * @param matrix The matrix
 * @param index The row or column index
 * @param isRow If true, the function will use cofactor expansion about a row. Otherwise, a column
 * @return Returns the determinant of the matrix
 */
float getDeterminant(Matrix matrix, int index, bool isRow)
{
    float determinant;
    if(matrix.getNumRows() == 1 && matrix.getNumColumns() == 1)
        return matrix.getElement(0,0);
    for(unsigned int i = 0; i < (isRow ? matrix.getNumRows() : matrix.getNumColumns()); i++)
    {
        if(isRow)
        {
            determinant += matrix.getElement(index,i) * pow(-1, i + index) * getDeterminant(matrix.getMinor(index,i));
        }
        else
        {
            determinant += matrix.getElement(i,index) * pow(-1, i + index) * getDeterminant(matrix.getMinor(i,index));
        }
    }
    return determinant;
}

bool hasInverse(Matrix matrix)
{
    return getDeterminant(matrix) != 0;
}

/**
 * @brief This function forms the identity matrix of order n
 * @param dimenision The order of the matrix
 * @return Returns the identity matrix of order n
 */
Matrix formIdentityMatrix(unsigned int dimension)
{
    Matrix identityMatrix;
    int j = 0;
    for(unsigned int i = 0; i < dimension; i++)
    {
        std::vector<float> row;
        for(unsigned int k = 0; k < dimension; k++)
        {
            row.push_back(0);
        }
        row.at(j) = 1;
        identityMatrix.addRow(row);
        j++;
    }
    return identityMatrix;
}

/**
 * @brief This function returns the inverse of a matrix
 * @param matrix The matrix
 * @return Returns the inverse of the matrix
 */
Matrix getInverse(Matrix matrix)
{
    Matrix RREFMatrix = getREF(augment(matrix, formIdentityMatrix(matrix.getNumColumns())), true);
    Matrix inverseMatrix;
    for(unsigned int i = 0; i < RREFMatrix.getNumRows(); i++)
    {
        std::vector<float> inverse_row;
        for(unsigned int j = matrix.getNumColumns(); j < RREFMatrix.getNumColumns(); j++)
        {
            inverse_row.push_back(RREFMatrix.getElement(i,j));
        }
        inverseMatrix.addRow(inverse_row);
    }
    return inverseMatrix;
}

/**
 * @brief This function returns the adjoint matrix of a matrix
 * @param matrix The matrix
 * @return Returns the adjoint matrix of the matrix
 */
Matrix getAdjointMatrix(Matrix matrix)
{
    Matrix adjointMatrix;
    for(unsigned int j = 0; j < matrix.getNumColumns(); j++)
    {
        std::vector<float> result_row;
        for(unsigned int i = 0; i < matrix.getNumRows(); i++)
        {
            result_row.push_back(pow(-1, i + j) * getDeterminant(matrix.getMinor(i,j)));
        }
        adjointMatrix.addRow(result_row);
    }
    return adjointMatrix;
}

/**
 * @brief This function returns the inverse of a matrix using the adjoint method
 * @param matrix The matrix
 * @return Returns the inverse of the matrix
 */
Matrix adjGetInverse(Matrix matrix)
{
    Matrix inverseMatrix = getAdjointMatrix(matrix);
    inverseMatrix.multiplyScalarToMatrix(1/getDeterminant(matrix));
    return inverseMatrix;
}

/**
 * @brief This function solves a linear system given a coefficient matrix and a constant matrix using the Gauss-Jordan Elimination (GJEM) method
 * @param matrix The coefficient matrix
 * @param constantMatrix The constant matrix
 * @return Returns the solution matrix
 */
Matrix GJEMSolveLS(Matrix matrix, Matrix constantMatrix)
{
    Matrix solutionSet;
    Matrix augmentedMatrix = getREF(augment(matrix, constantMatrix), true);
    std::vector<float> column;
    for(unsigned int i = 0; i < matrix.getNumRows(); i++)
    {
        column.push_back(augmentedMatrix.getElement(i,matrix.getNumRows()));
    }
    solutionSet.addColumn(column);
    return solutionSet;
}

/**
 * @brief This function solves a linear system given a coefficient matrix and a constant matrix using the inverse method
 * @param matrix The coefficient matrix
 * @param constantMatrix The constant matrix
 * @param isAdj If true, the inverse matrix that will be used will come from the adjoint method. Otherwise, the GJEM method.
 * @return Returns the solution matrix
 */
Matrix inverseSolveLS(Matrix matrix, Matrix constantMatrix, bool isAdj)
{
    Matrix inverseMatrix;
    if(isAdj)
    {
        inverseMatrix = adjGetInverse(matrix);
    }
    else
    {
        inverseMatrix = getInverse(matrix);
    }
    Matrix solutionSet = multiply(inverseMatrix, constantMatrix);
    return solutionSet;
}

#endif // LINEARSYSTEMSOLVER_H_INCLUDED
