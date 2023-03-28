#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

int precedence(char op) { // ������� ��������
    if (op == '+' || op == '-') return 1; // ��������� ��������
    if (op == '*' || op == '/') return 2; // ������� ��������
    if (op == '^')return 3;
    return 0; // �������� ��������(�����)
}

string infixToRPN(string infix) {
    stringstream output; //������ �� ��������
    stack<char> TestStack; //���� ��� ������ � �����������

    for (char c : infix) {
        if (isdigit(c)) { //�������� �� �� �����
            output << c;  //�������� �����
        }

        //������ � �������
        else if (c == '(') {
            TestStack.push(c);
        }
        else if (c == ')') {
            while (!TestStack.empty() && TestStack.top() != '(') {
                output << TestStack.top();
                TestStack.pop();
            }
            if (!TestStack.empty() && TestStack.top() == '(') {
                TestStack.pop();
            }
        }
        //������ � �������

        // "����������" ���������
        else if (precedence(c) > 0) {
            while (!TestStack.empty() && precedence(TestStack.top()) >= precedence(c)) {
                output << TestStack.top();
                TestStack.pop();
            }
            TestStack.push(c);
        }
        // "����������" ���������
    }

    //���� ��� �� ��������� ���������
    while (!TestStack.empty()) {
        output << TestStack.top();
        TestStack.pop();
    }
    //���� ��� �� ��������� ���������

    return output.str(); //���� ������ � ���������� ����������� ����� � ������ �����
}

double applyOperator(char op, double num1, double num2) {
    if (op == '+') return num1 + num2;
    if (op == '-') return num1 - num2;
    if (op == '*') return num1 * num2;
    if (op == '/') return num1 / num2;
    if (op == '^') return pow(num1, num2);
}

string evaluateRPN(string rpn) {
    stack<double> valueStack;
    double num1, num2;

    for (char c : rpn) {
        if (isdigit(c)) {
            valueStack.push(c - '0');
        }
        else if (precedence(c)>0) {
            num2 = valueStack.top();
            valueStack.pop();
            num1 = valueStack.top();
            valueStack.pop();
            valueStack.push(applyOperator(c, num1, num2));
        }
    }

    return to_string(valueStack.top());
}

bool Test1() {
    string t1 = "3+4*2/(1-5 )^(2^3)";
    string t2 = infixToRPN(t1);
    string expectation = "342*15-23^^/+";
    if (t2 == expectation)
    {
        cout << "===Test1.1: True===" << endl;
        return true;
    }
    else
    {
        cout << "===Test1.1: False===" << endl;
        return false;
    }
}
bool Test2() {
    string t1 = "(1+2)*(3-4)";
    string expectation = "12+34-*";
    if (infixToRPN(t1) == expectation)
    {
        cout << "===Test2.1: True===" << endl;
        return true;
    }
    else
    {
        cout << "===Test2.1: False===" << endl;
        return false;
    }
}
bool Test3() {
    string t1 = "5-(3+4*2)/2";
    string expectation = "5342*+2/-";
    if (infixToRPN(t1) == expectation)
    {
        cout << "===Test3.1: True===" << endl;
        return true;
    }
    else
    {
        cout << "===Test3.1: False===" << endl;
        return false;
    }

}

int main() {
    Test1();
    Test2();
    Test3();
    return 0;
}

