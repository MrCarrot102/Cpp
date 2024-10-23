#include <iostream>
#include <vector>

//template<typename T>
void insertion_sort(std::vector<std::string> &vec){
    for(size_t i=1;i<vec.size();++i){
        std::string key=vec[i];
        int j=i-1;
        while(j>=0 && vec[j].length() > key.length()){
            vec[j+1]=vec[j];
            --j;
        }
        vec[j+1]=key;
    }
}

int main(){
    std::vector<std::string> one={"zadanie 1", "zadanie 2", "zadanie 11", "zadanie 22", "zadanie 3"};
    insertion_sort(one);
    for(const auto &elem:one)
        std::cout<<elem<<" ";
    std::cout<<"\n";
}
