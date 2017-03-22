#ifndef HEADER_CELL_HPP_INCLUDED
#define HEADER_CELL_HPP_INCLUDED

class Cell
{
public:
    enum cell_type_t {Clear, Live, Water, Green};
    
private:
    cell_type_t cType;
    cell_type_t cPrevType;
    
public:
    Cell();
    Cell(cell_type_t ct);
    
    cell_type_t getType() const;
    cell_type_t getPrevType() const;
    void setType(cell_type_t ct);
    void setPrevType(cell_type_t ct);
    void updatePrevType();
};

#endif
