#ifndef HEADER_MATRIX_HPP_INCLUDED
#define HEADER_MATRIX_HPP_INCLUDED

#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <vector>

//! Matrix should BE a vector, not CONTAIN a vector
//! UPD: Done
template <typename T>
class Matrix : private std::vector<T>
{
public:
    Matrix (const Matrix& other);
    Matrix (unsigned height = 0, unsigned width = 0);
    Matrix (unsigned height, unsigned width, const T& element);
    Matrix (unsigned height, unsigned width, T&& element);
    T &at(unsigned y, unsigned x);
    void fill (const T& element);
    void setHeight (unsigned height);
    void setWidth (unsigned width);
    void setSize (unsigned height, unsigned width);
    unsigned getHeight () const;
    unsigned getWidth () const;

    // Get iteration abilities from vector
    using std::vector<T>::begin;
    using std::vector<T>::end;
    using std::vector<T>::rbegin;
    using std::vector<T>::rend;
    using std::vector<T>::cbegin;
    using std::vector<T>::cend;
    using std::vector<T>::crbegin;
    using std::vector<T>::crend;

    // Get element management from vector
    using std::vector<T>::clear;
    using std::vector<T>::swap;

protected:
    bool isInRange (unsigned x, unsigned y) const;
private:
    unsigned mHeight, mWidth;

    // Оператор вывода в поток
    friend std::ostream & operator << (std::ostream & ostr, Matrix & M)
    {
        ostr << "Matrix height: " << M.getHeight() << ", width: " << M.getWidth() << std::endl;
        for (unsigned i = 0; i < M.getHeight(); i++) {
            ostr << "        ";
            for (unsigned j = 0; j < M.getWidth(); j++)
                ostr << std::setw(4) << M.at(i, j) << " ";
            ostr << std::endl;
        }
        return ostr;
    }
    
    Matrix< T > & operator = (const Matrix< T > Other) const
    {
        std::vector<T>::operator =(Other);
        mWidth = Other.mWidth;
        mHeight = Other.mHeight;
    }

    Matrix< T > & operator = (const Matrix< T > & Other) const
    {
        std::vector<T>::operator =(Other);
        mWidth = Other.mWidth;
        mHeight = Other.mHeight;
    }

    Matrix< T > & operator = (const Matrix< T > && Other) const
    {
        std::vector<T>::operator =(Other);
        mWidth = Other.mWidth;
        mHeight = Other.mHeight;
    }
};

template <typename T>
Matrix<T>::Matrix(const Matrix& other) :
    std::vector<T>(other), mHeight(other.mHeight), mWidth(other.mWidth)
{
}

template <typename T>
Matrix<T>::Matrix (unsigned height, unsigned width):
    std::vector<T>(height * width, T()), mHeight (height), mWidth (width)
{

}

template <typename T>
Matrix<T>::Matrix (unsigned height, unsigned width, const T &element):
    std::vector<T>(height * width, T()), mHeight (height), mWidth (width)
{
    
}

template <typename T>
Matrix<T>::Matrix (unsigned height, unsigned width, T&& element):
    std::vector<T>(height * width, T()), mHeight (height), mWidth (width)
{

}

template <typename T>
T &Matrix<T>::at(unsigned y, unsigned x)
{
    return std::vector<T>::at(y * mWidth + x);
}


template <typename T>
bool Matrix<T>::isInRange(unsigned x, unsigned y) const
{
    return ((x < mHeight) && (y < mWidth));
}

template <typename T>
void Matrix<T>::fill(const T &element)
{
    std::fill(std::vector<T>::begin(), std::vector<T>::end(), element);
}

template <typename T>
unsigned Matrix<T>::getHeight() const
{
    return mHeight;
}

template <typename T>
unsigned Matrix<T>::getWidth() const
{
    return mWidth;
}

template <typename T>
void Matrix<T>::setHeight (unsigned height)
{
    setSize(height, mWidth);
}

template <typename T>
void Matrix<T>::setWidth(unsigned width)
{
    setSize(mHeight, width);
}

template <typename T>
void Matrix<T>::setSize(unsigned height, unsigned width)
{
    if (height == mHeight && width == mWidth)
        return;
    
    unsigned lWidth = mWidth;
    unsigned lHeight = mHeight;
    Matrix< T > buffer(*this);

    mWidth = width;
    mHeight = height;

    std::vector<T>::resize(mHeight * mWidth);
    std::fill(std::vector<T>::begin(), std::vector<T>::end(), T());

    for (unsigned i = 0; i < std::min(lHeight, mHeight); i++)
        for (unsigned j = 0; j < std::min(lWidth, mWidth); j++)
            at(i, j) = buffer.at(i, j);
}



#endif // MATRIX_HPP


