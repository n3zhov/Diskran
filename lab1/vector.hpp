#ifndef TVector_HPP
#define TVector_HPP
#include <cstdio>
#include <cstring>
const long long KEY_SIZE = 8;
namespace NMyStd{
    struct TItem{
        int Key[KEY_SIZE];
        char **Value;
    };

    template <class T>
    class TVector{
    private:
        long long TVectorSize;
        long long TVectorCapacity;
        T* Data;
    public:
        void Assign(const T elem);
        void Assign(const long long n, const T elem);
        TVector();
        TVector(const long long n);
        TVector(const long long n, T elem);
        long long Size();
        void PushBack(const T &elem);
        void Pop();
        bool Empty();
        T& operator[] (const long long iterator);
        ~TVector();
    };
    template <class T>
    void TVector<T>::Assign(const T elem){
        for (long long i = 0; i < TVectorSize; ++i){
            Data[i] = elem;
        }
    }

    template <class T>
    void TVector<T>::Assign(const long long n, const T elem){
        for (long long i = 0; i < n; ++i){
            Data[i] = elem;
        }
    }
    template <class T>
    TVector<T>::TVector(){
        TVectorSize = 0;
        TVectorCapacity = 0;
        Data = nullptr;
    }
    template <class T>
    TVector<T>::TVector(const long long n){
        TVectorSize = n;
        TVectorCapacity = n;
        Data = new T[TVectorCapacity];
        Assign(n, T());
    }
    template <class T>
    TVector<T>::TVector(const long long n, T elem):TVector(n){
        Assign(elem);
    }
    template <class T>
    long long TVector<T>::Size(){
        return TVectorSize;
    }
    template <class T>
    void TVector<T>::PushBack(const T &elem){
        if (TVectorCapacity == 0){
            TVectorCapacity = 1;
            TVectorSize = 0;
            Data = new T[TVectorCapacity];
        }
        else if (TVectorCapacity == TVectorSize){
            TVectorCapacity *= 2;
            T* newData = new T[TVectorCapacity];
            for (long long i = 0; i < TVectorSize; ++i){
                newData[i] = Data[i];
            }
            delete [] Data;
            Data = newData;
        }
        TVectorSize += 1;
        Data[TVectorSize - 1] = elem;
    }
    template <class T>
    void TVector<T>::Pop(){
        TVectorSize = 0;
        TVectorCapacity = 0;
        delete [] Data;
    }
    template <class T>
    bool TVector<T>::Empty(){
        return TVectorSize == 0;
    }
    template <class T>
    T& TVector<T>::operator[] (const long long iterator){
        return Data[iterator];
    }
    template <class T>
    TVector<T>::~TVector(){
        delete [] Data;
    }
}
#endif