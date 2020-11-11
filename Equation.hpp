#ifndef __EQUATION_HPP__
#define __EQUATION_HPP__
#include<ostream>
#include<vector>
#include<cmath>
#include<string>

//ONLY ADDITION AND SUBTRACTION ATM

namespace Chronos {
    class Term {
        public:
        int co_efficient, degree;
        Term() {}
        Term(int co_eff, int deg) : co_efficient(co_eff), degree(deg){}
    };

    double operator*(Term obj, double other){
        return obj.co_efficient * std::pow(other, obj.degree);
    }

    std::ostream& operator<<(std::ostream& out, Term other){
        return out << other.co_efficient << " " << other.degree << "\n";
    }

    class Equation {
        private:
        std::string m_equation;
        std::vector<Term> m_variables;
        void SetVariables(){
            std::string pre_ope = "+", temp_eqn = m_equation + "=";
            for(int i = 0, start = 0; i < temp_eqn.size(); i++){
                std::string variable;
                if (temp_eqn[i] == '+' or temp_eqn[i] == '-' or temp_eqn[i] == '='){
                    variable = temp_eqn.substr(start, i - start);
                    start = i + 1;
                    int j;
                    for(j = 0; j < variable.size(); j++){
                        if(variable[j] == 'x'){
                            std::string co_eff = "1", degree = "1";
                            if(j+1 != variable.size())
                                degree = variable.substr(j+2);
                            if(j != 0)
                                co_eff = variable.substr(0, j);
                            m_variables.emplace_back(Term(std::stoi(co_eff), std::stoi(degree)));
                            break;
                        }
                    }
                    //Without variable
                    if(j == variable.size()){
                        Term var;
                        var.degree = 0;
                        for(j = 0; j < variable.size(); j++){
                            if(variable[j] == '^'){
                                var.co_efficient = std::stoi(variable.substr(0, j));
                                var.co_efficient = std::pow(var.co_efficient, std::stoi(variable.substr(j+1)));
                            }
                        }
                        if(j == variable.size())
                            var.co_efficient = std::stoi(variable);
                        m_variables.emplace_back(var);
                    }
                    if(pre_ope == "-")
                        m_variables.back().co_efficient *= -1;
                    //Replace with index
                    if(temp_eqn[i] == '-')
                        pre_ope = "-";
                    else
                        pre_ope = "+";
                }
            }
        }
        public:
        Equation(const char* eqn) : m_equation(std::move(eqn)){
            SetVariables();
        }
        Equation(std::string eqn) : m_equation(eqn){
            SetVariables();
        }

        double Answer(double x){
            double total = 0;
            for(Term i : m_variables)
                total += i * x;
            return total;
        }

        inline std::string GetEqn() { return m_equation; }
        inline std::vector<Term> GetVariables() { return m_variables; }
    };
}
#endif