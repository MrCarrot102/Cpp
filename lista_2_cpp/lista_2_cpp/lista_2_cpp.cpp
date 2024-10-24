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
template <int N>
struct Factorial {
	static const int value = N * Factorial<N - 1>::value;
};
// czesciowa specjalizacja 
template <>
struct Factorial<0> {
	static const int value = 1;
};



int main() {
	std::vector<std::string> one = { "zadanie 1", "zadanie 11", "zadanie 2", "zadanie 22", "zadanie 3", "zadanie 33" };
	insertion_str(one);
	for (const auto& elem : one) {
		std::cout << elem << " ";
	}
	std::cout << "\n";
	return 0;
}