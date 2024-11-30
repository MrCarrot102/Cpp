#include <iostream>
#include <utility>   

// wprowadzenie do algorytmów 
enum class pixel{
    r = 0, 
    g = 0, 
    b = 0
}; 
struct Pixel {
    int r, g, b;

    Pixel() : r(0), g(0), b(0) {} // Konstruktor domyślny
    Pixel(int red, int green, int blue) : r(red), g(green), b(blue) {}

    friend std::ostream& operator<<(std::ostream& os, const Pixel& p) {
        os << "(" << p.r << ", " << p.g << ", " << p.b << ")";
        return os;
    }
};

namespace cpplab{
    template <typename T> 
    class vector{
        private:
            // wskaznik na dynamicznie alokowana pamiec 
            T* data; 
            // liczba elementow 
            size_t size; 
            size_t capacity; 
            // funckja pomocnicza do rozszerzania pojemnosci 
void reallocate(size_t new_capacity) {
    T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T))); // Alokacja surowej pamięci
    for (size_t i = 0; i < size; ++i) {
        new (&new_data[i]) T(std::move(data[i])); // Przenoszenie obiektów z użyciem placement new
        data[i].~T(); // Wywołanie destruktora dla starych obiektów
    }
    ::operator delete(data); // Zwolnienie starej pamięci
    data = new_data;
    capacity = new_capacity;
}


        public:
        // domyslny konstruktor 
        vector(): data(nullptr), size(0) {}
        // konstruktor kopujacy, regula trzech 
        vector(const vector &other) : data(new T[other.size]), size(other.size){
            for(size_t i = 0; i < size; ++i){
                data[i] = other.data[i];
            }
            std::cout << "konstruktor kopiujacy\n";
        }
        // opeator przypisania kopujacego 
        vector& operator=(const vector& other){
            if(this == &other) return *this; // ochraniamy przed samoprzypisaniem 
            delete[] data; // zwalniamy poprzednie zasoby 
            size = other.size;
            data = new T[size];
            for(size_t i = 0; i < size; ++i){
                data[i] = other.data[i];
            }
            std::cout<<"Operator przypisania kopiujacego\n";
            return *this;
        }
        ~vector(){
            delete[] data;               // dekonstruktor 
            std::cout<<"Dekostruktor\n"; // 
        }
        // konstruktor przenoszacy, regula pieciu 
        vector(vector &&other) noexcept : data(other.data), size(other.size){
            other.data = nullptr;
            other.size = 0;
            std::cout<<"Konstruktor przenoszacy\n";
        }
        // operator przypisania przenoszacego 
        vector &operator=(vector&& other) noexcept{
            if(this == &other) return *this; // znowu ochrona przed samoprzypisaniem 
            delete[] data; 
            data = other.data;
            size = other.size; 
            other.data = nullptr; 
            other.size = 0; 
            std::cout << "Operator przypisania przenoszacego\n";
            return *this;
        }
        // funkcja pomocnicza do dodawania elementow 
        void push_back(const T& value){
            T* new_data = new T[size+1];
            for(size_t i = 0; i < size; ++i)
                new_data[i] = data[i];
            new_data[size] = value; 
            delete[] data;
            data = new_data; 
            ++size; 
        }
        // funkcja do wysiwtlania elementow 
        void print() const {
            for(size_t i = 0; i < size; ++i)
                std::cout<<data[i] << " ";
            std::cout<<"\n";
        }

        // metoda emplace_back z perfect forwarding 
        template<typename... Args>
        void emplace_back(Args&&... args){
            if(size == capacity){
                reallocate(capacity == 0 ? 1 : capacity * 2);
            }
            new(&data[size]) T(std::forward<Args>(args)...); 
            ++size; 
        }
        


    };
}

int main(){
    // testy do zadania pierwszego 
    cpplab::vector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);

    std::cout << "Kopiowanie:\n";
    cpplab::vector<int> vec2 = vec1; // konstruktor kopiujący
    vec2.print();

    std::cout << "Przypisanie kopiujące:\n";
    cpplab::vector<int> vec3;
    vec3 = vec1; // operator przypisania kopiującego
    vec3.print();

    std::cout << "Przenoszenie:\n";
    cpplab::vector<int> vec4 = std::move(vec1); // konstruktor przenoszący
    vec4.print();

    std::cout << "Przypisanie przenoszące:\n";
    cpplab::vector<int> vec5;
    vec5 = std::move(vec3); // operator przypisania przenoszącego
    vec5.print();

    // 362 strona w książce temat odnośnie programowania dynamicznego co będzie na liście 5 
    // dobrym przykładem tematu będą liczby fibonaciego 

    // testowanie zadania 2 
    cpplab::vector<Pixel> pixels; 
    pixels.emplace_back(255,0,0);
    pixels.emplace_back(0,255,0);
    pixels.emplace_back(0,0,255);
    std::cout<<"Pixele dodane: \n";
    pixels.print(); 


    return 0;
}


// 287 strona w kosiazce do zrobienia listy 5 