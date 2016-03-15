#ifndef MATRIXOPERATIONS_H_INCLUDED
#define MATRIXOPERATIONS_H_INCLUDED

#include <vector>
#include <thread>
#include <iomanip>
#include <iostream>
#include <mutex>

static std::mutex barrier;

bool isAugmentable(Matrix firstOperand, Matrix secondOperand)
{
    return firstOperand.getNumRows() == secondOperand.getNumRows();
}

bool isDefinedOnMultiplication(Matrix firstOperand, Matrix secondOperand)
{
    return firstOperand.getNumColumns() == secondOperand.getNumRows();
}

bool isDefinedOnAddition(Matrix firstOperand, Matrix secondOperand)
{
    return firstOperand.getNumColumns() == secondOperand.getNumColumns() && firstOperand.getNumRows() == secondOperand.getNumRows();
}

Matrix multiply(Matrix firstOperand, Matrix secondOperand)
{
    Matrix result;
    auto multiplyRowColumn = [](const std::vector<float> &row, Matrix secondOperand, Matrix &result)
    {
        std::vector<float> result_row;
        for(unsigned int i = 0; i < secondOperand.getNumColumns(); i++)
        {
            float sum = 0;
            for(unsigned int j = 0; j < row.size(); j++)
            {
                sum += row.at(j) * secondOperand.getElement(j,i);
            }
            result_row.push_back(sum);
        }
        std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
        result.addRow(result_row);
    };
    std::vector<std::thread> threads;
    for(unsigned int i = 0; i < firstOperand.getNumRows(); i++)
    {
        std::vector<float> row = firstOperand.getRow(i);
        threads.push_back(std::thread(multiplyRowColumn, row, secondOperand, std::ref(result)));
    }
    for(auto &iter : threads)
    {
        iter.join();
    }
    return result;
}

Matrix add(Matrix firstOperand, Matrix secondOperand)
{
    Matrix result;
    auto addRows = [](const std::vector<float> &firstOperandRow, const std::vector<float> &secondOperandRow, Matrix &result)
    {
        std::vector<float> result_row;
        for(unsigned int i = 0; i < firstOperandRow.size(); i++)
        {
            float sum = firstOperandRow.at(i) + secondOperandRow.at(i);
            result_row.push_back(sum);
        }
        std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
        result.addRow(result_row);
    };
    std::vector<std::thread> threads;
    for(unsigned int i = 0; i < firstOperand.getNumRows(); i++)
    {
        std::vector<float> firstOperandRow = firstOperand.getRow(i);
        std::vector<float> secondOperandRow = secondOperand.getRow(i);
        threads.push_back(std::thread(addRows, firstOperandRow, secondOperandRow, std::ref(result)));
    }
    for(auto &iter : threads)
    {
        iter.join();
    }
    return result;
}

Matrix augment(Matrix firstOperand, Matrix secondOperand)
{
    Matrix result = firstOperand;
    for(unsigned int i = 0; i < secondOperand.getNumColumns(); i++)
    {
        result.addColumn(secondOperand.getColumn(i));
    }
    return result;
}

#endif // MATRIXOPERATIONS_H_INCLUDED
