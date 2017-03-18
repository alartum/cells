#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <QDebug>

// Закомментрировать, если проверка выхода за границы не нужна
//#define MATRIX_RANGE_CHECK

template <class T>
class Matrix
{
public:
    Matrix (unsigned width = 0, unsigned height = 0, const T& element = T());
    // Возвращает элемент с данной позицией
    const T& getElement (unsigned x, unsigned y) const;
    T& changeElement (unsigned x, unsigned y);
    void setElement (unsigned x, unsigned y, const T& element);
    // Заполняет матрицу элементом element
    void fill (const T& element);
    // Изменяет высоту
    void setHeight (unsigned height);
    // Изменяет ширину
    void setWidth (unsigned width);
    // Изменяет оба параметра
    void setSize (unsigned width, unsigned height);
    unsigned getHeight () const;
    unsigned getWidth () const;
protected:
    // Корректны ли координаты
    bool isInRange (unsigned x, unsigned y) const;
private:
    // Размеры матрицы
    unsigned mHeight, mWidth;
    // Вектор, в котором хранится
    QVector<T> mElements;
};

template <typename T>
Matrix<T>::Matrix (unsigned width, unsigned height, const T &element):
    mHeight (height), mWidth (width), mElements (height * width, element)
{

}

template <typename T>
const T& Matrix<T>::getElement (unsigned x, unsigned y) const
{
#ifdef MATRIX_RANGE_CHECK
    if (!isInRange(x, y))
    {
        qDebug () << "The 1st element will be returned!";
        return mElements.at(0);
    }
#endif
    return mElements.at(y * mWidth + x);
}

template <typename T>
void Matrix<T>::setElement(unsigned x, unsigned y, const T &element)
{
#ifdef MATRIX_RANGE_CHECK
    if (!isInRange(x, y))
        return;
#endif
    mElements [y * mWidth + x] = element;
}

template <typename T>
bool Matrix<T>::isInRange(unsigned x, unsigned y) const
{
    if ((x < mWidth) && (y < mHeight))
        return true;
    else
    {
        qDebug() << "Matrix: index out of range!";
        return false;
    }
}

template <typename T>
void Matrix<T>::fill(const T &element)
{
    mElements.fill(element);
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
void Matrix<T>::setSize(unsigned width, unsigned height)
{
    mWidth = width;
    mHeight = height;
    mElements.fill (T(), mHeight * mWidth);
}

template <typename T>
T& Matrix<T>::changeElement(unsigned x, unsigned y)
{
#ifdef MATRIX_RANGE_CHECK
    if (!isInRange(x, y))
    {
        qDebug () << "The 1st element will be returned!";
        return mElements [0];
    }
#endif
    return mElements [y * mWidth + x];
}

#endif // MATRIX_H
