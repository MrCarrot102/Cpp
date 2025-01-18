#include <iostream> 
#include <vector> 
#include <thread>
#include <future>  
#include <exception> 
#include <cstddef>
#include <type_traits> 
#include <memory> 

// zadanie 1 obliczanie iloczynu skalarnego 
void calculate_dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2, std::promise<double> result_promise){
	try { 
		if(vec1.empty() || vec2.empty())
			throw std::invalid_argument("Wektory nie mogą być puste");
		if(vec1.size() != vec2.size())
			throw std::invalid_argument("Wektory musza miec taka sama wielkosc");
		double result = 0.0; 
		for(size_t i = 0; i <= vec1.size(); i++)
			result += vec1[i] * vec2[i];
		result_promise.set_value(result);
		} catch(...){
		result_promise.set_exception(std::current_exception());
	}
}

// zadanie 2 
namespace cpplab{
	template <typename T>
		class allocator{
			public:
				using value_type = T; // alias typu danych, którym zarządza ten alokator 
				allocator() = default; // konstruktor 
				~allocator() = default; // dekonstruktor 

				T* allocate(std::size_t n){
					if(n==0) return nullptr; // jak liczba elementów 0 to daj nullptr 
					void* ptr = operator new(n*sizeof(T)); // alokacja pamieci dla n elementow typu T
					return static_cast<T*>(ptr); // rzutowanie wskaznika na odpowiedni typ 
				}
				void deallocate(T* p, std::size_t n){
					if(p){ // sprawdzanie czy wskaznik jest nullptr 
						operator delete(p,n*sizeof(T)); // zwalnianie pamieci zaalokowanej dla n elementow
					}
				}
		};
};

int main(){
	std::vector<std::vector<double>> vectors1 = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
	std::vector<std::vector<double>> vectors2 = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
	
	std::vector<std::thread> threads;
	std::vector<std::future<double>> futures;

	// uruchamianie watkow
	for(size_t i = 0; i < vectors1.size(); ++i){
		std::promise<double> promise; 
		futures.push_back(promise.get_future());
		threads.emplace_back(calculate_dot_product, std::ref(vectors1[i]), std::ref(vectors2[i]), std::move(promise)); 
	}
	
	double sum = 0.0;
	for(auto& future : futures){
		try {
			sum += future.get();
		} catch (const std::exception& e){
			std::cerr << "Blad: "<<e.what() << "\n";
		}
	}
	// dolaczanie waktow 
	for(auto& thread : threads){
		if(thread.joinable()){
			thread.join();
		}
	}
	std::cout<<"Suma: " << sum << "\n";
	
	// testowanie zadania 2 
	cpplab::allocator<int> alloc;
	std::cout<<typeid(cpplab::allocator<int>::value_type).name()<<std::endl;

	cpplab::allocator<int>::value_type* p_test = alloc.allocate(1);
	std::cout<<*p_test<<std::endl;
	*p_test = 3; 
	std::cout<<*p_test<<std::endl;
	alloc.deallocate(p_test,1);

	std::vector<int, cpplab::allocator<int>> v;
	v.push_back(13);
	v.push_back(23);
	std::cout<<*(v.end()-1)<<std::endl;






	return 0;


}

