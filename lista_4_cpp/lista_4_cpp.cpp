#include <iostream>

namespace cpplab {
	template<typename T>
	class vector {
	private:
		T* data;
		size_t size;
		size_t capacity;
	public:
													// domyslny konstrukor 
		vector() : data(nullptr), size(0) {}
													// konstruktor kopiujacy
		vector(const vector& other) : data(new T[other.size]), size(other.size) {
			for (size_t i = 0; i < size; ++i) {
				data[i] = other.data[i];
			}
			std::cout << "Konstruktor kopiujacy\n";
		}
													// operator kopiujacy
		vector& operator=(const vector& other) {
			if (this != other) {					// ochrona przed samoprzypisaniem 
				delete[] data;						// zwolnienie istniejacej pamieci 
				size = other.size;					// kopiowanie rozmiaru 
				data = new T[size];					// alokowanie nowej pamieci 
				for (size_t i = 0; i < size; ++i) { // kopiowanie zawartosci tablicy 
					data[i] = other.data[i];
				}
				std::cout << "Operator kopiujacy\n";
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
	};
}

int main() {

	cpplab::vector<int> wektor1;

	return 0;
}