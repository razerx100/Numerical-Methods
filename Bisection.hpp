#ifndef __BISECTION_HPP__
#define __BISECTION_HPP__
#include<fstream>
#include"Equation.hpp"
namespace Chronos {
    class Bisection {
        Equation equation;
        int x_max;
        inline double find_x0(double x1, double x2) { return (x1 + x2) / 2; }
        public:
        Bisection(const char* eqn) : equation(std::move(eqn)){
            std::vector<Term> vars = equation.GetVariables();
            double var1 = std::pow((vars[1].co_efficient / vars[0].co_efficient), 2);
            double var2 = 2 * (vars[2].co_efficient / vars[0].co_efficient);
            x_max = std::sqrt(var1 - var2);
        }

        void FindRoot(){
            std::vector<std::pair<int, int>> points;
            int start = x_max * -1;
            while(start <= x_max){
                points.emplace_back(equation.Answer(start), start);
                start++;
            }

            double x1, x2, x0;
            for(int i = 0; i < points.size() - 1; i++){
                if((points[i].first > 0 and points[i + 1].first < 0)
                or (points[i].first < 0 and points[i + 1].first > 0)){
                    x1 = points[i].second;
                    x2 = points[i + 1].second;
                    break;
                }
            }

            std::ofstream fout;
            fout.open("Results.txt");
            double f_x0 = 1;
            while(0.0001 - f_x0 < 0){
                x0 = find_x0(x1, x2);
                f_x0 = equation.Answer(x0);
                fout << "x1 = " << x1 << ", x2 = " << x2 << ", x0 = " << x0 << "\n\n";
                if(f_x0 * equation.Answer(x1) < 0)
                    x2 = x0;
                else if(f_x0 * equation.Answer(x2) < 0)
                    x1 = x0;
                if(f_x0 < 0)
                    f_x0 *= -1;
            }
            fout << "Approximate root is " << x0 << "\n";
            fout.close();
        }
    };
}
#endif