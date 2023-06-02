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
#include <algorithm>

using namespace std;

class calculator {
    public:
        static string evaluateExpression(const string & expr) {
            int exprValidation = validateExpression(expr);
            if (exprValidation == 0) {
                return "Invalid Expression!";
            }
            //Prefix evaluation
            if (exprValidation == 1) {
                return evaluatePrefix(expr);
            }
            //Infix evaluation
            if (exprValidation == 2) {
                return evaluateInfix(expr);
            }
            //Postfix evaluation
            if (exprValidation == 3) {
                return evaluatePostfix(expr);
            }
            return "Invalid Expression!";
        }

private:
    static int validateExpression(string expr) {
        string::iterator it;
        int counter = 0;
        vector<char> expressionVec;
        for(it = expr.begin(); it!=expr.end(); it++) {
            if (*it == ' ' || *it == '=') {
                continue;
            }

            //Return 2 if expression is infix assuming parenthesis only exist in infix
            if(*it == '(' || *it == ')') {
                return 2;
            }
            expressionVec.insert(expressionVec.end(), *it);
            counter++;
        }

        //Return 0 if it's not an expression.
        if (counter < 3) {
            return 0;
        }
        //Return 1 if it's a prefix
        if (isOperator(expressionVec[0])) {
            return 1;
        }

        //Return 2 if it's infix
        if (isOperand(expressionVec[0]) && isOperator(expressionVec[1])) {
            //Return 0 if an infix expression contains @ character;
            if (find(expressionVec.begin(), expressionVec.end(), '@') != expressionVec.end()) {
                return 0;
            }
            return 2;
        }

        //Return 3 if it's postfix
        if (isOperand(expressionVec[0]) && isOperand(expressionVec[1])) {
            return 3;
        }
        return 0;
    }

    static string evaluatePostfix(string expr) {
        int a, b;
        stack<float> stk;
        string::iterator it;
        for(it=expr.begin(); it!=expr.end(); it++){
            if(isOperator(*it)){
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
        oss1 << std::fixed << setprecision(0) << result;
        string resultString = oss1.str();
        return resultString;
    }

    static float scanNum(char ch){
        int value;
        value = ch;
        return float(value-'0');//return float from character
    }
    static bool isOperator(char ch){
        return (ch == '+'|| ch == '-'|| ch == '*'|| ch == '/' || ch == '^' || ch == '@');
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

    static int getPrecedence(char op) {
        if (op == '*' || op == '/')
            return 2;
        else if (op == '+' || op == '-')
            return 1;
        else
            return 0;
    }

    static string infix2postfix(string infix) {
        stack<char> stack;
        string postfix;

        for (char cc : infix) {

            if (cc==' ' || cc == '=') {
                continue;
            }

            if (cc == '(') {
                stack.push(cc);
                continue;
            }
            if (cc == ')') {
                while (!stack.empty() && stack.top() != '(') {
                    postfix += ' ';
                    postfix += stack.top();
                    stack.pop();
                }
                if (!stack.empty() && stack.top() == '(') {
                    stack.pop();
                }
                continue;
            }

            if (!isOperator(cc) && cc != '(' && cc != ')') {
                postfix += ' ';
                postfix += cc;
            } else if (isOperator(cc)) {
                if (stack.empty()) {
                    stack.push(cc);
                } else if (!(getPrecedence(stack.top()) > getPrecedence(cc))) {
                    stack.push(cc);
                }
                else {
                    while(!stack.empty() && getPrecedence(stack.top()) > getPrecedence(cc)) {
                        postfix += ' ';
                        postfix+=stack.top();
                        stack.pop();
                    }
                    postfix += ' ';
                    postfix+=cc;
                }
            }
        }

        while (!stack.empty()) {
            postfix += ' ';
            postfix += stack.top();
            stack.pop();
        }
        postfix = postfix.substr(1);
        return postfix;
    }

    static string evaluateInfix(string expr) {
        string postFixed = infix2postfix(expr);
        return evaluatePostfix(postFixed);
    }

    static string evaluatePrefix(string expr) {

        stack<double> operendStack;
        int size = expr.size() - 1;

        for (int i = size; i >= 0; i--) {
            if (expr[i] == ' ' || expr[i] == '=') {
                continue;
            }

            if (isOperand(expr[i]) > 0) {
                operendStack.push(expr[i] - '0');
            } else if (isOperator(expr[i])) {

                if (expr[i] == '@') {
                    double sum = 0;
                    int counter = 0;
                    while (!operendStack.empty() && isOperand(operendStack.top())) {
                        sum += operendStack.top();
                        operendStack.pop();
                        counter++;
                    }
                    operendStack.push(sum / counter);
                } else {
                    double o1 = operendStack.top();
                    operendStack.pop();
                    double o2 = operendStack.top();
                    operendStack.pop();
                    operendStack.push(operation(o1, o2, expr[i]));
                }
            }
        }

        float result = operendStack.top();
        ostringstream oss1;
        //Round up float to a whole number.
        //TODO: Make it keep decimal points
        oss1 << std::fixed << setprecision(0) << result;
        string resultString = oss1.str();
        return resultString;
    }
};

#endif
