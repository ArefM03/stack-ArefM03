#include <iostream>
#include <cctype>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

class CustomStack 
{
private:
    vector<double> elements;

public:
    double top()
    {
        if (!elements.empty())
        {
            return elements.back();
        }
        else
        {
            return -1.0;
        }
    }

    void push(double item)
    {
        elements.push_back(item);
    }

    double pop()
    {
        if (!elements.empty())
        {
            double item = elements.back();
            elements.pop_back();
            return item;
        }
        else
        {
            return -1.0;
        }
    }

    double peek() {
        if (!elements.empty()) {
            return elements.back();
        }
        else {
            return -1.0;
        }
    }

    bool empty() {
        return elements.empty();
    }

    int size()
    {
        return elements.size();
    }
};

int precedence(char op)
{
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '^' || op == '!') {
        return 3;
    }
    return 0;
}

void applyOperator(CustomStack& values, char op)
{
    if (op == '!')
    {
        int val = values.top();
        values.pop();
        int result = 1;
        for (int i = 1; i <= val; ++i)
        {
            result *= i;
        }
        values.push(result);
    }
    else if (op == '^')
    {
        double right = values.top();
        values.pop();
        double left = values.top();
        values.pop();
        values.push(pow(left, right));
    }
    else
    {
        double right = values.top();
        values.pop();
        double left = values.top();
        values.pop();
        if (op == '+')
        {
            values.push(left + right);
        }
        else if (op == '-')
        {
            values.push(left - right);
        }
        else if (op == '*')
        {
            values.push(left * right);
        }
        else if (op == '/')
        {
            values.push(left / right);
        }
    }
}

double evaluateExpression(const string& expression)
{
    CustomStack values;
    CustomStack ops;
    string number;
    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ')
        {
            continue;
        }
        if (expression[i] == '(')
        {
            ops.push(expression[i]);
        }
        else if (isdigit(expression[i]) || expression[i] == '.')
        {
            number = "";
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
            {
                number += expression[i];
                i++;
            }
            i--;
            values.push(stod(number));
        }
        else if (expression[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                applyOperator(values, ops.top());
                ops.pop();
            }
            ops.pop();
        }
        else
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i]))
            {
                applyOperator(values, ops.top());
                ops.pop();
            }
            ops.push(expression[i]);
        }
    }
    while (!ops.empty())
    {
        applyOperator(values, ops.top());
        ops.pop();
    }
    return values.top();
}

string infixToPostfix(const string& expression)
{
    string postfix;
    CustomStack ops;
    for (size_t i = 0; i < expression.length(); i++) 
    {
        if (expression[i] == ' ')
        {
            continue;
        }
        if (isdigit(expression[i]) || expression[i] == '.') 
        {
            postfix += expression[i];
        }
        else 
        {
            postfix += " ";
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i]))
            {
                postfix += ops.top();
                postfix += " ";
                ops.pop();
            }
            ops.push(expression[i]);
        }
    }
    while (!ops.empty()) 
    {
        postfix += " ";
        postfix += ops.top();
        ops.pop();
    }
    return postfix;
}

int main() 
{
    string expression;
    getline(cin, expression);
    string postfixExpression = infixToPostfix(expression);
    cout << "Result: " << evaluateExpression(postfixExpression) << endl;
    return 0;
}