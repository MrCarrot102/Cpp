#include <iostream>
#include <memory>
#include <vector> 
#include <algorithm> 

// zadanie 1 
class BST{
    public:
        struct Node{
            int value; // wartosc
            std::unique_ptr<Node> left; // wskaznik na lewo 
            std::unique_ptr<Node> right; // wskaznik na prawo 
            Node* parent; // wskaznik na parent

            Node(int val, Node* par = nullptr) : value(val), parent(par){}
        };
        // wskazywanie na poczatek drzewa 
        std::unique_ptr<Node> root;// korzen drzewa
        
        // metoda dodajaca elementy 
        void insert(int value){
            if(!root) // tworzenie korzenia jesli drzewo takiego nie posiada
                root = std::make_unique<Node>(value);
            else 
                insert_recursive(root.get(), value);
        }
        
        void insert_recursive(Node* node, int value){
            if(value < node->value){
                if(node -> left){
                    insert_recursive(node->left.get(), value);
                } else{
                    node->left=std::make_unique<Node>(value, node);
                }
            } else if(value>node->value){
                if(node->right){
                    insert_recursive(node->right.get(), value);
                }else {
                    node->right=std::make_unique<Node>(value, node);
                }
            }
        }
        
        void print_in_order() const { print_in_order_recursive(root.get());}
        
        void print_in_order_recursive(const Node* node) const{
            if(!node) return; // konczenie jesli wezel jest pusty
            print_in_order_recursive(node->left.get());
            std::cout<<node->value<< " ";
            print_in_order_recursive(node->right.get());
        }        
};

// zadanie 2 
namespace cpplab{
    template <typename T>
    class unique_ptr {
        private:
            T* ptr; // wskaznik na zarzadzany obiekt

        public: 
            // konstruktor domyslny 
            unique_ptr() : ptr(nullptr) {}
            // konstruktor przyjmujacy wskaznik 
            explicit unique_ptr(T* raw_ptr) : ptr(raw_ptr) {}
            // destruktor 
            ~unique_ptr(){ delete ptr; } // zwalnianie zarzadzanego obiektu 
            // konstruktor przenoszacy 
            unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; } // pozbywanie sie wlasnosci 
            // opeator przenoszacy 
            unique_ptr& operator=(unique_ptr&& other) noexcept{
                if(this != &other){
                    delete ptr; // zwalnianie aktrualnego zasobu 
                    ptr = other,ptr; // przeniesienie wskaznika
                    other.ptr = nullptr; 
                }
                return *this; 
            }
            // usuwanie kopiowania 
            unique_ptr(unique_ptr&) = delete; 
            unique_ptr& operator=(const unique_ptr&) = delete; 
            // dostep do zarzadzanego obiektu 
            T& operator*() const { return *ptr; }
            T* operator->() const { return ptr; }
            // zwaranie wskaznika na zarzadzany obiekt 
            T* get() const { return ptr; }
            // resetowanie wskaznika 
            void reset(T* new_ptr=nullptr){
                delete ptr; 
                ptr = new_ptr; 
            }
            // zwracanie wskaznika i oddawanie wlasnosci 
            T* release() {
                T* temp = ptr;
                ptr = nullptr; 
                return temp; 
            }
    };
}

// zadanie 3
// funkcja do obliczania maksymalnej wartosci skarbow
int knapsack(int W, const std::vector<int> &weight, const std::vector<int> &values, int N){
    std::vector<std::vector<int>> dp(N+1, std::vector<int>(W+1,0));
    // wypelnianie tabeli dynamicznego programowania 
    for(int i = 1; i<= N; i++){
        for(int w = 1; w <= W; w++){
            if(weight[i-1] <= w){
            // maksimum z dwoch przypadkow
            // 1. nie bierzemy biezacego skarbu
            // 2. bierzemy biezacy skarb 
            dp[i][w] = std::max(dp[i-1][W], dp[i-1][W-weight[i-1]]+values[i-1]);
            } else {
                // nie mozna wziac biezacego skarbu bo waga przekracza limit
                dp[i][W] = dp[i-1][w];
            } 
        }
    }
    // maksymalna wartosc znajduje sie w w tym dp[n][w]
    return dp[N][W];
}


int main(){
    // testowanie zadania 1
    BST tree;
    for(int i=0;i<=10;i++)
        tree.insert(i);
    tree.print_in_order();
    std::cout<<"\n";
    // testowanie zadania 2 
    cpplab::unique_ptr<int> ptr(new int(42));
    std::cout << "Wartość: " << *ptr << "\n";
    // przeniesienie wlasnosci 
    cpplab::unique_ptr<int> ptr2 = std::move(ptr);
    if(!ptr.get())
        std::cout << "ptr jest pusty\n";
    ptr2.reset(new int(100));
    std::cout<<"Nowa wartosc: "<< *ptr2 << "\n";
    // zadanie 3 
    int N = 3, W = 50; 
    std::vector<int> weights = {10,20,30}; // wagi skarbow
    std::vector<int> values = {60,100,120}; // wartosc skarbow 

    int result = knapsack(W, weights, values, N);
    std::cout << "Zadanie 3 odpowiedz: \n";
    std::cout<<result<<"\n";


    return 0; 
}