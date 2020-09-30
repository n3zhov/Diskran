#ifndef TVector_HPP
#define TVector_HPP
#include <cstdio>
namespace NMystd{
    struct TItem{
        char key [33];
        char value [2049];
    };

    template<class T>
    class TVector {
    private:
        unsigned int Capacity;
        unsigned int MaxSize;
        T *Data;
    public:
        void Assign(unsigned int n, T elem);
        void Assign(unsigned int n);
        void Clear();
        T &operator[](const unsigned int &index);
        void PushBack(T elem);
        T PopBack();
        unsigned int Size();
        TVector();
        TVector(unsigned int n);
        TVector(unsigned int n, T elem);
        ~TVector();
    };
    template<class T>
    void TVector<T>::Assign(const unsigned int n, T elem) {
        delete[] Data;
        MaxSize = n*2;
        Data = new T[MaxSize];
        Capacity = n;
        for (int i = 0; i < n; i++) {
            Data[i] = elem;
        }
    }

    template<class T>
    void TVector<T>::Assign(const unsigned int n) {
        delete[] Data;
        MaxSize = n*2;
        Data = new T[MaxSize];
        Capacity = 0;
    }


    template <class T>
    void TVector<T>::Clear(){
        Capacity = 0;
        MaxSize = 0;
        delete[] Data;
    }

    template<class T>
    T& TVector<T>::operator[](const unsigned int &index) {
        return Data[index];
    }

    template<class T>
    void TVector<T>::PushBack(T elem) {
        if (MaxSize == 0) {
            MaxSize = 1;
            Data = new T[MaxSize];
        }
        if (Capacity == MaxSize) {
            MaxSize = MaxSize * 2;
            T* newData = new T[MaxSize];
            for (int i = 0; i < Capacity; ++i) {
                newData[i] = Data[i];
            }
            delete[] Data;
            Data = newData;
        }
        Data[Capacity] = elem;
        Capacity++;
    }

    template<class T>
    T TVector<T>::PopBack() {
        if (Data == 0) {
            return 0;
        }
        T returnElem = Data[Capacity];
        Capacity--;
        Data[Capacity] = 0;
        return returnElem;
    }

    template<class T>
    unsigned int TVector<T>::Size() {
        return Capacity;
    }

    template<class T>
    TVector<T>::TVector() {
        Capacity = 0;
        MaxSize = 0;
        Data = 0;
    }

    template<class T>
    TVector<T>::TVector(const unsigned int n) {
        Assign(n);
    }

    template<class T>
    TVector<T>::TVector(const unsigned int n, T elem) {
        Assign(n, elem);
    }

    template<class T>
    TVector<T>::~TVector() {
        delete[] Data;
    }
}
#endif