#ifndef __SIMPSON_1_3_HPP__
#define __SIMPSON_1_3_HPP__
#include<fstream>
#include<iostream>
#include"Equation.hpp"
namespace Chronos {
    class Simpson1_3 {
    private:
        Equation eqn;
        int ite_num;
        double lower_bound, upper_bound;
    public:
        Simpson1_3(std::string eqn) : eqn(eqn) {
            std::cout << "Number of iterations : ";
            std::cin >> ite_num;
            std::cout << "Lower limit and Upper limit : ";
            std::cin >> lower_bound >> upper_bound;
        }
        void Answer(){
            std::fstream fout;
            fout.open("Results.txt");
            fout << "Xi = a + i ((b - a) / n)     I = (" << eqn.GetEqn() << ") dx\n";
            fout << "a = " << lower_bound << ", b = " << upper_bound << " and n = " << ite_num << ".\n";
            double values[ite_num + 1];
            for(int i = 0; i <= ite_num; i++){
                values[i] = lower_bound + i * ((upper_bound - lower_bound) / ite_num);
                fout << "x" << i << " = " << values[i] << " ";
            }
            fout << "\nI = ((b - a) / 3n)[f(x0)";
            for(int i = 1; i < ite_num; i++){
                if(i & 1)
                    fout << "+" << 4 << "f(x" << i << ")";
                else
                    fout << "+" << 2 << "f(x" << i << ")";
            }
            fout << "+f(x" << ite_num << ")" <<"]\n";
            fout << "\n  = ((" << upper_bound << " - " << lower_bound << ") / " << "3 * " << ite_num << ")[f(" << values[0] << ")";
            double answer = (upper_bound - lower_bound) / (3 * ite_num);
            double sum = eqn.Answer(values[0]);
            for(int i = 1; i < ite_num; i++){
                if(i & 1){
                    sum += (4 * eqn.Answer(values[i]));
                    fout << "+4f(" << values[i] << ")";
                }
                else{
                    sum += (2 * eqn.Answer(values[i]));
                    fout << "+2f(" << values[i] << ")";
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