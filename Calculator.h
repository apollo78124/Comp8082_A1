// Starter code Calculator - Question 1 of Assignment 1
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

class calculator {
    public:
        static string evaluateExpression(const string & expr) {

            return evaluatePostfix(expr);
        }

    static string evaluatePostfix(string expr) {
        int a, b;
        stack<float> stk;
        string::iterator it;
        for(it=expr.begin(); it!=expr.end(); it++){
            if(isOperator(*it) != -1){
                a = stk.top();
                stk.pop();
                b = stk.top();
                stk.pop();
                stk.push(operation(a, b, *it));
            }else if(isOperand(*it) > 0){
                stk.push(scanNum(*it));
            }
        }
        float result = stk.top();
        ostringstream oss1;
        //Round up float to a whole number.
        //TODO: Make it keep decimal points
        oss1 << std::fixed << setprecision(0) << result;
        string resultString = oss1.str();
        return resultString;
    }

    static float scanNum(char ch){
        int value;
        value = ch;
        return float(value-'0');//return float from character
    }
    static int isOperator(char ch){
        if(ch == '+'|| ch == '-'|| ch == '*'|| ch == '/' || ch == '^')
            return 1;//character is an operator
        return -1;//not an operator
    }
    static int isOperand(char ch){
        if(ch >= '0' && ch <= '9')
            return 1;//character is an operand
        return -1;//not an operand
    }
    static float operation(int a, int b, char op){
        //Perform operation
        if(op == '+')
            return b+a;
        else if(op == '-')
            return b-a;
        else if(op == '*')
            return b*a;
        else if(op == '/')
            return b/a;
        else if(op == '^')
            return pow(b,a);
        else if(op == '@')
            return (b + a) / 2;
        else
            return INT_MIN; //return negative infinity
    }
    private:
        static int validateExpression(const string & expr) {
            return 0;
        }
};

#endif
