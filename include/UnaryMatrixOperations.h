#ifndef UNARYMATRIXOPERATIONS_H_INCLUDED
#define UNARYMATRIXOPERATIONS_H_INCLUDED

#include <vector>

/**
 * @brief This function returns the transpose of a matrix
 * @param matrix The matrix to be transposed
 * @return Returns the transpose of a matrix
 */
Matrix getTransposeMatrix(Matrix matrix)
{
    Matrix transposeMatrix;
    for(unsigned int i = 0; i < matrix.getNumColumns(); i++)
    {
        std::vector<float> row = matrix.getColumn(i);
        transposeMatrix.addRow(row);
    }
    return transposeMatrix;
}

#endif // UNARYMATRIXOPERATIONS_H_INCLUDED
