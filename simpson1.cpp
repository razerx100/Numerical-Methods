#include<iostream>
#include"Simpson1_3.hpp"
int main(){
    std::cout << "Write the equation (with no space and x as numeral) : ";
    std::string equation;
    std::cin >> equation;
    Chronos::Simpson1_3 sim = equation;
    sim.Answer();
    return 0;
}