#include <iostream>
#include <vector>
#include <cctype> 
#include <string>

// zadanie 1
// funkcja do znajdywania liczb w stringach
int extractNumber(const std::string& str) {
	std::string numberstr = "";// tymczasowy string dla przechowywania liczb 
	for (char ch : str) {
		if (std::isdigit(ch))
			numberstr += ch;
	}
	return numberstr.empty() ? 0 : std::stoi(numberstr);// zwracanie znalezionych liczb przeksztalconych na int 
}
// insertion sort typowo dla wektorow stringów
void insertion_str(std::vector<std::string>& str) {
	int n = str.size();
	for (int i = 0; i < n; ++i) {
		std::string key = str[i];
		int j = i - 1;
		while (j >= 0 && extractNumber(str[j]) > extractNumber(key)) {
			str[j + 1] = str[j];
			j--;
		}
		str[j + 1] = key;
	}
}
// zadanie 2 
// definicja ogolna szablonu klasy
template <int N> // szablon który przymuje wartość całkowitą 
class Factorial{
public:
	static const int value=N*Factorial<N-1>::value; // rekurencyjnie silnia 
};
template <>
class Factorial<0>{ // definiowanie specjalnego wyjatku dla 0
public:
	static const int value=1;
};
template <>
class Factorial<1>{ // specjalizacja dla warunku 1 
public: 
	static const int value=1;
};
// zadanie 3  variadic templates szabon funkcji print_all
void print_all(){} // funkcja bazowa, zakonczenie rekurencji 
// szablon funkcji do wypisywania argumentow 
template <typename T, typename... Args>
void print_all(T first, Args... args){
	std::cout<<first;
	if constexpr(sizeof...(args)>0){
	std::cout<<", ";
	}
	print_all(args...);
}

int main() {
	// sprawdzanie zadanie 1
	std::vector<std::string> one = { "zadanie 1", "zadanie 11", "zadanie 2", "zadanie 22", "zadanie 3", "zadanie 33" };
	/*for(int i=0;i<one.size();++i){
		std::cout<<extractNumber(one[i])<<"\n";
	}*/
	insertion_str(one);
	for (const auto& elem : one) {
		std::cout << elem << " ";
	}
	std::cout << "\n";
	// sprawdzanie zadanie 2
	constexpr int n=5; 
	std::cout<<"Silnia "<<n<<" wynosi: "<<Factorial<n>::value<<"\n";
	// sprawdzanie zadania 3 
	print_all(1,1.0,1.0f,"hello");
	std::cout<<"\n";
	print_all(1,2.0);
	std::cout<<"\n";
	
	return 0; 
}
