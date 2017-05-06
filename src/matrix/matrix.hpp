#ifndef HEADER_MATRIX_HPP_INCLUDED
#define HEADER_MATRIX_HPP_INCLUDED

#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>


//! Matrix should BE a vector, not CONTAIN a vector
//! UPD: Done
template <typename T>
class Matrix : public std::vector<T>
{
public:
    Matrix (unsigned height = 0, unsigned width = 0);
    Matrix (unsigned height, unsigned width, const T& element);
    Matrix (unsigned height, unsigned width, T&& element);
    // Возвращает ссылку элемент с данной позицией
    T& at (unsigned x, unsigned y);
    // Заполняет матрицу элементом element
    inline void fill (const T& element);
    // Изменяет высоту
    inline void setHeight (unsigned height);
    // Изменяет ширину
    inline void setWidth (unsigned width);
    // Изменяет оба параметра
    inline void setSize (unsigned height, unsigned widht);
    inline unsigned getHeight () const;
    inline unsigned getWidth () const;

protected:
    // Корректны ли координаты
    inline bool isInRange (unsigned x, unsigned y) const;
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
    
    inline Matrix< T > & operator = (const Matrix< T > Other) const
    {
        std::vector<T>::operator =(Other);
        mWidth = Other.mWidth;
        mHeight = Other.mHeight;
    }

    inline Matrix< T > & operator = (const Matrix< T > & Other) const 
    {
        std::vector<T>::operator =(Other);
        mWidth = Other.mWidth;
        mHeight = Other.mHeight;
    }

    inline Matrix< T > & operator = (const Matrix< T > && Other) const 
    {
        std::vector<T>::operator =(Other);
        mWidth = Other.mWidth;
        mHeight = Other.mHeight;
    }
};

template <typename T>
inline Matrix<T>::Matrix (unsigned height, unsigned width):
    std::vector<T>(height * width, T()), mHeight (height), mWidth (width)
{

}

template <typename T>
inline Matrix<T>::Matrix (unsigned height, unsigned width, const T &element):
    std::vector<T>(height * width, T()), mHeight (height), mWidth (width)
{
    
}

template <typename T>
inline Matrix<T>::Matrix (unsigned height, unsigned width, T&& element):
    std::vector<T>(height * width, T()), mHeight (height), mWidth (width)
{

}

template <typename T>
inline T& Matrix<T>::at (unsigned x, unsigned y)
{
    return std::vector<T>::at(x * mWidth + y);
}


template <typename T>
inline bool Matrix<T>::isInRange(unsigned x, unsigned y) const
{
   return ((x < mHeight) && (y < mWidth));
}

template <typename T>
inline void Matrix<T>::fill(const T &element)
{
    std::fill(std::vector<T>::begin(), std::vector<T>::end(), element);
}

template <typename T>
inline unsigned Matrix<T>::getHeight() const
{
    return mHeight;
}

template <typename T>
inline unsigned Matrix<T>::getWidth() const
{
    return mWidth;
}

template <typename T>
inline void Matrix<T>::setHeight (unsigned height)
{
    setSize(height, mWidth);
}

template <typename T>
inline void Matrix<T>::setWidth(unsigned width)
{
    setSize(mHeight, width);
}

template <typename T>
inline void Matrix<T>::setSize(unsigned height, unsigned width)
{
    if (height == mHeight && width == mWidth)
        return;
    
    unsigned lWidth = mWidth;
    unsigned lHeight = mHeight;
    std::vector< T > buffer(*this);

    mWidth = width;
    mHeight = height;

    std::vector<T>::resize(mHeight * mWidth);

    for (unsigned i = 0; i < std::min(lHeight, mHeight); i++)
        for (unsigned j = 0; j < std::min(lWidth, mWidth); j++)
            std::vector<T>::at(i * mHeight + j) = buffer.at(i * lHeight + j);
}



#endif // MATRIX_HPP


