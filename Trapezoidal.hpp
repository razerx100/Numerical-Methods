#ifndef __TRAPEZOIDAL_HPP__
#define __TRAPEZOIDAL_HPP__
#include<fstream>
#include<iostream>
#include"Equation.hpp"
namespace Chronos {
    class Trapezoidal {
    private:
        Equation eqn;
        int trape_nums;
        double lower_bound, upper_bound;
    public:
        Trapezoidal(std::string eqn) : eqn(eqn) {
            std::cout << "Number of trapezoidals : ";
            std::cin >> trape_nums;
            std::cout << "Lower limit and Upper limit : ";
            std::cin >> lower_bound >> upper_bound;
        }
        void Answer(){
            std::fstream fout;
            fout.open("Results.txt");
            fout << "Xi = a + i ((b - a) / n)     I = (" << eqn.GetEqn() << ") dx\n";
            fout << "a = " << lower_bound << ", b = " << upper_bound << " and n = " << trape_nums << ".\n";
            double values[trape_nums + 1];
            for(int i = 0; i <= trape_nums; i++){
                values[i] = lower_bound + i * ((upper_bound - lower_bound) / trape_nums);
                fout << "x" << i << " = " << values[i] << " ";
            }
            fout << "\nI = ((b - a) / 2n)[f(x0)";
            for(int i = 1; i < trape_nums; i++){
                fout << "+" << 2 << "f(x" << i << ")";
            }
            fout << "+f(x" << trape_nums << ")" <<"]\n";
            fout << "\n  = ((" << upper_bound << " - " << lower_bound << ") / " << "2 * " << trape_nums << ")[f(" << values[0] << ")";
            double answer = (upper_bound - lower_bound) / (2 * trape_nums);
            double sum = eqn.Answer(values[0]);
            for(int i = 1; i < trape_nums; i++){
                sum += (2 * eqn.Answer(values[i]));
                fout << "+2f(" << values[i] << ")";
            }
            sum += eqn.Answer(values[trape_nums]);
            fout << "+f(" << values[trape_nums] << ")" <<"]\n";
            fout << "\n  = " << answer * sum;
            fout.close();
        }
    };
}
#endif