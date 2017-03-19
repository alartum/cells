#ifndef HEADER_MATRIX_HPP_INCLUDED
#define HEADER_MATRIX_HPP_INCLUDED

#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>

template <typename T>
class Matrix
{
public:
    Matrix (unsigned width = 0, unsigned height = 0, const T& element = T());
    // Возвращает ссылку элемент с данной позицией
    T& at (unsigned x, unsigned y);
    // Заполняет матрицу элементом element
    inline void fill (const T& element);
    // Изменяет высоту
    inline void setHeight (unsigned height);
    // Изменяет ширину
    inline void setWidth (unsigned width);
    // Изменяет оба параметра
    inline void setSize (unsigned width, unsigned height);
    inline unsigned getHeight () const;
    inline unsigned getWidth () const;

protected:
    // Корректны ли координаты
    inline bool isInRange (unsigned x, unsigned y) const;
private:
    // Размеры матрицы
    unsigned mHeight, mWidth;
    // Вектор, в котором хранится
    std::vector<T> mElements;
    
    
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
        mHeight = Other.mHeight;
        mWidth = Other.mWidth;
        mElements = Other.mElements;
    }

    inline Matrix< T > & operator = (const Matrix< T > & Other) const 
    {
        mHeight = Other.mHeight;
        mWidth = Other.mWidth;
        mElements = Other.mElements;
    }

    inline Matrix< T > & operator = (const Matrix< T > && Other) const 
    {
        mHeight = Other.mHeight;
        mWidth = Other.mWidth;
        mElements = Other.mElements;
    }
};

template <typename T>
inline Matrix<T>::Matrix (unsigned width, unsigned height, const T &element):
    mHeight (height), mWidth (width), mElements (height * width, element)
{

}

template <typename T>
inline T& Matrix<T>::at (unsigned x, unsigned y)
{
    return mElements[y * mWidth + x];
}


template <typename T>
inline bool Matrix<T>::isInRange(unsigned x, unsigned y) const
{
   return ((x < mWidth) && (y < mHeight));
}

template <typename T>
inline void Matrix<T>::fill(const T &element)
{
    std::fill(mElements.begin(), mElements.end(), element);
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
inline void Matrix<T>::setSize(unsigned width, unsigned height)
{
    unsigned lWidth = mWidth;
    unsigned lHeight = mHeight;
    std::vector< T > buffer = mElements;

    mWidth = width;
    mHeight = height;

    mElements.resize(mHeight * mWidth);

    for (unsigned i = 0; i < std::min(lHeight, mHeight); i++)
        for (unsigned j = 0; j < std::min(lWidth, mWidth); j++)
            mElements[i * mWidth + j] = buffer[i * lWidth + j];
}



#endif // MATRIX_HPP


