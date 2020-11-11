#include<iostream>
#include"Bisection.hpp"
int main(){
    Chronos::Bisection bs = "x^2-4x-10";
    bs.FindRoot();
    return 0;
}