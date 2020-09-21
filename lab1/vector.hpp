#ifndef VECTOR_HPP
#define VECTOR_HPP
namespace mystd{
    template<class T>
    class vector {
    private:
        unsigned int Capacity;
        unsigned int Maxsize;
        T *Data;
    public:
        void Assign(unsigned int n, T elem);
        void Clear();
        T &operator[](const unsigned int &index);
        void Push_back(T elem);
        T Pop_back();
        unsigned int Size();
        vector();
        vector(unsigned int n);
        vector(unsigned int n, T elem);
        ~vector();
    };
    template<class T>
    void vector<T>::Assign(const unsigned int n, T elem) {
        delete[] Data;
        Maxsize = n*2;
        Data = new T[Maxsize];
        Capacity = n;
        for (int i = 0; i < n; i++) {
            Data[i] = elem;
        }
    }

    template <class T>
    void vector<T>::Clear(){
        Capacity = 0;
        Maxsize = 0;
        delete[] Data;
    }

    template<class T>
    T& vector<T>::operator[](const unsigned int &index) {
        return Data[index];
    }

    template<class T>
    void vector<T>::Push_back(T elem) {
        if (Capacity == 0) {
            Maxsize = 1;
            Data = new T[Maxsize];
        }
        if (Capacity == Maxsize) {
            Maxsize = Maxsize * 2;
            T* new_Data = new T[Maxsize];
            for (int i = 0; i < Capacity; ++i) {
                new_Data[i] = Data[i];
            }
            Data = new_Data;
        }
        Data[Capacity] = elem;
        Capacity++;
    }

    template<class T>
    T vector<T>::Pop_back() {
        if (Data == 0) {
            return 0;
        }
        T return_elem = Data[Capacity];
        Capacity--;
        Data[Capacity] = 0;
        return return_elem;
    }

    template<class T>
    unsigned int vector<T>::Size() {
        return Capacity;
    }

    template<class T>
    vector<T>::vector() {
        Capacity = 0;
        Maxsize = 0;
        Data = 0;
    }

    template<class T>
    vector<T>::vector(const unsigned int n) {
        Capacity = n;
        Maxsize = n;
        Data = new T[Capacity];
        assign(n, T());
    }

    template<class T>
    vector<T>::vector(const unsigned int n, T elem) {
        Capacity = n;
        Maxsize = n;
        Data = new T[Capacity];
        Assign(n, elem);
    }

    template<class T>
    vector<T>::~vector() {
        delete[] Data;
    }
}
#endif
