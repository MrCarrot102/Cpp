#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <concepts>

// definiowanie konceptu sprawdzajacego czy mozna wykonac iloczyn skalarny
template<typename T, typename U>
concept Scalar = requires(T a, U b){
    {a*b} -> std::converible_to<typename std::common_type_t<T,U>>;
    {a+b};
};

