#include <iostream>
#include <vector>

template<typename T, typename C>
T my_max(T a, T b, C comp){
    return comp(a, b) ? b:a;
}


// zadanie 2 definiowanie szablonu funkcji insertion_sort
template<typename T>
std::vector<T> insertion_sort(std::vector<T> v){
    for (int i = 1 ; i < v.size(); ++i){
        int key = v[i];
        int j = i - 1;

        while ( j >= 0 && v[j] > key ){
            v[j+1] = v[j];
            j = j - 1;
        }
        v[j+1] = key;
    }
    return v;
}
// funkcja pomocnicza o wypisywania wektora
template <typename T>
void print_vector(const std::vector<T>& v){
    for ( int i = 1; i < v.size() ; ++i){
        std::cout << v[i] << " ";
    }
    std :: cout << "\n";
}

// zdanie 3
namespace cpplab{ // tworzenie przestrzeni nazw
template<typename T>
class DynamicVector{
public:
    using value_type = T; // definiowanie typu elementow wektora
private:
    T* data; // dynamicznie alokowana pamiec (wskaznik)
    size_t size;    // liczba elementow
    size_t capacity;    // zarezerwowana pojemnosc pamieci
public:
    DynamicVecotr():data(nullptr), size(0), capacity(0){} // konstruktor nie alokujacy domyslnie pamieci
    ~DynamicVector(){
        delete[] data; // dekonstruktor
    }

    // dodwanie elementow na koniec wektora
    void push_back( const T& value ){
        if( size == capacity ) {
            resize_capacity (( capacity == 0 ) ? 1 : capacity * 2 );
        }
        data[size++] = value;
    }
    // usuwanie elementow od konca
    void pop_back() {
        if ( size > 0 )
            --size;
    }

    T& operator[] ( size_t index ) {
        if ( index >= size ) {
            throw std::out_of_range("Za duzy indeks");
        }
        return data[index];
    }

    const T& operator[] (size_t index) const {
        if ( index >= size )
            throw std::out_of_range("Za duzy indeks");

    return data[index];
    }

    };

}



int main(){

    // poczatek zadania 1
    auto comp = [](auto a, auto b){
        return a < b; // definiowanie comp
    };

    // sprawdzanie dla int
    int x = 1, y = 2;
    std::cout << my_max(x,y,comp) << "\n";
    // sprawdzanie dla float
    float f = 1.23, g = 2.34;
    std::cout << my_max(f,g,comp) << "\n";


    // poczatek zadania 2
    std::cout<<"\nzadanie 2:\n";
    // sprawdzanie dzialania sortowania
    std::vector<int> zadanie2 = {10,9,8,7,6,5,4,3,2,1};
    print_vector(insertion_sort(zadanie2));
    return 0;
}
