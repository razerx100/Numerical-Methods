#ifndef __EQUATION_HPP__
#define __EQUATION_HPP__
#include<ostream>
#include<vector>
#include<cmath>
#include<string>

//ONLY ADDITION AND SUBTRACTION WITH SINGLE FRACTION ATM

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
        std::vector<std::vector<Term>> m_variables;
        void SetVariables(std::string equation){
            std::string pre_ope = "+", temp_eqn = equation + "=";
            std::vector<Term> variables;
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
                            variables.emplace_back(Term(std::stoi(co_eff), std::stoi(degree)));
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
                        variables.emplace_back(var);
                    }
                    if(pre_ope == "-")
                        variables.back().co_efficient *= -1;
                    //Replace with index
                    if(temp_eqn[i] == '-')
                        pre_ope = "-";
                    else
                        pre_ope = "+";
                }
            }
            m_variables.emplace_back(variables);
        }
        void CheckFraction(){
            int length = m_equation.length();
            bool fraction = false;
            for(int i = 0; i < length; ++i){
                if(m_equation[i] == '/'){
                    SetVariables(m_equation.substr(1, i - 2));
                    SetVariables(m_equation.substr(i + 2, (length - 1) - (i + 2)));
                    fraction = true;
                    break;
                }
            }
            if(!fraction){
                SetVariables(m_equation);
                SetVariables("1");
            }
        }
        public:
        Equation(const char* eqn) : m_equation(std::move(eqn)){
            CheckFraction();
        }
        Equation(std::string eqn) : m_equation(eqn){
            CheckFraction();
        }

        double Answer(double x){
            double answer1 = 0, answer2 = 0;
            for(Term i : m_variables[0])
                answer1 += i * x;
            for(Term i : m_variables[1])
                answer2 += i * x;
            return answer1 / answer2;
        }

        inline std::string GetEqn() { return m_equation; }
        inline std::vector<Term> GetVariables() { return m_variables[0]; }
    };
}
#endif