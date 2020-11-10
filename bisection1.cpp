#include<iostream>
#include"Equation.hpp"
int main(){
    Chronos::Equation eq = "x^2-4x-10";
    std::cout << eq.GetEqn() << "\n";
    std::cout << eq.Answer(-1.6875);
    return 0;
}