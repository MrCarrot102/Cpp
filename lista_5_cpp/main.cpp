#include <iostream>
#include <memory>

class BST{
    public:
        struct Node{
            int value;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;
            Node* parent;

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


int main(){
    BST tree;
    tree.insert(4);
    tree.insert(5);

    tree.print_in_order();
}