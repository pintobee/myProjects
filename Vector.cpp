#include "Vector.h"
#include <iostream>
#include <cstddef>
using std::size_t;

// template <typename T>
Vector::Vector()
{
    capacity = CHUNK;
    n_elems = 0;
    data_ptr = new T[CHUNK];
}

// template <typename T>
Vector<T>::Vector(const Vector<T> &v)
{
    capacity = v.capacity;
    n_elems = v.n_elems;
    data_ptr = new T[capacity];
    for (size_t i = 0; i < n_elems; ++i)
    {
        data_ptr[i] = v.data_ptr[i];
    }
}

// template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v)
{
    if (this != &v)
    {
        if (capacity < v.n_elems)
        {
            delete[] data_ptr;
            capacity = v.capacity;
            data_ptr = new T[capacity];
        }
        n_elems = v.n_elems;
        std::copy(v.data_ptr, v.data_ptr + n_elems, data_ptr);
    }
    return *this;
}

// template <typename T>
Vector<T>::~Vector()
{
    delete[] data_ptr;
}

// template <typename T>
void Vector<T>::grow()
{
    capacity *= 1.6;
    T *new_ptr = new T[capacity];
    for (int i = 0; i < n_elems; ++i)
    {
        new_ptr[i] = data_ptr[i];
    }
    delete[] data_ptr;
    data_ptr = new_ptr;
}

// Accessors
// template <typename T>
T Vector<T>::front() const
{
    if (n_elems == 0)
    {
        throw std::range_error("Nothing is in this vector");
    }
    return data_ptr[0];
}

template <typename T>
T Vector<T>::back() const
{
    if (n_elems == 0)
    {
        throw std::range_error("Empty vector");
    }
    return data_ptr[n_elems - 1];
}

template <typename T>
T Vector<T>::at(size_t pos) const
{
    if (pos >= n_elems)
    {
        throw std::range_error("Out of range access");
    }
    return data_ptr[pos];
}

template <typename T>
size_t Vector<T>::size() const
{
    return n_elems;
}

template <typename T>
bool Vector<T>::empty() const
{
    return n_elems == 0;
}

// Mutators
// Same as at but no bounds checking
template <typename T>
T &Vector<T>::operator[](size_t pos)
{
    return data_ptr[pos];
}

// Append a new element at the end of the array
template <typename T>
void Vector<T>::push_back(T item)
{
    if (n_elems == capacity)
    {
        grow();
    }
    data_ptr[n_elems] = item;
    ++n_elems;
}

// --n_elems (nothing else to do; returns nothing)
template <typename T>
void Vector<T>::pop_back()
{
    if (n_elems > 0)
    {
        --n_elems;
    }
}

// Remove item in position pos and shuffles following items left
template <typename T>
void Vector<T>::erase(size_t pos)
{
    if (pos >= n_elems)
    {
        throw std::range_error("Invalid position");
    }
    for (size_t i = pos; i < n_elems - 1; ++i)
    {
        data_ptr[i] = data_ptr[i + 1];
    }
    --n_elems;
}

// Shuffle items right to make room for a new element
template <typename T>
void Vector<T>::insert(size_t pos, T item)
{
    if (pos > n_elems)
    {
        throw std::range_error("Invalid position");
    }
    if (n_elems == capacity)
    {
        grow();
    }
    for (size_t i = n_elems; i > pos; --i)
    {
        data_ptr[i] = data_ptr[i - 1];
    }
    data_ptr[pos] = item;
    ++n_elems;
}

// n_elems = 0 (nothing else to do; keep the current capacity)
template <typename T>
void Vector<T>::clear()
{
    n_elems = 0;
}

// Iterators

// Return a pointer to 1st element, or nullptr if n_elems == 0
template <typename T>
T *Vector<T>::begin()
{
    if (n_elems == 0)
    {
        return nullptr;
    }
    return data_ptr;
}

// Return a pointer to 1 past last element, or nullptr if n_elems == 0
template <typename T>
T *Vector<T>::end()
{
    if (n_elems == 0)
    {
        return nullptr;
    }
    return data_ptr + n_elems;
}

// Comparators
template <typename T>
bool Vector<T>::operator==(const Vector<T> &v) const
{
    if (n_elems != v.n_elems)
    {
        return false;
    }
    for (size_t i = 0; i < n_elems; ++i)
    {
        if (data_ptr[i] != v.data_ptr[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T> &v) const
{
    return !(*this == v);
}
