#include<iostream>
#include"Trapezoidal.hpp"
int main(){
    std::cout << "Write the equation (with no space and x as numeral) : ";
    std::string equation;
    std::cin >> equation;
    Chronos::Trapezoidal tra = equation;
    tra.Answer();
    return 0;
}