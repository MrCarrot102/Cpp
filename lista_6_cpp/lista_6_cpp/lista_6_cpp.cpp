#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include <mutex>
#include <atomic>
#include <numeric>
#include <functional>
#include <condition_variable>
#include <queue>


// funkcja generujaca losowe liczby 
std::vector<int> generateRandomVector(size_t size, int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	std::vector<int> vec(size);
	for (auto& val : vec)
		val = dis(gen);

	return vec; 
}

// funkcja sortujaca zakresy w wektorze 
void sortRange(std::vector<int>& vec, size_t start, size_t end) {
	std::sort(vec.begin() + start, vec.begin() + end + 1);
}
class thread_pool {
public:
	explicit thread_pool(size_t thread_count)
		: stop_processing(false) {
		for (size_t i = 0; i < thread_count; ++i) {
			workers.emplace_back([this]() {
				worker_thread();
				});
		}
	}

	~thread_pool() { stop(); }

	// dodawanie zadan do kolejki 
	void add_task(std::function<double()> task) {
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			tasks.emplace(std::move(task));
		}
		task_available.notify_one();
	}
	// srednia wynikow wykonanych zadan 
	double average() {
		std::unique_lock<std::mutex> lock(results_mutex);
		if (results.empty()) return 0.0;
		double sum = std::accumulate(results.begin(), results.end(), 0.0);
		return sum / results.size();
	}
	// zatrzymywanie watkow procesujacych i zakanczanie 
	void stop() {
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			stop_processing = true;
		}
		task_available.notify_all();
		for (auto& worker : workers) {
			if (worker.joinable()) {
				worker.join();
			}
		}
	}


private:
	// pracujace watki 
	std::vector<std::thread> workers;
	// kolejka 
	std::queue<std::function<double()>> tasks;
	// wyniki zadan 
	std::vector<double> results;
	// synchronizacja dostepu do kolejki i wynikow 
	std::mutex queue_mutex;
	std::mutex results_mutex;
	std::condition_variable task_available; 
	// flaga zatrzymania przetwarzania 
	std::atomic<bool> stop_processing;
	// funkcja watku procesujacego 
	void worker_thread() {
		while (true) {
			std::function<double()> task;
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				task_available.wait(lock, [this]() {
					return stop_processing || !tasks.empty();
					});
				if (stop_processing && tasks.empty())
					return;

				task = std::move(tasks.front());
				tasks.pop();
			}
			double result = task();
			{
				std::unique_lock<std::mutex> lock(results_mutex);
				results.push_back(result);
			}
		}
	}
};



int main() {
	const size_t vectorSize = 1000; 
	std::vector<int> vec = generateRandomVector(vectorSize, 1, 1000);
	// sortowanie watkami 
	std::thread t1(sortRange, std::ref(vec), 0, vectorSize / 2 -1  ); // pierwszy watek
	std::thread t2(sortRange, std::ref(vec), vectorSize / 2, vectorSize - 1); // drugi watek
	// laczenie watkow 
	t1.join();
	t2.join();
	// wektor po posortowaniu
	std::cout << "Wektor po posortowaniu za pomoca dwoch watkow: \n";
	for (size_t i = 0; i < 20; ++i)
		std::cout << vec[i] << " "; // wyswietlanie pierwszych 20 dla oszczednosci miejsca 
	std::cout << "...\n"; 
	// scalenie posortowanych polowek 
	std::inplace_merge(vec.begin(), vec.begin() + vectorSize / 2, vec.end());
	std::cout << "Wektor po scaleniu: \n";
	for (size_t i = 0; i < 20; ++i) 
		std::cout << vec[i] << " ";
	std::cout << "...\n";
	// wektor nie bedzie posortowany w calosci poniewaz pierwsza polowa wektora bedzie
	// posortowana w zakresie 0-499 a druga 500-999, ale wektor jako calosc nie bedzie posrtowany w pelni,
	// poniewaz elementy z pierwszej polowy moga byc wieksze od elementow z drugiej polowy
	// aby usyzskac w pelni posortowany wektor, trzeba posortowac caly wektor lub scalic dwie 
	// posortowane polowki za pomoca algorytmu std::inplace_merge()
	
	// sprawdzenie do zadania 2 
	thread_pool pool(4);
	for (int i = 0; i < 10; ++i) {
		pool.add_task([i]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			return static_cast<double>(i * i);
			});
		}
	// czekanie chwile aby pozwolic watka na przetworzenie zadania 
	std::this_thread::sleep_for(std::chrono::seconds(2));
	// obliczanie sredniej 
	std::cout << "Średnia: " << pool.average() << "\n";
	pool.stop();
	
	
	
	
	
	
	return 0; 
	

}