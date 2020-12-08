#include<iostream>
#include"Simpson3_8.hpp"
int main(){
    std::cout << "Write the equation (with no space and x as numeral) : ";
    std::string equation;
    std::cin >> equation;
    Chronos::Simpson3_8 sim = equation;
    sim.Answer();
    return 0;
}