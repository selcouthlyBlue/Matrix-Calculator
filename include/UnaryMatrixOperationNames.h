#ifndef UNARYMATRIXOPERATIONNAMES_H_INCLUDED
#define UNARYMATRIXOPERATIONNAMES_H_INCLUDED

enum UnaryMatrixOperation
{
    GETADJOINT, TRANSPOSE, GETDETERMINANT, GETINVERSE, GETADJINVERSE
};

std::string toString(UnaryMatrixOperation unaryMatrixOperation)
{
    std::string s;
    switch(unaryMatrixOperation)
    {
        case UnaryMatrixOperation::GETADJOINT: return "getadjoint";
        case UnaryMatrixOperation::TRANSPOSE: return "transpose";
        case UnaryMatrixOperation::GETDETERMINANT: return "getdeterminant";
        case UnaryMatrixOperation::GETINVERSE: return "getinverse";
        case UnaryMatrixOperation::GETADJINVERSE: return "getadjinverse";
    }
    return s;
}


#endif // UNARYMATRIXOPERATIONNAMES_H_INCLUDED
