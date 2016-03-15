#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <windows.h>
#include "Matrix.h"
#include "UnaryMatrixOperations.h"
#include "MatrixOperations.h"
#include "LinearSystemSolver.h"

void readFile(std::string filename)
{
    std::ifstream file(filename, std::ios::in);
    if(!file)
    {
        std::cerr << "Error in opening " << filename << "." << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}

bool isMatrixOperation(const char argument[])
{
    return strcmp(argument, "addition") == 0 || strcmp(argument, "multiplication") == 0 || strcmp(argument, "solveLS") == 0;
}

bool isUnaryMatrixOperation(const char argument[])
{
    return strcmp(argument, "transpose") == 0 || strcmp(argument, "getdeterminant") == 0 || strcmp(argument, "getinverse") == 0;
}

int main(int argc, char *argv[])
{
    const std::string helpFile = "readme.txt";
    switch(argc)
    {
    case 2:
    {
        if(strcmp(argv[1], "-help") == 0)
        {
            readFile(helpFile);
        }
        else
        {
            std::cout << "Enter -help as a command line argument to see the manual for this program." << std::endl;
        }
        break;
    }
    case 3:
    {
        if(isUnaryMatrixOperation(argv[2]))
        {
            std::ifstream matrixFile((std::string(argv[1])).c_str(), std::ios::in);
            Matrix matrix(matrixFile);
            if(strcmp(argv[2], "transpose") == 0)
            {
                Matrix transposeMatrix = getTransposeMatrix(matrix);
                transposeMatrix.seeMatrix();
            }
            else if(strcmp(argv[2], "getdeterminant") == 0)
            {
                if(hasDeterminant(matrix))
                {
                    std::cout << "The determinant of the given matrix is equal to " << getDeterminant(matrix) << std::endl;
                }
                else
                {
                    std::cout << "The determinant of the given matrix does not exist." << std::endl;
                }
            }
            else if(strcmp(argv[2], "getinverse") == 0)
            {
                if(!hasInverse(matrix))
                {
                    std::cout << "The inverse of the given matrix does not exist." << std::endl;
                }
                else
                {
                    Matrix inverseMatrix = getInverse(matrix);
                    inverseMatrix.seeMatrix();
                }
            }
        }
        else
        {
            std::cout << "Enter -help as a command line argument to see the manual for this program." << std::endl;
        }
        break;
    }
    case 4:
    {
        if(isMatrixOperation(argv[3]))
        {
            std::ifstream firstFile((std::string(argv[1])).c_str(), std::ios::in);
            Matrix firstOperand(firstFile);
            std::ifstream secondFile((std::string(argv[2])).c_str(), std::ios::in);
            Matrix secondOperand(secondFile);
            if(strcmp(argv[3], "addition") == 0)
            {
                if(!isDefinedOnAddition(firstOperand, secondOperand))
                {
                    std::cout << "Matrix addition is not applicable for the given matrices." << std::endl;
                }
                else
                {
                    Matrix result = add(firstOperand, secondOperand);
                    result.seeMatrix();
                }
            }
            else if(strcmp(argv[3], "multiplication") == 0)
            {
                if(!isDefinedOnMultiplication(firstOperand, secondOperand))
                {
                    std::cout << "Matrix multiplication is not applicable for the given matrices." << std::endl;
                }
                else
                {
                    Matrix result = multiply(firstOperand, secondOperand);
                    result.seeMatrix();
                }
            }
            else if(strcmp(argv[3], "solveLS") == 0)
            {
                if(!isSolvable(firstOperand, secondOperand))
                {
                    std::cout << "Unable to find the solution for the given linear system parameters." << std::endl;
                }
                else
                {
                    Matrix augmentedMatrix = augment(firstOperand, secondOperand);
                    Matrix result = getREF(augmentedMatrix, true);
                    result.seeMatrix();
                }
            }
        }
        else
        {
            std::cout << "Enter -help as a command line argument to see the manual for this program." << std::endl;
        }
        break;
    }
    default:
    {
        std::cout << "Enter -help as a command line argument to see the manual for this program." << std::endl;
    }
    }
    return 0;
}
