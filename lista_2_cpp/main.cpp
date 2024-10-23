#include <iostream>
#include <vector>
#include <cctype>

// insertion sort domyslna
template <typename T>
void insertion_sort(std::vector<T> &vec){
    for(size_t i=1; i<vec.size();++i){
        T key=vec[i];
        int j=i-1;
        while(j>=0 && vec[j]>key){
            vec[j+1]=vec[j];
            --j;
        }
        vec[j+1]=key;
    }
}

std::vector<int> insertion_str(std::vector<std::string> &str){
    std::string numberstr="";
    std::vector<int> result;
    for(size_t i=1;i<str.size();++i){
        for(char ch:str[i]){
            if(std::isdigit(ch))
                numberstr += ch;
        }
    }


    return result;
}





int main(){
    std::vector<std::string> one={"zadanie 1", "zadanie 2", "zadanie 11", "zadanie 22", "zadanie 3"};
    insertion_str(one);
    for(const auto &elem:one)
        std::cout<<elem<<" ";
    std::cout<<"\n";
}
