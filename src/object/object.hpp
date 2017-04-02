#ifndef HEADER_OBJECT_HPP_INCLUDED
#define HEADER_OBJECT_HPP_INCLUDED



// ABSTRACT CLASS //
class Object 
{
public:
    // Entity := behaviour depends on environment
    // Item   := behaviour is unconditional
    enum Type {Entity, Item};
    
protected:
    Type  mType;
public:
    Type getType() const;

};

#endif
