#include "Matrix.h"
#include "Helpers.h"

Matrix::Matrix(std::ifstream& file)
{
    if(!file)
    {
        std::cerr << "Error in opening file.";
        exit(1);
    }
    std::string line;
    std::vector<std::vector<float>> matrix;
    this->matrix = matrix;
    while(std::getline(file, line))
    {
        addRow(split(line, ' '));
    }
}

Matrix::Matrix()
{
    std::vector<std::vector<float>> matrix;
    this->matrix = matrix;
}

bool Matrix::isEmpty()
{
    return matrix.empty();
}

std::vector<float> Matrix::getRow(int i)
{
    return matrix.at(i);
}

void Matrix::swapRows(int rowIndex1, int rowIndex2)
{
    std::vector<float> temp;
    temp = matrix.at(rowIndex1);
    matrix.at(rowIndex1) = matrix.at(rowIndex2);
    matrix.at(rowIndex2) = temp;
}

void Matrix::multiplyScalarToRow(int i, float scalar)
{
    for(unsigned int j = 0; j < getNumColumns(); j++)
    {
        matrix.at(i).at(j) *= scalar;
    }
}

void Matrix::addScalarToRow(int i, float scalar)
{
    for(unsigned int j = 0; j < getNumColumns(); j++)
    {
        matrix.at(i).at(j) += scalar;
    }
}

std::vector<float> Matrix::getColumn(int j)
{
    std::vector<float> column;
    for(auto &iter : matrix)
    {
        column.push_back(iter.at(j));
    }
    return column;
}

float Matrix::getElement(int i, int j)
{
    return matrix.at(i).at(j);
}

void Matrix::replaceColumn(int j, std::vector<float> column)
{
    unsigned int k = 0;
    for(auto &iter : matrix)
    {
        iter.at(j) = column.at(k);
        k++;
    }
}

unsigned int Matrix::getNumRows()
{
    return matrix.size();
}

unsigned int Matrix::getNumColumns()
{
    return matrix.at(0).size();
}

void Matrix::addRow(std::vector<float> row)
{
    matrix.push_back(row);
}

void Matrix::addColumn(std::vector<float> column)
{
    if(isEmpty())
    {
        for(auto &iter : column)
        {
            std::vector<float> rowToAdd;
            rowToAdd.push_back(iter);
            addRow(rowToAdd);
        }
    }
    else
    {
        int j = 0;
        for(auto &iter : matrix)
        {
            iter.push_back(column.at(j));
            j++;
        }
    }
}

Matrix Matrix::getMinor(unsigned int i, unsigned int j)
{
    Matrix minorMatrix;
    if(i < getNumRows() && j < getNumColumns())
    {
        for(unsigned int k = 0; k < getNumRows(); k++)
        {
            std::vector<float> minor_row;
            for(unsigned int l = 0; l < getNumColumns(); l++)
            {
                if(k != i && l != j)
                {
                    minor_row.push_back(this->getElement(k,l));
                }
            }
            if(!minor_row.empty())
            {
                minorMatrix.addRow(minor_row);
            }
        }
    }
    return minorMatrix;
}

void Matrix::seeMatrix()
{
    if(!isEmpty())
    {
        for(unsigned int i = 0; i < getNumRows(); i++)
        {
            for(unsigned int j = 0; j < getNumColumns(); j++)
            {
                std::cout << std::left << std::setw(7) << std::setprecision(2) << getElement(i,j);
            }
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "The matrix is empty";
    }
}
