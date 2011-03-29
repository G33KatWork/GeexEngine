#ifndef _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#include <assert.h>

template <class T>
class DynamicArray
{
protected:
    unsigned int quantity;
    unsigned int currentCapacity;
    unsigned int growBy;
    T* data;

public:
    //Construction and destruction
    DynamicArray(unsigned int initial = 0, unsigned int growBy = 1);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray(void);

    DynamicArray& operator= (const DynamicArray& other);

    //State
    inline unsigned int Count() { return quantity; }
    inline T* GetElements() const { return data; }

    //Access operators
    const T& operator[](unsigned int i) const;
    T& operator[] (unsigned int i);
    
    void Append(const T& element);
    void Clear();
};

template <class T>
DynamicArray<T>::DynamicArray (unsigned int initial, unsigned int growBy)
{
    quantity = initial;
    currentCapacity = quantity;
    this->growBy = growBy;

    if(quantity > 0)
    {
        data = new T[quantity];
        memset(data, 0, sizeof(T) * quantity);
    }
    else
        data = NULL;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
    data = NULL;
    *this = other;
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
    if(data)
    {
        delete[] data;
        data = NULL;
    }
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator= (const DynamicArray<T>& other)
{
    quantity = other.quantity;
    currentCapacity = other.currentCapacity;
    growBy = other.growBy;

    if(data)
        delete[] data;
    if (currentCapacity > 0)
    {
        data = new T[currentCapacity];
        for (int i = 0; i < currentCapacity; i++)
            data[i] = other.data[i];
    }
    else
        data = NULL;

    return *this;
}

template <class T>
const T& DynamicArray<T>::operator[](unsigned int i) const
{
    assert(i < quantity);
    return data[i];
}

template <class T>
T& DynamicArray<T>::operator[](unsigned int i) 
{
    assert(i < quantity);
    return data[i];
}

template <class T>
void DynamicArray<T>::Append(const T& element)
{
    if (++quantity > currentCapacity)
    {
        if (growBy > 0)
        {
            T* newData = new T[(currentCapacity + growBy) * sizeof(T)];
            memset(newData, 0, (currentCapacity + growBy) * sizeof(T));

            for (int i = 0; i < currentCapacity; i++)
                newData[i] = data[i];

            newData[quantity - 1] = element;

            currentCapacity += growBy;

            if(data)
                delete[] data;
            data = newData;

            return;
        }

        // cannot grow the array, overwrite the last element
        quantity--;
    }

    if(currentCapacity > 0)
        data[quantity-1] = element;
}

template <class T>
void DynamicArray<T>::Clear()
{
    quantity = 0;
    currentCapacity = 0;
    if(data)
    {
        delete[] data;
        data = NULL;
    }
}

#endif
