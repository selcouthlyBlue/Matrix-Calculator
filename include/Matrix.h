#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <fstream>
#include <iostream>

class Matrix
{
private:
    std::vector<std::vector<float>> matrix;

public:
    /**
     * @brief Primary Constructor of Matrix class
     * @param file
     */
    Matrix(std::ifstream& file);

    /**
     * @brief Null Constructor of Matrix class
     */
    Matrix();

    /**
     * @brief This function returns a vector of integers
     * @param i The row number
     * @return A vector of integers containing the ith row contents of the matrix
     */
    std::vector<float> getRow(int i);

    /**
     * @brief This function swaps two rows of a matrix
     * @param rowIndex1 The index of the row to be swapped with another row having rowIndex2
     * @param rowIndex2 The index of the row to be swapped with another row having rowIndex1
     */
    void swapRows(int rowIndex1, int rowIndex2);

    /**
     * @brief This function multiplies a scalar to each element of the ith row
     * @param i The index of the row
     * @param scalar The scalar to be multiplied to each element of the ith row
     */
    void multiplyScalarToRow(int i, float scalar);

    /**
     * @brief This function adds a scalar to each element of the ith row
     * @param i The index of the row
     * @param scalar The scalar to be added to each element of the ith row
     */
    void addScalarToRow(int i, float scalar);

    /**
     * @brief This function returns a vector of integers
     * @param j The row number
     * @return A vector of integers containing the jth column contents of the matrix
     */
    std::vector<float> getColumn(int j);

    /**
     * @brief This function returns an element of a matrix
     * @param i The row number
     * @param j The column number
     * @return Returns the element at the ith row, jth column of the matrix
     */
    float getElement(int i, int j);

    /**
     * @brief This function replaces the jth column of a matrix with another column
     * @param j The index to of the column to be replace
     * @param column The column to replace the jth column
     */
    void replaceColumn(int j, std::vector<float> column);

    /**
     * @brief This function returns the number of rows that the matrix has
     * @return The number of rows
     */
    unsigned int getNumRows();

    /**
     * @brief This function returns the number of columns that the matrix has
     * @return The number of columns
     */
    unsigned int getNumColumns();

    /**
     * @brief This adds a row to the matrix
     * @param row The row to be added to the matrix
     */
    void addRow(std::vector<float> row);

    /**
     * @brief This adds a column to the matrix
     * @param column The column to be added to the matrix
     */
    void addColumn(std::vector<float> column);

    /**
     * @brief Checks if the matrix is empty
     * @return True if the matrix is empty; false otherwise
     */
    bool isEmpty();

    /**
     * @brief This function returns the minor of a matrix about a row and a column
     * @param i The ith row of the matrix
     * @param j The jth row of the matrix
     * @return Returns the minor of a matrix
     */
    Matrix getMinor(unsigned int i, unsigned int j);

    /**
     * @brief Prints out the elements of a matrix
     */
    void seeMatrix();
};

#endif // MATRIX_H
