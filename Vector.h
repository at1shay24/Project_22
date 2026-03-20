#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector {
    private:
        T* data;
        size_t sz;
        size_t cap;

        void resize(size_t new_cap){
            if(new_cap < cap) return;
            T* new_data = new T[new_cap];
            for(size_t i = 0; i < sz; i++) {new_data[i] = data[i];}
            delete[] data;
            data = new_data;
            cap = new_cap;
        }
    
    public:
        //Constructors
        Vector() : data(nullptr), sz(0), cap(0) {}
        //Destructor
        ~Vector() { delete[] data; }
        //Copy Constructor
        Vector(const Vector &other) : data(nullptr), sz(0), cap(0) {*this = other;}
        //Assignement Operator
        Vector &operator=(const Vector &other){
            if(this != other){
                clear();
                if(other.sz > 0){
                    resize(other.sz);
                    for(size_t i = 0; i < other.sz; i++){data[i] = other.data[i];}
                    sz = other.sz;
                }
            }
            return *this;
        }
        //Index operator
        T &operator[](size_t index){
            if(index >= sz) throw std::out_of_range("Index out of bounds");
            return data[index];
        }

        const T &operator[](size_t index) const{
            if(index >= sz) throw std::out_of_range("Index out of bounds");
            return data[index];
        }
        //Clear the vector
        void clear() {
            delete data;
            data = nullptr;
            sz = 0;
            cap = 0;
        }

        //Push back an element
        void push_back(const T &elem){
            if(sz == cap) {
                size_t new_cap = (cap == 0) ? 1 : cap * 2;
                resize(new_cap);
            }
            data[sz++] = elem;
        }

        //Get the number of elements in the vector
        size_t size() const { return sz; }

        //Check if the vector is empty
        bool isEmpty() const { return sz == 0; }

        //Access elements by index
        T &at(size_t index){
            if(index >= sz) throw std::out_of_range("Index out of bounds");
            return data[index];
        }

        const T& at(size_t index) const{
            if(index >= sz) throw std::out_of_range("Index out of bounds");
            return data[index];
        }
};
#endif