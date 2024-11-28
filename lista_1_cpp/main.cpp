#include <iostream>
#include <vector>

// zadanie 1
template<typename T, typename C>
T my_max(T a, T b, C comp){
    return comp(a,b) ? b : a; // wyrazenie labda jesli true bedzie b jak nie to a
}

// zadanie 2 złożolność O(n^2)
template<typename T>
void insertion_sort(std::vector<T> &vec){
    for(size_t i =1; i < vec.size(); ++i){
        T key = vec[i];
        int j = i - 1;
        while(j >= 0 && vec[j] > key){
            vec[j+1]=vec[j];
            --j;
        }
        vec[j+1] = key;
    }
}

// zadanie 3 a, przestrzen nazw cpplab
namespace cpplab{
template<typename T>
class vector{
private:
    size_t size_;
    size_t capacity;
    T *data;
public:
    using value_type = T;
    // konstruktor który domyślnie nie alokuje żadnej pamięci
    vector():size_(0), capacity(0), data(nullptr){}
    // dekonstruktor
    ~vector(){ delete[] data; size_ = 0; }
    // funkcja do zmiany wymiarów vectora potrzebna do dynamicznego dodawania i usuwania elementow
    void resize(size_t new_capacity){
        T* new_data = new T[new_capacity];
        for(size_t i = 0; i < size_; ++i)
            new_data[i] = data[i];
        delete[] data;
        data=new_data;
        capacity=new_capacity;
    }
    // funkcja push back
    void push_back(const T &value){
        if(size_==capacity){
            resize(capacity==0 ? 1:capacity*2);
            data[size_++]=value;
        }
    }
    // funkcja pop back
    void pop_back(){
        data[size_--];// zmiana dzialania funckji pop_back() aby nie musiala wykonywać tyle czynności
    }
    // operator [] do dostepu do elementow
    T &operator[](size_t index) { return data[index];}
    // ten sa operator do stalych obiektow
    const T &operator[](size_t index) const{ return data[index];}
    // funkcja size do pobierania aktualnej liczby elementow
    size_t size() const{ return size_;}
};
// zmiana miejsca deklaracji, poza klasa 
template<typename V1, typename V2>
    auto operator*(const V1& v1, const V2& v2){ // definiowanie operatora* jako przyjaciela klasym ktory poznwala na obliczanie iloczyu skalarnego miedzy wektorami
        // porownywanie rozmiarow
        if (v1.size() != v2.size())
            throw std::invalid_argument("Wektory musza miec ta sama wielkosc");
        // okreslenie typu wyniku ilorazu skalarnego
        using result_type=decltype(v1[0]*v2[0]);  // decltype zwraca typ wynikowy mnozenia dwoch wektorow
        // inicjalizacja zmiennej o tym samym typie co wynik mnozenia
        result_type result=result_type();  // uzywamy domyslnego konstruktora ktory zwraca wartosc normalnca
        // petla do obliczania iloczynu skalarnego
        for(size_t i=0;i<v1.size();++i)
            result += v1[i]*v2[i];
        return result;
    } // uzywamy friend aby miec dostep do prywatnych czlonkow klasy z ktora jest powiazany
}

int main(){
    // sprawdzanie zadania 1
    auto comp = [](int a, int b) { return a<b; };
    int x = 8, y = 1;
    std::cout << my_max(x,y,comp) << "\n";
    double d = 1.23, s = 9.72;
    std::cout << my_max(d,s,comp) << "\n";
    // sprawdzanie zadania 2
    std::vector<int> vec={5,4,3,2,1,6,7,8};
    insertion_sort(vec);
    for(const auto &elem:vec) // wyswietlanie
        std::cout<<elem<<" "; // posortowanego
    std::cout<<"\n";          // vectora
    // sprawdzanie zadania 3
    cpplab::vector<double> v1;
    v1.push_back(1.1);
    v1.push_back(2.2);
    v1.push_back(3.3);
    for(size_t i=0;i<v1.size();++i){ // wyswietlanie
        std::cout<<v1[i]<<" "; // i sprawdzanie czy wielkosc sie zgadza od razu
    }
    std::cout<<"\n";
    // sprawdzanie dzialania operatora * do mnozenia skalarnego
    std::vector<double> stdVec={1.0,2.0,3.0};
    double scalar=v1*stdVec; // sprawdzanie dla cpplab * vector
    double scalar_2 = stdVec*v1;
    std::cout<<scalar<<"\n";
    std::cout<<scalar_2<<"\n";
    // sprawdzanie dzialania popa
    v1.pop_back();
    for(size_t i=0;i<v1.size();++i)
        std::cout<<v1[i]<<" ";
    std::cout<<"\n";
}
