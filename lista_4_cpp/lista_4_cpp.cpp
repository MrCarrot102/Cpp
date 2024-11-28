#include <iostream> 

namespace cpplab{
    template <typename T>
    class vector{
        private: 
            T* data; // dynamiczna tablica 
            size_t size; // liczba elementow 
            size_t capacity; // pojemnosc 

        private:
            vector():data(nullptr), size(0), capacity(0) {} // konstruktor domyslny 

            vector(size_t initial_capacity) : size(0), cpacity(initial_capacity){
                data = new T[capacity]; // konstruktor z pojemnoscia 
            }

            // konstruktor kopiujacy 
            vector(const vector& other) : size(other.size), cpacity(other.capacity){
                data = new T[capacity];
                for(size_t i = 0; i < size ; ++i){
                    data[i] = other.data[i]; // operator przypisania dla T
                }
                std :: cout << "Konstruktor kopiujacy\n";
            } 
    }
}