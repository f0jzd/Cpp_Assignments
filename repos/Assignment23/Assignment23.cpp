#include <iostream>
#include <iterator>

using namespace std;

template<typename T>
class CustomVector
{
public:

    struct Iterator
    {
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}//Iterator constructor?

        reference operator*() const { return *m_ptr; }
        pointer operator ->() { return *m_ptr; }

        //Prefix
        Iterator& operator++() { m_ptr++; return *this; };

        //Postfix
        Iterator& operator++(T) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:

        pointer m_ptr;
    };

    Iterator begin() { return Iterator(&data[size]); }
    Iterator end() { return Iterator(&data[size]); }



private:
    int capacity{ 0 };
    int size{ 0 };
    T* data = nullptr;


public:
    CustomVector()
    {
        SetCapacity(8);
    }
    void add(T incomingVal)
    {
        if (size >= capacity)
        {
            SetCapacity(size * 2);
        }
        data[size] = incomingVal;
        size++;
    }

    int GetSize()
    {
        return capacity;
    }
    T& GetValue()
    {
        return *data;
    }
    T* GetPointer()
    {
        return data;
    }

    T Begin()
    {
        return data[0];
    }
    T End()
    {
        return data[size];
    }

    void SetCapacity(int newCapacity) {

        T* oldData = data;
        data = new T[newCapacity];

        if (oldData != nullptr) {
            memcpy(data, oldData, capacity * sizeof(T));
            delete oldData;
        }
        capacity = newCapacity;
    }

    void push_back(T value)
    {
        if (size >= capacity)
        {
            SetCapacity(size * 2);
        }
        data[size + 1] = value;
        size++;
    }

public:




};



int main() {


    CustomVector<int> vektor;
    cout << vektor.GetSize() << endl;

    cout << vektor.GetSize() << endl;


    for (int i = 0; i < 20; ++i) {

        vektor.add(8);
    }
    cout << vektor.GetSize() << endl;


    return 0;
}
