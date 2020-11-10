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
        std::string m_equation, m_postfix_eqn, m_replaced_eqn;
        std::vector<Term> m_variables;
        void GetVariables(){
            m_replaced_eqn = "";
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
                    if(temp_eqn[i] == '=')
                        m_replaced_eqn += std::to_string(m_variables.size() - 1);
                    else if(temp_eqn[i] == '-'){
                        pre_ope = "-";
                        m_replaced_eqn += std::to_string(m_variables.size() - 1) + "+";
                    }
                    else{
                        pre_ope = "+";
                        m_replaced_eqn += std::to_string(m_variables.size() - 1) + "+";
                    }
                }
            }
        }
        void ToPostfix(){
            m_postfix_eqn = "";
            std::vector<std::string> stack;
            int start = 0;
            for(int i = 0; i < m_replaced_eqn.size(); i++){
                if (m_replaced_eqn[i] == '+'){
                    m_postfix_eqn += m_replaced_eqn.substr(start, i - start) + "'";
                    start = i + 1;
                    while(!stack.empty()){
                        m_postfix_eqn += stack.back();
                        stack.pop_back();
                    }
                    stack.emplace_back("+");
                }
            }
            m_postfix_eqn += m_replaced_eqn.substr(start) + "'";
            while(!stack.empty()){
                m_postfix_eqn += stack.back();
                stack.pop_back();
            }
        }
        public:
        Equation(const char* eqn) : m_equation(std::move(eqn)){
            GetVariables();
            ToPostfix();
        }
        Equation(std::string eqn) : m_equation(eqn){
            GetVariables();
            ToPostfix();
        }

        double Answer(double x){
            std::vector<double> stack;
            int start = 0;
            for(int i = 0; i < m_postfix_eqn.size(); i++){
                if(m_postfix_eqn[i] == '\''){
                    std::string index = m_postfix_eqn.substr(start, i - start);
                    stack.emplace_back(m_variables[std::stoi(index)] * x);
                    start = i + 1;
                }
                else if (m_postfix_eqn[i] == '+'){
                    start = i + 1;
                    double var1 = stack.back();
                    stack.pop_back();
                    double var2 = stack.back();
                    stack.pop_back();
                    stack.emplace_back(var2 + var1);
                }
            }
            return stack.back();
        }

        inline std::string GetEqn() { return m_equation; }
    };
}