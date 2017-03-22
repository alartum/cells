#include "cell.hpp"

Cell::Cell() : cType(Cell::Clear), cPrevType(Cell::Clear) 
{
}
Cell::Cell(cell_type_t ct) : cType(ct), cPrevType(Cell::Clear) 
{
}
Cell::cell_type_t Cell::getType() const
{
    return cType;
}
Cell::cell_type_t Cell::getPrevType() const
{
    return cPrevType;
}
void Cell::setType(Cell::cell_type_t ct)
{
    cType = ct;
}
void Cell::setPrevType(Cell::cell_type_t ct)
{
    cPrevType = ct;
}
void Cell::updatePrevType() 
{
    cPrevType = cType;
}
