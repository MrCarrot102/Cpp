#include <iostream>
#include <concepts>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory> 

template <typename T, typename U>
concept Scalar= requires(T a, U b) {
	{ a * b }->std::convertible_to<std::common_type_t<T,U>>;
	{ a + b };
};

template <typename V1, typename V2>
	requires Scalar<typename V1::value_type, typename V2::value_type>
auto operator*(const V1& v1, const V2& v2) {
	if (v1.size() != v2.size()) {
		throw std::invalid_argument("wektory musz byc tej samej wielkosci");
	}
	using result_type = decltype(v1[0] * v2[0]);
	result_type result = result_type();

	for (size_t i = 0; i < v1.size(); ++i) {
		result += v1[i] * v2[i];
	}
	return result; 
}

// zadanie 2 
template <typename T> 
void as_sorted_view(std::vector<T> v1) {
	std::vector<T> vec1 = v1;				// kopia aby nie zmieniac orginalu 

	std::sort(vec1.begin(), vec1.end());	// sortowanie kopii

	for (const auto &element:vec1) {
		std::cout << element << " ";
	}
	std::cout << "\n";
}
// Zadanie 3 
template <typename T> 
class forward_list {
private:
	// struktura wezla przechowuje wartosci i wskaznik do kolejenego elementu 
	struct Node {
		T data; 
		std::unique_ptr<Node> next;
		Node(const T& data) : data(data), next(nullptr) {}
	};
	std::unique_ptr<Node> head;				// wskaznik na pierwszy element listy 

public:
	forward_list() :head(nullptr) {}
											// dodawanie elementow na poczatek 
	void push_front(const T& value) {
		auto new_node = std::make_unique<Node>(value);
		new_node->next = std::move(head);
		head = std::move(new_node);
	}
	void reverse() {
		std::unique_ptr<Node> prev = nullptr;
		std::unique_ptr<Node> current = std::move(head);

		while (current) {
			auto next = std::move(current->next);
			current->next = std::move(prev);
			prev = std::move(current);
			current = std::move(next);
		}
		head = std::move(prev);
	}
	void print() const {
		Node* current = head.get();
		while (current) {
			std::cout << current->data << " ";
			current = current->next.get();
		}
		std::cout << "\n";
	}
};
int main() {
										// sprawdzanie zadania 1 
	std::vector<int> wektor1{ 1,2,3 };
	std::vector<int> wektor2{ 2,3,4 };
										// dzilanie dla tych samych typow danych 
	try {
		std::cout << "iloczyn skalarny: " << wektor1 * wektor2 << "\n";
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << "\n";
	}
	// dzialanie dla innych typow danych 
	/*std::vector<std::string> wektor3{"a","b","c"};
	try {
		std::cout << wektor1 * wektor3 << "\n";
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << "\n";
	} program wykrywa rozne typy danych i nie daje sie wykonac */
										// sprawdzanie zadania 2 
	std::vector<int> wektor4{ 9,8,7,6,5,4,3,2,1 };
	std::vector<std::string> wektor5{ "zupa","kura","jajo", "arbuz", "bulion"};
	as_sorted_view(wektor4);			// posortowany wektor
	as_sorted_view(wektor5);			// sprawdzenie dla std::stringa
	for (const auto &element : wektor4) {
		std::cout << element<< " ";
	}
	std::cout << "\n";					// orginalny wektor nie zminiony 
										// sprawdzanie zadania 3 
	forward_list<int> lista; 
	lista.push_front(1);
	lista.push_front(2);
	lista.push_front(3);
	std::cout << "lista: ";				// wyswietlanie listy 
	lista.print();
	lista.reverse();					// odwracanie listy 
	std::cout << "lista odwrocona: ";	
	lista.print();						// wyswietlanie odwroconej listy 

	return 0; 
}
