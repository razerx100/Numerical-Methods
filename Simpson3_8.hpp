#ifndef __SIMPSON_3_8_HPP__
#define __SIMPSON_3_8_HPP__
#include<fstream>
#include<iostream>
#include"Equation.hpp"
namespace Chronos {
    class Simpson3_8 {
    private:
        Equation eqn;
        int ite_num;
        double lower_bound, upper_bound, h_val;
        inline void get_ite_num(){
            ite_num = (upper_bound - lower_bound) / h_val;
        }
    public:
        Simpson3_8(std::string eqn) : eqn(eqn) {
            std::cout << "Value of h : ";
            std::cin >> h_val;
            std::cout << "Lower limit and Upper limit : ";
            std::cin >> lower_bound >> upper_bound;
            if(h_val <= 0){
                std::cout << "Number of iterations : ";
                std::cin >> ite_num;
            }
            else
                get_ite_num();
        }
        void Answer(){
            std::ofstream fout;
            fout.open("Results.txt");
            fout << "Xi = a + i ((b - a) / n)     I = (" << eqn.GetEqn() << ") dx\n";
            fout << "a = " << lower_bound << ", b = " << upper_bound << " and n = " << ite_num << ".\n";
            double values[ite_num + 1];
            for(int i = 0; i <= ite_num; i++){
                values[i] = lower_bound + i * ((upper_bound - lower_bound) / ite_num);
                fout << "x" << i << " = " << values[i] << " ";
            }
            fout << "\nI = (3(b - a) / 8n)[f(x0)";
            for(int i = 1; i < ite_num; i++){
                if((i + 1) % 4 == 0)
                    fout << "+" << 2 << "f(x" << i << ")";
                else
                    fout << "+" << 3 << "f(x" << i << ")";
            }
            fout << "+f(x" << ite_num << ")" <<"]\n";
            fout << "\n  = (3(" << upper_bound << " - " << lower_bound << ") / " << "8 * " << ite_num << ")[f(" << values[0] << ")";
            double answer = (3 * (upper_bound - lower_bound)) / (8 * ite_num);
            double sum = eqn.Answer(values[0]);
            for(int i = 1; i < ite_num; i++){
                if((i + 1) % 4 == 0){
                    sum += (2 * eqn.Answer(values[i]));
                    fout << "+2f(" << values[i] << ")";
                }
                else{
                    sum += (3 * eqn.Answer(values[i]));
                    fout << "+3f(" << values[i] << ")";
                }
            }
            sum += eqn.Answer(values[ite_num]);
            fout << "+f(" << values[ite_num] << ")" <<"]\n";
            fout << "\n  = " << answer * sum;
            fout.close();
        }
    };
}
#endif