#include <iostream>
#include <utility>
													// klasa pixel 
struct pixel {
	int r, g, b;
	pixel(int r, int g, int b) : r(r), g(g), b(b) {
		std::cout << "Pixel(" << r << ", " << g << ", " << b << ")\n";
	}
	~pixel() {}
};

namespace cpplab {
	template<typename T>
	class vector {
	private:
		T* data;
		size_t size;
		size_t capacity;
													// funkcja pomocnicza do emplace_back
		void reserve(size_t new_capacity) {
			if (new_capacity > capacity) {
				T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
				for (size_t i = 0; i < size; ++i) {
					new (&new_data[i]) T(std::move(data[i]));
					data[i].~T(); // desktruktor dla starego typu
				}
				::operator delete(data);
				data = new_data;
				capacity = new_capacity;
			}
		}
	public:
													// domyslny konstrukor 
		vector() : data(nullptr), size(0) {}
													// konstruktor kopiujacy
		vector(const vector& other) : data(new T[other.size]), size(other.size) {
			for (size_t i = 0; i < size; ++i) {
				data[i] = other.data[i];
			}
			//std::cout << "Konstruktor kopiujacy\n";
		}
													// operator kopiujacy
		vector& operator=(const vector& other) {
			if (this != &other) {					// ochrona przed samoprzypisaniem 
				delete[] data;						// zwolnienie istniejacej pamieci 
				size = other.size;					// kopiowanie rozmiaru 
				data = new T[size];					// alokowanie nowej pamieci 
				for (size_t i = 0; i < size; ++i) { // kopiowanie zawartosci tablicy 
					data[i] = other.data[i];
				}
				//std::cout << "Operator kopiujacy\n";
			}
			return *this;
		}
													// konstruktor przenoszacy 
		vector(vector&& other) noexcept :data(nullptr), size(0) { // referencja przenoszaca
			//std::cout << "Konstruktor przenoszacy\n";
			data = other.data;
			size = other.size;
			other.data = nullptr;					// zerujemy wskazniki w obiekcie zrodlowym 
			other.size = 0;
		}
													// operator 
		vector& operator=(vector&& other) noexcept {
			//std::cout << "Operator przenoszacy\n";
			if (this != &other) {
				delete[] data; 
				data = other.data;
				size = other.size;
				other.data = nullptr;
				other.size = 0;
			}
			return *this;
		}
													// dekonstruktor 
		~vector() {
		delete[] data;
		std::cout << "Dekostruktor\n";
		}
													// funkcja pomocnicza 
		void push_back(const T& value) {
			T* new_data = new T[size + 1];			// wskaznik na dynamicznie alokowana tablice
			for (size_t i = 0; i < size; ++i)
				new_data[i] = data[i];				// kopiowanie elementow z tablicy do nowo alokowanej
			new_data[size] = value;					// wartosc ktora chcemy dodac dodajemy na koniec tablicy
			delete[] data;							// zwalniamy pamiec
			data = new_data;						// nadpisujemy pamiec wskazujac na wskaznik z nowa tablica z naszym elementem 
			++size;									// zwiekszamy rozmiar aby zgadzal sie z rzeczywistym rozmiarem tablicy
		}
													// funkcja do wyswietlania vectora 
		void print() {
			for (int i = 0; i < size; ++i) {
				std::cout << data[i] << " ";
			}
			std::cout << "\n";
		}
													// funkcja emplace_back 
		template<typename... Args>
		void emplace_back(Args&&... args) {
			if (size >= capacity)
				reserve(capacity == 0 ? 1 : capacity * 2);
			new (&data[size]) T(std::forward<Args>(args)...);
			++size;

		}
		int get_size() {
			return size; 
		}
		T& operator[](size_t index) {
			return data[index];
		}
	};
}

int main() {
	// wektor sprawdzajacy 1 
	std::cout << "Wzor wektora:\n";
	cpplab::vector<int> wektor1;
	wektor1.push_back(1);
	wektor1.push_back(2);
	wektor1.print();
	// wektor sprawdzajacy konstruktor kopiujacy 
	std::cout << "Wektor 2, stworzony za pomoca konstruktora kopiujacego:\n";
	cpplab::vector<int> wektor2(wektor1);
	wektor2.print();
	// wektor sprawdzajacy operator kopiujacy 
	std::cout << "Wektor 3, stworzony za pomoca operatora = kopiujacego:\n";
	cpplab::vector<int> wektor3;
	wektor3 = wektor1;
	wektor3.print();
	// sprawdzanie dzialania konstruktora przenoszacego 
	std::cout << "Wektor 4, stworzony za pomoca konstruktora przenoszacego:\n";
	cpplab::vector<int> wektor4 = std::move(wektor1);
	wektor4.print();
	// sprawdzanie dzialania operatora przenoszacego 
	std::cout << "Wektor 5, stworzony za pomoca operatora przenoszacego:\n";
	cpplab::vector<int> wektor5;
	wektor5 = std::move(wektor4);
	wektor5.print();
	// dlaczego nie uzywamy memcpy
	// jest to funkcja niskopoziomowa, ktora kopiuje dane w pamieci bit po bicie, ale w przypadku obiektow z dynamicznie alokowanymi zasobami
	// lub nietrywialnym zarzadzaniem pamiecia jej uzycie moze prowadzic do powaznych problemow.
	// sprawdzanie emplace_back 
	std::cout << "Sprawdzanie pixela \n";
	std::cout << "\n";
	cpplab::vector<pixel> wektor6;
	wektor6.emplace_back(255, 0, 0);
	wektor6.emplace_back(0, 255, 0);
	wektor6.emplace_back(0, 0, 255);
	for (size_t i = 0; i < wektor6.get_size(); ++i) {
		std::cout << "Pixel " << i << ": ("
			<< wektor6[i].r << "," << wektor6[i].g << ", " << wektor6[i].b << ")\n";
	}
	return 0;
}